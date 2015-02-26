# timer_calc
XMEGA timer parameter calculator demonstration

Demonstrates how to calculate the optimal PER and divider values for XMEGA timers, given a desired overflow frequency in hertz. The same code works on XMEGA devices.

`freq = desired frequency in hertz`<br>
`clkCPU/freq = (PER+1) x perscaler`

The code simply iterates through all available prescalers, checking if a valid PER setting is possible (max 0xFFFF) and which combination has the lowest amount of error.
