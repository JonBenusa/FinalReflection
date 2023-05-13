#Jonathan Benusa
#HW 4

.data
	prompt: .asciiz "Enter a number betweeen 0 and 32767: "
	answer: .asciiz "The results are: "
	
.text
call1:
	li $v0, 4 		#code to print the string
	la $a0, prompt		#telling the adddress of the string to print
	syscall 
	
	li $v0, 5 		#call for an integer from the user
	syscall 

	move $t0, $v0		#take the user input and store it in the temporary register
	bgt $t0, 32767, call1	#if the number entered is greater than 32767 go back to function
	blt $t0, 0, call1	#if the number entered is less than 0 go back to function
	
call2:
	li $v0, 4 		#code to print the string
	la $a0, prompt		#telling the adddress of the string to print
	syscall 
	
	li $v0, 5 		#call for an integer from the user
	syscall 

	move $t1, $v0		#take the user input and store it in the temporary register
	bgt $t1, 32767, call2	#if the number entered is greater than 32767 go back to function
	blt $t1, 0, call2	#if the number entered is less than 0 go back to function
	
	addi $t2, $zero, 0	#this will be the index
	addi $t3, $zero, 0	#this will be the answer
	beq $t1, 0, end 		#if the input for $t1 is 0 then skip arithmetic
	
arithmetic:
	add $t3, $t3, $t0	#$t3 gets $t3 plus $t0
	addi $t2, $t2, 1		#add one to the index
	blt $t2, $t1, arithmetic	#repeat $t1 times

end:
	li $v0, 4 		#code to print the string
	la $a0, answer		#telling the adddress of the string to print
	syscall 

	li $v0, 1		#print the results
	move $a0, $t3
	syscall
	
	