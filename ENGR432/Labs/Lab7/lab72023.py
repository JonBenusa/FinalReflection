#raspberry pi code for lab 7

import serial
from time import sleep
import w1thermsensor
import time
import RPi.GPIO as GPIO
from w1thermsensor import W1ThermSensor
#set up board with proper settings
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)
GPIO.setup(5, GPIO.OUT, initial=0)

#store the temp in these global variables
temp1=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
temp2=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]

#gets the temps from the STM32
def get_temps():
    global temp1
    global temp2
    
    sensor = W1ThermSensor()
    index = 0
    
    #Open port with baud rate
    ser = serial.Serial ("/dev/ttyS0", 115200)    
    index = 0
    GPIO.output(5,GPIO.HIGH)
    #Get first sensor data
    while (index<20):
        temperature = sensor.get_temperature()
        time.sleep(1)
        temp1[index]=int(temperature)
        index=index+1
    #Get second sensor's data
    while (index<20):
        #read serial port
        temp = ser.read()              
        sleep(0.03)
        #check for remaining byte
        data_left = ser.inWaiting()             
        temp += ser.read(data_left)
        temp2[index]=int(temp)
        index=index+1
        
#Print the data on the ssh terminal
def print_data():
    index=0           
    while (index<20):    
        print("\nThe temperature is %s farenheit" % temp1[i])
        print("\nThe temperature is %s farenheit" % temp2[i])
        #calculate the percentage difference in the two sensors
        error=abs((temp1[index]-temp2[index])/temp1[index])*100
        print("\nThe percentage error is %s" % error)
        index=index+1

#calculate and display all of the asked for data
def find_key_values():    
    #find sums
    index=0
    temp1_sum=0
    #sum of first temp
    while (index<20):
        temp1_sum=temp1_sum + temp1[index]
        index=index+1  
    index=0
    temp2_sum=0
    #sum of second temp
    while (index<20):
        temp2_sum=temp2_sum + temp2[index];
        index=index+1
    #calculate the averages    
    average1 = temp1_sum/20
    average2 = temp2_sum/20
    #print the values
    print("\n Averege temperature read by DS18B20 is %s " % average1)
    print("\n Averege temperature read by MCP9700A is %s " % average2)

    #find max
    index=0
    max1=0
    max2=0
    while (index<20):
        if max1<temp1[index]:
            max1=temp1[index]
        elif max2<temp2[index]:
                max2=temp2[index]
        index=index+1
    #print the values        
    print("\n Max temperature read by DS18B20 is %s " % max1)
    print("\n Max temperature read by MCP9700A is %s " % max2)
    
    
    #Find the Medians
    #Array Sorting for data received from DS18B20 in Increasing order
    for index in range(0, len(temp1)):
        for index2 in range(index+1, len(temp1)):
            if(temp1[index] > temp1[index2]):
                temp = temp1[index]
                temp1[index] = temp1[index2]
                temp1[index2] = temp
    #again for second temp
    for index in range(0, len(temp2)):
        for index2 in range(index+1, len(temp2)):
            if(temp2[index] > temp2[index2]):
                temp = temp2[index]
                temp2[index] = temp2[index2]
                temp2[index2] = temp
                
    median1=temp1[10]
    median2=temp2[10]
    print("\n Median by DS18B20 is %s " %median1)
    print("\n Median by MCP9700A is %s " %median2)

#print the sorted arrays   
def print_sorted():  
    print("\n Temperature in incresing order measured using DS18B20: \n")
    index = 0
    while index<20:
        print(" "+str(temp1[index]))
        index=index+1
    print("\n Temperature in incresing order measured using MCP9700A: \n")    
    index = 0    
    while index<20:
        print(" "+str(temp2[index]))
        index=index+1    

#main function calls
get_temps()
print_data()
find_key_values()
print_sorted()