#Jonathan Benusa
#Assignment 4
#3/27/2023

#This code calculates the address page number and offset from a given decimal address. It assumes a 32-bit virtual memory address with a 4-KB page size
#outputs the results to output.txt

import string

nums = [19986, 347892, 5978]

def get_page_num_and_offset(num):
    # Calculate the page number
    page_num = num >> 12
    # Calculate the offset 
    offset = num & 0xFFF
    return (page_num, offset)

with open('output.txt', 'w') as f:
    # Loop through the nums
    for num in nums:
        # Get the page number and offset
        page_num, offset = get_page_num_and_offset(num)
        f.write('The num '+str(num)+' is in:\n Page number = '+str(page_num)+'\n Offset = '+str(offset)+'\n\n')
        #print('The num '+str(num)+' is in:\n Page number = '+str(page_num)+'\n Offset = '+str(offset)+'\n\n')

