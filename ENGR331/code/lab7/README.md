Problem Definition: Control the speed of the Motor based on reading from Ultrasonic sensor

Requirements:

Upon startup, the motor should be stopped.
Set the motor to a certain speed (your choice) in either forward or reverse direction.
Wire the Ultrasonic Sensor
Drive the transmit pin of the sensor with PWM signal with a period between 0.65sec to 1sec and a high pulse of 10us.
See specifications in 2nd last slide from Wednesday lecture on Input capture.
Listen to the receive pin of the sensor using input capture and measure the duration of the high pulse on the receive side. The duration of that pulse is proportional to the distance. 
See how to use speed of sound calculation and the time of the pulse to calculate distance.
Display the Distance to an object on the LCD screen
Change the speed of the DC motor based on proximity to an object
slow the motor when object is close
speed up the motor when the object is far.
You an define what close/far and slow/fast speeds are.