# Jonathan Benusa 2/24/2023 Assignment 2
#
# This code contains two threads, a consumer and a producer
# The consumer reads from a shared variable and eventually adds the sum of read values
# The producer writes to a shared variable


import threading
import random

num = 100  
sum = []  

def producer():
    i=0
    
    while  i<5:
        wait_time = random.randint(1, 3)  # random wait time from 1 to 3 seconds
        threading.Timer(wait_time, lambda: write_num(i)).start() #start thread
        i=i+1
# write to num
def write_num(value):
    global num

    num = value

def consumer():
    i = 0

    while i < 5:
        wait_time = random.randint(1, 3)  # random wait time from 1 to 3 seconds
        threading.Timer(wait_time, lambda: read_num()).start() #start thread
        i = i + 1
def read_num():
    global num
    global sum

    sum.append(num)

    if len(sum)>4:
        # write to a file
        with open('output.txt', 'w') as f:
            final_sum = sum[0]+sum[1]+sum[2]+sum[3]+sum[4] #add the final sum
            f.write("Jonathan Benusa \n"+"ICS 462 Assignment #2 \n"+"The sum is "+str(final_sum)+"\n")
            print(final_sum)
        print('Worked')

# main code
thread1 = threading.Thread(target=producer)
thread2 = threading.Thread(target=consumer)
thread1.start()
thread2.start()
