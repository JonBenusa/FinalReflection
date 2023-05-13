#Jonathan Benusa
#HW 8 This is a hamming code generator
.data
	prompt: .asciiz "Enter an 8 bit unsigned number: "
	ans: .asciiz "The hamming code for this integer is: "
.text
getNum:	
	li $v0, 4 			#print the prompt
	la $a0, prompt
	syscall
	
	li $v0, 5			#get the number from the user
	syscall
	
	add $t0, $zero, $v0		#move the number to a temporary register
	
	blt $v0, 0, getNum		#if the number isn't between 0 and 255 ask for the number again
	bgt $v0, 255, getNum
	
	addi $t9, $zero, 128		#and with 128 to get D1
	and $t1, $t0, $t9
	sll $t1, $t1, 2
	
	addi $t9, $zero, 64		#and with 64 to get D2
	and $t2, $t0, $t9
	sll $t2, $t2, 1			
	 
	addi $t9, $zero, 32		#and with 32 to get D3
	and $t3, $t0, $t9
	sll $t3, $t3, 1	
			
	addi $t9, $zero, 16		#and with 16 to get D4
	and $t4, $t0, $t9			
	sll $t4, $t4, 1	

	addi $t9, $zero, 8		#and with 8 to get D5
	and $t5, $t0, $t9
	
	addi $t9, $zero, 4		#and with 4 to get D6
	and $t6, $t0, $t9  
	
	addi $t9, $zero, 2		#and with 2 to get D7
	and $t7, $t0, $t9
	
	addi $t9, $zero, 1		#and with 1 to get D8 
	and $t8, $t0, $t9
	
	add $s5, $s1, $s2
	add $s5, $s5, $t1	
	add $s5, $s5, $s3
	add $s5, $s5, $t2			
	add $s5, $s5, $t3
	add $s5, $s5, $t4	
	add $s5, $s5, $s4
	add $s5, $s5, $t5
	add $s5, $s5, $t6
	add $s5, $s5, $t7
	add $s5, $s5, $t8

	li $v0, 34
	move $a0, $s5
	syscall
	                
	addi $s6, $zero, 0		#set to zero, these will be used to keep track of if the parit bit should be 1 or 0
	addi $s7, $zero, 0
	addi $t9, $zero, 0
	addi $t0, $zero, 0
	slt $s6, $s6, $t1 		#P1 is 1 if bits 1+3+5+7=an odd number
	slt $s7, $s7, $t3
	slt $t9, $t9, $t5
	slt $t0, $t0, $t7
	xor $s6, $s6, $s7		#check if there is an odd number of ones	
	xor $s7, $t9, $t0
	xor $s6, $s6, $s7
	beq $s6, 0, P2 
	addi $s1, $zero, 2048		 
	
P2:	
	addi $s6, $zero, 0		#set to zero, these will be used to keep track of if the parit bit should be 1 or 0
	addi $s7, $zero, 0
	addi $t9, $zero, 0
	addi $t0, $zero, 0
	slt $s6, $s6, $t1		#P2 is 1 if bits 2+3+6+7=an odd number
	slt $s7, $s7, $t3
	slt $t9, $t9, $t4
	slt $t0, $t0, $t6
	xor $s6, $s6, $s7		#check if there is an odd number of ones	
	xor $s7, $t9, $t0
	xor $s6, $s6, $s7
	beq $s6, 0, P3 	
	addi $s2, $zero, 1024
	
P3:
	addi $s6, $zero, 0		#set to one, these will be used to keep track of if the parit bit should be 1 or 0
	addi $s7, $zero, 0
	addi $t9, $zero, 0
	addi $t0, $zero, 0
	slt $s6, $s6, $t4 		#P3 is 1 if bits 4+5+6+7=an odd number
	slt $s7, $s7, $t5
	slt $t9, $t9, $t6
	slt $t0, $t0, $t7
	xor $s6, $s6, $s7		#check if there is an odd number of ones	
	xor $s7, $t9, $t0
	xor $s6, $s6, $s7
	beq $s6, 0, P4 
	addi $s3, $s3, 256
	
P4:				
	#beq $t8, 0, concat 		#fourth parity bit is 1 if bits 8=an odd number
	addi $s4, $s4, 16	

concat:
	add $s5, $s1, $s2
	add $s5, $s5, $t1	
	add $s5, $s5, $s3
	add $s5, $s5, $t2			
	add $s5, $s5, $t3
	add $s5, $s5, $t4	
	add $s5, $s5, $s4
	add $s5, $s5, $t5
	add $s5, $s5, $t6
	add $s5, $s5, $t7
	add $s5, $s5, $t8

print:
	li $v0, 4 			#code to print the string
	la $a0, ans			#telling the adddress of the string to print
	syscall 
	
	li $v0, 34 			#code to print hex
	move $a0, $s5	
	syscall
