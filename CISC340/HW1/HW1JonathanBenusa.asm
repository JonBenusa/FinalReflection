# Jonthan Benusa
# Homework 1
# This program takes 3-10 integers from the user and stores them in an array. Then prints the array twice, once before and once after sorting
.data
	prompt: .asciiz "Enter the number of integers you would like to use between 3 and 10 inclusive: "
	prompt2: .asciiz "Enter a number: "
	label1: .asciiz "The unsorted array that you entered: "
	label2: .asciiz "The sorted array that you entered: "
	.align 2
	list: .space 40		#declare an array of up to 10 integers 
	
.text
function:
	li $v0, 4 		#code to print the string
	la $a0, prompt		#telling the adddress of the string to print
	syscall 
	
	li $v0, 5 		#call for an integer from the user
	syscall 

	move $t0, $v0		#take the user input and store it in the temporary register
	
	bgt $t0, 10, function 	#if the number entered is greater than 10 go back to function
	blt $t0, 3, function	#if the number entered is less than 3 go back to function
	
	move $a1, $t0
	addi $t0, $zero, 0 	#set an index counter to 0
	addi $s1, $zero, 0 	#set a counter for number of integers stored to 0
	
	
loop: 
	li $v0, 4		#print the prompt for the user
	la $a0, prompt2
	syscall
	
	li $v0, 5		#take an integer from the user
	syscall
	
	add $s0, $v0, $zero	#move the contents of $v0 to $s0
	
	sw $s0, list($t0)	#store the integer added into the next open spot in the array
	   addi $t0, $t0, 4	#add 4 to the index so the next integer is stored in the appropriate spot
	   addi $s1, $s1, 1	#add 1 to the counter
	   
	blt $s1, $a1, loop	#if the count is still less than the number initialized go back through the loop
	
	addi $t0, $zero, 0 	#set an index counter to 0
	addi $s1, $zero, 0 	#set a counter for number of integers stored to 0
	
	li $v0, 4		#print label for unsorted array
	la $a0, label1		
	syscall
while:
	lw $s0, list($t0)	#load the integer from the array
	   addi $t0, $t0, 4	#add 4 to the index so the next integer is from the appropriate spot
	   addi $s1, $s1, 1	#add 1 to the counter
	   
	li $v0, 1			#print the value from the array
	move $a0, $s0
	syscall
	
    	li $a0, 32		#print a space
    	li $v0, 11  
    	syscall
	   
	blt $s1, $a1, while	#if the count is still less than the number initialized go back through the loop
	
	#sort the array
	la  $t0, list      	# Copy the base address of your array into $t1
    	addi $t0, $t0, 40   	# $t0-4 is the last index of the array        
outterLoop:             		# Used to determine when we are done iterating over the Array
    	add $t1, $0, $0     	# $t1 holds a flag to determine when the list is sorted
    	la  $a0, list      	# Set $a0 to the base address of the Array
innerLoop:                  	# The inner loop will iterate over the Array checking if a swap is needed
   	lw  $t2, 0($a0)         # sets $t0 to the current element in array
    	lw  $t3, 4($a0)         # sets $t1 to the next element in array
    	slt $t5, $t2, $t3       # $t5 = 1 if $t0 < $t1
    	beq $t5, $0, continue   # if $t5 = 1, then swap them
    	add $t1, $0, 1          # if we need to swap, we need to check the list again
    	sw  $t2, 4($a0)         # store the greater numbers contents in the higher position in array (swap)
    	sw  $t3, 0($a0)         # store the lesser numbers contents in the lower position in array (swap)
continue:
    	addi $a0, $a0, 4            # advance the array to start at the next location from last time
    	bne  $a0, $t0, innerLoop    # If $a0 != the end of Array, jump back to innerLoop
    	bne  $t1, $0, outterLoop    # $t1 = 1, another pass is needed, jump back to outterLoop
	
	
	
	
	# repeat the previous steps to print the sorted array
	addi $t0, $zero, 0 	#set an index counter to 0
	addi $s1, $zero, 0 	#set a counter for number of integers stored to 0
	
	li $v0, 4		#print label for unsorted array
	la $a0, label2		
	syscall
while2:
	lw $s0, list($t0)	#load the integer from the array
	   addi $t0, $t0, 4	#add 4 to the index so the next integer is from the appropriate spot
	   addi $s1, $s1, 1	#add 1 to the counter
	   
	li $v0, 1			#print the value from the array
	move $a0, $s0
	syscall
	
    	li $a0, 32		#print a space
    	li $v0, 11  
    	syscall
	   
	blt $s1, $a1, while2	#if the count is still less than the number initialized go back through the loop
	
	
	
