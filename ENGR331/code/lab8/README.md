Problem Definition: Sample data into the board through an analog input port at the rate of 8 kHz. Collect a total of 500 data points. Once the collection is done, send data to a terminal window (Logic Analyzer) using UART protocol. 

Requirements:

Setup function generator to create a 0-3V, 1kHz sine wave. Verify using the oscilloscope in lab that the voltage values are in the range of 0V-3V and that the frequency is 1kHz.  Once verified you will use this sine wave signal as the source into an ADC pin. Details below.
Setup Timer 3 with interrupts to occur at the rate of 8kHz.
Setup ADC to measure an analog waveform at 12 bit resolution coming into Port A Pin 1 using the Timer 3 interrupt service routine.
Save a total of 500 data points in an array.

After 500 data points have been stored in the array – turn off the Timer interrupt. Do not collect any more ADC data.
Using UART 4 (Port C Pin 10 ) send the data to a  Logic Analyzer Terminal window.
UART 4 settings:
Baud Rate : 9600 Bits/s
Word Length: 8 bits
Parity: None
Stop Bits: 1
Flow Control: none
You can setup UART for Transmit ONLY
Setup Transmit Interrupt
Connect Port C Pin 10 (Tx) pin to Logic Analyzer CHANNEL 0.
Launch Logic software on the computer.
Press Analyzer button in the Logic window. 
Select Async Serial
Choose (see screenshots below) the right channel and the UART baud rate etc.