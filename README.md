


### Timer Functions

TIMER | FUNCTION
--- | --------
TIM1  | Rotary Encoder
TIM2  | Input Trigger
TIM3  | PWM function - AUX output only (32bit timer)
TIM5  | Frequency Sweep - Both outputs
TIM8  | DAC Trigger
TIM15 | Display Manager - screen refresh
TIM16 | Button debounce
TIM17 | Event Manager - Statechart event processor


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

<img src=images/TIM2InputTriggerCapture.svg.png width=320 height=240>

- On timer capture callback, the frequency in hertz is then calculated:

      Freq = MCLK / (TIM2->PSC * TIM2->CCR1)

- Longer processing delays for input frequencies lower than 50Hz are expected.
- At these lower frequencies the input trigger automatically enters "LF Mode" and adjusts the prescaler to improve resolution/accuracy.

#### Voltage Measurements

0.05V  precision
