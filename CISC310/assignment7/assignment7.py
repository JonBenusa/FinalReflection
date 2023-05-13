#Jonathan Benusa 5/2/2023
#This program makes a simple buddy buffer manager with 4 functions for an operating system and a test driver.
import array as arr 

#the number represents the starting location of the buffer
location = 0
BufferA = []

#just for making the code more managable
sizes = [511, 255, 127, 63, 31, 15, 7]

#starts with 10 buffers of size 511
for index in range(10):    
    #buffers contain two parts, the location and the size
    BufferA.append([location, 511])
    location = location + 511
#arrays for other sizes. starts empty. 
BufferB = []
BufferC = []
BufferD = []
BufferE = []
BufferF = []
BufferG = []

low_memory = False

#list of all available space
bufferMatrix = [BufferA, BufferB, BufferC, BufferD, BufferE, BufferF, BufferG]

UsedBufferMatrix = [[], [], [], [], [], [], []]

#returns the starting point of the  required buffer size that fulfils the request
def giveBuffer(request):
    global low_memory
    #error because request was too large to handle 
    if request > 511:
        #print("Request is too large")
        return -2
    
    #check to see if running low on largest buffers
    get_status()    

    #figure out what the best buffer size is
   
    index_of_bestFit = 0
    while index_of_bestFit < 6 and sizes[index_of_bestFit+1]>request:
        index_of_bestFit = index_of_bestFit+1
    
    

    #find the most efficient way to allocate the requested buffer
    if not bufferMatrix[index_of_bestFit]: #check to see if the best buffer size already exists
        #doesn't exist so break it appart
        current_index = index_of_bestFit - 1
        while current_index > -1:
            if bufferMatrix[current_index]:
                while current_index != index_of_bestFit:
                    offset1 = bufferMatrix[current_index].pop(0)
                    offset1 = [offset1[0], int((offset1[1]-1) / 2)]
                    #ofset of new unsused buffer = old buffer's offset + new buffer's size
                    offset2 = [offset1[0] + sizes[current_index+1], sizes[current_index+1]]
                    #add the new buffers to the list of buffers that their size matches
                    bufferMatrix[current_index+1].insert(0, offset2)
                    bufferMatrix[current_index+1].insert(0, offset1)
                    # move onto the next list of buffers and repeat until you have one of the correct size
                    current_index = current_index +1
                    if len(bufferMatrix[0])<2:
                        low_memory = True
                    else:
                        low_memory = False 
                #once done return the buffer's offset 
                UsedBufferMatrix[index_of_bestFit].insert(0, bufferMatrix[index_of_bestFit].pop(0))
                get_status()   
                return UsedBufferMatrix[index_of_bestFit][0]
            #if there are still no buffers at this level move to the next largest
            else:
                current_index = current_index -1 
        #if you get to here it means that all buffers that are greater than the requested size are used. 
        return -1 #out of space
        #print("Out of space!")

    else:
        #does so just return that value and remove from the list
        UsedBufferMatrix[index_of_bestFit].insert(0, bufferMatrix[index_of_bestFit].pop(0))
        return UsedBufferMatrix[index_of_bestFit][0]
    
def freeBuffer(buffer_address):
    global low_memory
    size_index = 0 #will keep track of which size level we are looking at
    returned_buffer = [] #will store the offset information of the returned buffer once found
    index = 0

    #figure out where to place the buffer based on it's size
    while size_index < 7:
        if UsedBufferMatrix[size_index]:
            buffer_index = 0
            for buffer in UsedBufferMatrix[size_index]:
                if buffer_address == buffer[0]:
                    #remove from the used buffer list because it is now freed
                    returned_buffer = UsedBufferMatrix[size_index].pop(buffer_index)
                    index = size_index
                    break
                buffer_index = buffer_index+1
        size_index = size_index+1    

    #correction because size index is added one too many times in the loop
    size_index = index

    #combine if possible
    combinable = True
    old_level = size_index
    while combinable and size_index!=0:
        for offset in bufferMatrix[size_index]:
            #check to see if addresses are adjacent
            if offset[0] + sizes[size_index] == returned_buffer[0]:
                bufferMatrix[size_index].remove(offset) #remove buffer that is combining from the list of available buffers
                offset[1] = offset[1]*2+1 #save the new size of the buffer
                returned_buffer = offset #save the buffer here so it can check if another combination can be made
                size_index = size_index - 1 #update level that we are looking at for combinations
                break
            elif offset[0] == returned_buffer[0] + sizes[size_index]:   
                bufferMatrix[size_index].remove(offset) #remove buffer that is combining from the list of available buffers
                returned_buffer[1] = returned_buffer[1]*2+1 #save the new size of the buffer
                size_index = size_index - 1 #update level that we are looking at for combinations
                break
        #check to see if a combination was made    
        if size_index == old_level:
            combinable = False
        else: 
            #if a combination was made then update the value of old_level so that there won't be an infinite loop
            old_level = size_index
    
    #Once here combinations have been made. Add the buffer back into the matrix of available buffers
    if bufferMatrix[size_index]:
        location = 0
        for buffer in bufferMatrix[size_index]:
            if buffer[0] > returned_buffer[0]:
                bufferMatrix[size_index].insert(location, returned_buffer)
                break   
            location = location+1
            print("returned: "+ str(returned_buffer[0])) 
            print(buffer[0])        
    else:
        bufferMatrix[size_index].append(returned_buffer)

    #check if memory is tight
    get_status()    

