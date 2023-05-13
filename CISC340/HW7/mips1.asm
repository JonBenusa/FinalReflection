#Jonathan Benusa
#HW 7 finda the page and offset of an address

.data
	prompt: .asciiz "Enter the address of being accessed: "
	page: .asciiz "Page number = "
	offset: .asciiz "\nOffset = "
	
.text
	li $v0, 4 		#code to print the string
	la $a0, prompt		#telling the adddress of the string to print
	syscall 
	
	li $v0, 5 		#call for an integer from the user
	syscall 
	
	add $t0, $v0, $zero 	#move the address into the temporary register
	addi $t1, $zero, 4096 	#store the page size for the deivide

	div $t0, $t1		#divide the remainder is the offset and the quotient is the page number
	mfhi $t2 		# remainder to $t2
	mflo $t3			# quotient to $t3
	
	li $v0, 4 		#code to print the string
	la $a0, page		#telling the adddress of the string to print
	syscall 
	li $v0, 1		#print the page
	move $a0, $t3
	syscall
	
	li $v0, 4 		#code to print the string
	la $a0, offset		#telling the adddress of the string to print
	syscall 
	li $v0, 1		#print the offset
	move $a0, $t2
	syscall	
	
	
	
