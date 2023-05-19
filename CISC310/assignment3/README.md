# This code contains two threads, a consumer and a producer
# The consumer reads from a shared variable and writes the output to a file
# The producer writes the current index to a shared variable
# The consumer will also write whenever it is waiting o0nj the producer 

The runs had vastly different values. I believe that on the first run value 1 was read before it was ever written to so the first value inside sum[] was 100. This showed the importance of 
wait times for programs that have multiple threads. If a process hasn’t finished yet, then the following lines of code might be using incorrect values. This assignment took roughly 4 hours 
because I hadn’t used threading in python before. 