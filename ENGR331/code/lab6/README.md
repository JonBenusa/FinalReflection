# Fun with DC Motor control

Problem Definition: Control the speed and direction of a DC Motor.

Requirements:

Upon startup, the motor should be stopped.
The LCD display should indicate whether the motor is turning forward, reverse, or is stopped.
The LCD display should also display the Duty Cycle (e.g. 70%).
The rotary pulse generator (RPG) should be used to set the speed and direction. Each click should change the speed (duty cycle) by 10%. The following figure illustrates the intended behavior.
An emergency stop button should set the motor speed to 0 and the state to stopped when pressed. The RPG Button should act as the emergency stop.
The TI SN754410 Quad Half-H driver IC is to be used for providing motor drive current.
The H-bridge driver IC should be powered from the lab power supply or external 9V battery provided. The IC will provide the required motor drive current.