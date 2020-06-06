


### Timer Functions

TIMER | FUNCTION
--- | --------
TIM1  | Rotary Encoder
TIM2  | Input Trigger
TIM3  | PWM function - AUX output only
TIM5  | Frequency Sweep - Both outputs
TIM8  | DAC Trigger
TIM15 | Display Manager - screen refresh
TIM16 | Button debounce
TIM17 | Event Manager - Statechart event processor


### Input Trigger Multiplexer

TS5A3357 SP3T [(datasheet)](http://www.ti.com/lit/ds/symlink/ts5a3357.pdf)

- GPIO PC8 mapped to IN1
- GPIO PC9 mapped to IN2  

IN1     | IN2     | FUNCTION
:------:|:-------:|:--------:
H       | L       | TIM2 (PA0)
L       | H       | COMP (PA1)
H       | H       | ADC  (PA2)
