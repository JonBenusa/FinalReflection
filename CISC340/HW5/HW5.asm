#Jonathan Benusa
#HW 4

.data
	prompt: .asciiz "Enter the number being devided: "
	prompt2: .asciiz "Enter the devisor: "
	answer: .asciiz "The answer is: "
	remainder: .asciiz "  With a remainder of: "
	
.text
call1:
	li $v0, 4 		#code to print the string
	la $a0, prompt		#telling the adddress of the string to print
	syscall 
	
	li $v0, 5 		#call for an integer from the user
	syscall 

	move $t1, $v0		#take the user input and store it in the temporary register
	
call2:
	li $v0, 4 		#code to print the string
	la $a0, prompt2		#telling the adddress of the string to print
	syscall 
	
	li $v0, 5 		#call for an integer from the user
	syscall 

	move $t2, $v0			#take the user input and store it in the temporary register
	beq $t2, 0, call2		#if the number entered is greater than 32767 go back to function
	blt $t2, 0, negative_divisor	#if the number entered is less than 0 follow instuctions for a negative number
	bgt $t2, 0, positive_divisor	#if the number entered is greater than 0 follow instructions for a passitive number
	
negative_divisor:
	slt $t4, $t1, $zero		#if t1 is less than zero then negative is devided by negative, so set flag 1 to indicate positive results
	sub $t2, $zero, $t2	#set t2 positive
	beq $t4, $zero, div_loop	#if t1 wasn't less than 0 go to divide
	sub $t1, $zero, $t1	#set t1 possitive 
	j div_loop		#ready to devide
	  	  
positive_divisor:	
	sgt $t4, $t1, $zero		#if t1 is greater than 0, then dividing pos by a pos and results will be pos
	bne $t4, $zero, div_loop	#if t1 wasn't less than 0 go to divide
	sub $t1, $zero, $t1	#set t1 possitive 
	j div_loop		#ready to devide	
	
div_loop:	#I will be dividing with positive numbers always and then use a flag to check if the sign needs to be flipped after
    sle $t3, $t2, $t1        	#checks if $t1 > $t2
    beq $t3, $zero, end_div 	#if first number < second number, break

    sub $t1, $t1, $t2        	#subtract $t2 from $t1
    addi $t0, $t0, 1              	#add one to counter
    j div_loop               	#loop
    
end_div:
	beq $t4, $zero, neg_results 	#if the flag is zero flip the signs of the results
	j end			#otherwise results are ready to be printed as is

neg_results:
	sub $t0, $zero, $t0	#make results negative
	sub $t1, $zero, $t1	#make remainder negative
	
end:
	li $v0, 4 		#code to print the string
	la $a0, answer		#telling the adddress of the string to print
	syscall 
	li $v0, 1		#print the results
	move $a0, $t0
	syscall
		
	li $v0, 4 		#code to print the string
	la $a0, remainder	#telling the adddress of the string to print
	syscall 
	li $v0, 1		#print the remainder
	move $a0, $t1
	syscall
	
	