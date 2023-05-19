Add External Interrupt (you may use the code from Blue User Button Interrupt Lecture as a guide) to your code such that:

a) Pressing the BUTTON on the RPG (Rotary Pulse Generator), causes the duration of the BLUE LED (the one connected to Timer 6) blinking to increase by exactly 0.5 seconds.

b) The LCD should show a message in 2 lines that shows the "desired" duration of the LED blinking.

SO if the BLUE LED was supposed to be blinking every 12.5 seconds then the message should read: "BLUE LED Blinks Every 12.5 sec"

Every time you press the RPG button, the LCD message should update itself to show the "desired" duration for which the LED is on.

c) Using the LOGIC ANALYZER, verify that the desired duration printed on the LCD matches the actual duration of the waveform probed on the appropriate PORT D pin.

d) Once the ON time of the BLUE LED gets to 15 seconds, pressing the button should bring the LED ON time back to 0.5 seconds. Subsequent press of the button should increase the LED duration by the 0.5 second amount specified in step (a).
