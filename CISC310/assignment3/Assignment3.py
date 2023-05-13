# Jonathan Benusa 2/24/2023 Assignment 3
#
# This code contains two threads, a consumer and a producer
# The consumer reads from a shared variable and writes the output to a file
# The producer writes the current index to a shared variable
# The consumer will also write whenever it is waiting o0nj the producer  


import threading
import random
import queue
import time

# shared variables
buffer = [None] * 5
buffer_index = 0

# lock for accessing shared variables
lock = threading.Lock()

# output file setup
file = open("output.txt", "a")
print("file created")
file.write("Jonathan Benusa\n")
file.write("ICS 462 Assignment #3\n\n\n")
print("file header done")

def producer():
    global buffer, buffer_index
    i = 0
    while i < 100:
        # generate random wait time
        wait_time = random.randint(1, 4)
        time.sleep(wait_time) #start wait
        
        with lock:
            # wait for available space in buffer
            while buffer_index == 5:
                time.sleep(1) #start wait
            
            # add item to buffer
            buffer.append(i)
            buffer_index = buffer_index+ 1
            
            # check if producer is done
            if i == 99:
                buffer.append(-1)
                done_flag = True
        i = i +1
    file.close()

def consumer():
    global buffer, buffer_index
    # generate random wait time
    wait_time = random.randint(2, 5)
    time.sleep(wait_time) #start wait
    
    with lock:
        # wait for available item in buffer
        while buffer_index == 0:
            file.write("consumer waiting\n")
            time.sleep(1) #start wait
        # read item from buffer
        num = buffer.pop(0)
        buffer_index =buffer_index- 1
        # check if consumer is done
        if num == -1:
            file.write("Consumer done\n")
        else:
            file.write(str(num) + "\n")
    file.close()

# create and start threads
producer_thread = threading.Thread(target=producer)
consumer_thread = threading.Thread(target=consumer)
producer_thread.start()
consumer_thread.start()

# wait for threads to finish
producer_thread.join()
consumer_thread.join()
