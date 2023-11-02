FAN control via UART commands/responses

Design and write a control program for the fan through control commands via the UART protocol with the following features:

1 Turn on/off the fan (when turned off, only accepts commands to turn on the fan), with an LED to indicate whether the fan is on or off.

- Off: Default mode, after a power-on reset, the fan will be in the off state.

- On: The fan will only be in the on state after receiving the command to turn it on. The mode and fan speed will remain the same as before (for example, if the fan was in manual control mode and set to speed 2 before being turned off, when turned back on, the fan will remain in manual control mode and set to speed 2).

2 Mode (with an LED to indicate the mode)

- Automatic: Automatically adjust the fan speed according to the measured temperature (temperature is read from an ADC with a range of 5 to 50 degrees Celsius).

+ Below 15 degrees: fan speed at 0.

+ 16 to 30 degrees: fan speed at 1.

+ Above 30 degrees: fan speed at 2.

+ When the fan is in automatic mode and the user sends “mode selection” command to switch to manual control mode, the fan speed will remain the same as before (for example, if the fan speed was set to 1, when switching to manual control mode, the fan speed will still be at 1).

- Manual control:

+ The user can send a “wind level selection” command to select fan speed levels 0, 1, or 2.

+ When the fan is in automatic mode and the user sends a “wind level selection” command to select a fan speed level (such as level 1), the fan will automatically switch to manual control mode with the speed set to level 1.

3 Wind level (3 levels with LED indicator)

- Level 0: equivalent to PWM duty cycle of 0%.

- Level 1: equivalent to PWM duty cycle of 60%.

- Level 2: equivalent to PWM duty cycle of 80%.

4.Implement:

· Build a design document for the system.

· Use variable resistors (connected to an ADC) to simulate changes in temperature values.

· Use a PWM module to control the output for fan speed.

· Use Flash memory to store system states.

· Use GPIO to control LED.

· Use UART 1 to implement control protoco