
### Graphics Library

This project contains a modified and optimised version of the [STM32-ILI9341](https://github.com/martnak/STM32-ILI9341) library.


- Optimized to use direct-to-register SPI for single- and multi-byte transfers (MOSI only). This offers a noticeable performance boost over HAL API.
- Draw functions were modified to use x,y,width,height parameters.
- Additional draw functions from STMBasicGUI were included.


### Timer Functions

Timer | Function | Notes
--- | -------- |-----
TIM1  | Rotary Encoder | Encoder Mode TI2
TIM2  | Input Trigger | Input Capture Direct Mode (see Input Trigger section). Preload Enabled
TIM3  | PWM function | AUX output only
TIM5  | Frequency Sweep | Both outputs (32bit timer)
TIM8  | DAC Trigger | Update Event. Preload Enabled
TIM15 | Display Manager | Calls DM_UpdateDisplay()
TIM16 | Button debounce
TIM17 | Event Manager | Called EM_ProcessEvent()

### Event Manager

EventManager.h defines system states and events for the menu display and user controls (buttons and rotary encoder).


  eSystemState |
  ------|
  Toplevel_Main_Menu_State
  Toplevel_Output_Menu_State
  Toplevel_Input_Menu_State
  Func_Main_Menu_State
  Func_Signal_Menu_State
  Func_Aux_Menu_State
  Gain_Main_Menu_State
  Gain_Signal_Menu_State
  Gain_Aux_Menu_State
  Freq_Main_Menu_State
  Freq_Preset_Menu_State
  Freq_Adjust_Menu_State
  Freq_Sweep_Menu_State
  Freq_Prescaler_Menu_State
  Bias_Menu_State
  Idle_State = Toplevel_Main_Menu_State

eSystemEvent|
-----|
evIdle,						
evBlueBtn,				
evGreenBtn,				
evYellowBtn,			
evRedBtn,				
evEncoderSet,			
evEncoderPush,			
evSweepEnableBtn,
evSweepModeBtn,			
evSweepSpeedBtn,
evSweepLimitBtn,


Active event and state are held in global variables eNextState and eNewEvent, respectively.

Interrupts triggered by the buttons and rotary encoder are processed by InterruptManager.c, which sets the global event variable to the appropriate event.

The EM_ProcessEvent function is periodically called by Timer #17.

EM_ProcessEvent selects the *current* state and calls the related event handler for the *new* event. A simplified version is shown below:

```
void EM_ProcessEvent()
{

    switch(eNextState)
	{
        case someState1:

            if(eNewEvent == evSomeEvent1)
                eNextState = doSomeEventHandler1();
            break;

            if(eNewEvent == evSomeEventN)
                eNextState = doSomeEventHandlerN();
            break;

        case someStateN:
        ....
    }

}
```

The Event handler for the new event is called and *returns the next system state.*

Business logic for Top level menu, Function menu, Frequency menu, Gain menu and Offset Bias menu are delegated to separate files. 


### Display Manager

DisplayManager.h defines a standard colour palette used by the graphics library.

The ILI9341 LCD driver IC  has a very low refresh rate . To avoid flicker, the background is redrawn only on eSystemState change (when the user navigates to a different menu screen). All text is periodically redrawn by Timer15, which executes DM_UpdateDisplay() function. To avoid flicker, text strings must be positioned so that they do not overlap.



### Input Trigger

Input trigger function including external multiplexing, DMA callbacks, frequency and voltage measurements are handled by InputTrigger.c

#### External Multiplexer

An external "TS5A3357" SP3T switch [(datasheet)](http://www.ti.com/lit/ds/symlink/ts5a3357.pdf) selects the input signal path into the microcontroller.

IN1     | IN2     | FUNCTION
:------:|:-------:|:--------:
H       | L       | TIM2 (PA0)
L       | H       | COMP (PA1)
H       | H       | ADC  (PA2)

TS5A3357 pins IN1 and IN2 are set/reset by microcontroller pins PC8 and PC9, respectively.


#### Frequency Measurement

In "Time Mode" the input signal frequency is measured using reciprocal counting methods with TIM2.

- When this mode is enabled TIM2 is enabled and begins counting to 0xFFFF.
- The input signal is externally multiplexed into port PA0 (set to alt. function TIM2_CH1).
- This is internally multiplexed using the interconnect to "tim_ti1_in0".
- A rising edge detected on the input signal triggers a "tim_ti1_fp1" signal to Input Capture Channel 1 and the slave controller.
- TIM2 is configured to reset its count on "tim_ti1_fp1" trigger signal. This sends an write request to the DMA controller and contents of CCR1 is written to memory.

<img src=/images/TIM2InputTriggerCapture.png.svg width=960 height=720>

- On timer capture callback, the frequency in hertz is then calculated:

      Freq = MCLK / (TIM2->PSC * TIM2->CCR1)

- Longer processing delays for input frequencies lower than 50Hz are expected.
- At these lower frequencies the input trigger automatically enters "LF Mode" and adjusts the prescaler to improve resolution/accuracy.

#### Voltage Measurements

0.05V  precision