def get_status():
    if len(bufferMatrix[0])<2:
        low_memory = True
    else:
        low_memory = False   
    return low_memory     

def get_number_of_buffers():
    string = ("The nuber of 511 word buffers is: " +str(len(bufferMatrix[0]))+".\n"
                +"The nuber of 255 word buffers is: " +str(len(bufferMatrix[1]))+".\n"
                +"The nuber of 127 word buffers is: " +str(len(bufferMatrix[2]))+".\n"
                +"The nuber of 63 word buffers is: " +str(len(bufferMatrix[3]))+".\n"
                +"The nuber of 31 word buffers is: " +str(len(bufferMatrix[4]))+".\n"
                +"The nuber of 15 word buffers is: " +str(len(bufferMatrix[5]))+".\n"
                +"The nuber of 7 word buffers is: " +str(len(bufferMatrix[6]))+".\n\n")    
    return string

#initializing buffer
f = open("Debugger.txt", "w")
f.write("Jonathan Benusa 5.5.2023 Assignment 7\n \n \n \n ")
f.write("Initializing buffers\n")
f.write("Expected values: 10 512 size buffers, Status Ok\n\n")
f.write("Free Buffer Count:\n"+get_number_of_buffers())
f.write("Low on memory = "+ str(get_status())+"\n\n")

#main driving code
def driver(expected, requestedSize):
    offset = giveBuffer(requestedSize)
    if type(offset) is int:
        if offset == -2:
            f.write("Requesting "+str(requestedSize)+"\n Expected values: \n "+expected+"\n\n Actual = Error Response: "+ str(offset)+"\n\n")
        elif offset == -1:
            f.write("Requesting "+str(requestedSize)+"\n Expected values: \n"+expected+"\n\n Error response: "+ str(offset)+"\n\n")
    else:
        f.write("Requesting "+str(requestedSize)+"\n Expected values: \n"+expected+"\n\n Actual = Assigned address is: "+ str(offset)+"\n\n")
        f.write(get_number_of_buffers())
        f.write("Memory is tight = "+str(get_status())+"\n\n")    

f.write("Requesting 700 \nExpected values: \n")
driver("Error code: -2", 700)

f.write("Request buffer size 6 \n Expected values: \n 9 510 size buffers, 1 254 size buffer, 1 126 size buffer, \n 1 62 size buffer, 1 30 size buffer, 1 14 size buffer and 1 6 size buffer, Status OK\n\n")
driver("Assigned Address: 0", 6)

f.write("Using up all memory starting now:\n\n")
for index in range(10):
    if bufferMatrix[0]:
        driver("Assigned address: "+str(bufferMatrix[0][0]), 511)
    else:
        driver("Error Code: -1", 511)

f.write("Returning size 511 Buffers\n\n")
while UsedBufferMatrix[0]:  
    freeBuffer(UsedBufferMatrix[0][0][0])
f.write("Current Status: \n" +get_number_of_buffers()+"\n\n")

f.write("Returning size 7 Buffers\n\n")
while UsedBufferMatrix[6]:  
    freeBuffer(UsedBufferMatrix[6][0][0])
f.write("Current Status: \n" +get_number_of_buffers()+"\n\n")


f.write("Requesting 21 254 sized buffers:\n\n")
for index in range(21):
    if bufferMatrix[0] or bufferMatrix[1]:
        if bufferMatrix[1]:
            driver("Assigned address: "+str(bufferMatrix[1][0][0]), 254)
        else:
            driver("Assigned address: "+str(bufferMatrix[0][0][0]), 254)
    else:
        driver("Error Code: -1", 254)

f.write("Returning size 254 Buffers\n\n")
while UsedBufferMatrix[1]:  
    freeBuffer(UsedBufferMatrix[1][0][0])
f.write("Current Status: \n" +get_number_of_buffers()+"\n\n")

f.write("Free buffer at the end: "+ str(bufferMatrix))


