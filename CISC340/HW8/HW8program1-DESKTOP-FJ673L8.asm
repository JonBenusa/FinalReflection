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
	add $s1, $zero, $t0		#set $s1 to 0 
	
	blt $v0, 0, getNum		#if the number isn't between 0 and 255 ask for the number again
	bgt $v0, 255, getNum
	
	addi $t9, $zero, 2		#add 2 to t9 so it can be used to divide

bit8:	
	div $t0, $t9			#divide the remainder will be the least significant bit
	mfhi $t8 			# remainder to $t3 This is bit 8
	mflo $t0			# quotient 
bit7:	
	div $t0, $t9			#divide the remainder will be the least significant bit
	mfhi $t7 			# remainder to $t3 This is bit 7
	mflo $t0			# quotient 
bit6:	
	div $t0, $t9			#divide the remainder will be the least significant bit
	mfhi $t6 			# remainder to $t3 This is bit 6
	mflo $t0			# quotient 
bit5:	
	div $t0, $t9			#divide the remainder will be the least significant bit
	mfhi $t5 			# remainder to $t3 This is bit 5
	mflo $t0			# quotient 
bit4:	
	div $t0, $t9			#divide the remainder will be the least significant bit
	mfhi $t4 			# remainder to $t3 This is bit 4
	mflo $t0			# quotient 
bit3:	
	div $t0, $t9			#divide the remainder will be the least significant bit
	mfhi $t3 			# remainder to $t3 This is bit 3
	mflo $t0			# quotient 
bit2:	
	div $t0, $t9			#divide the remainder will be the least significant bit
	mfhi $t2 			# remainder to $t3 This is bit 2
	mflo $t0			# quotient 
bit1:	
	div $t0, $t9			#divide the remainder will be the least significant bit
	mfhi $t1 			# remainder to $t3 This is bit 1
	mflo $t0			# quotient
	
	addi $t9, $zero, 0		#reset t9 to 0
	addi $t0, $zero, 2		#to now gets 2
	addi $s1, $zero, 0		#set to 0
first:	
	add $t9, $t1, $t3		#first parity bit is 1 if bits 1+3+5+7=an odd number
	add $t9, $t9, $t5
	add $t9, $t9, $t7
	div $t9, $t0
	mfhi $s0			#the remainder. if it is one than the first parity bit should be activated
	beq $s0, 0, second
	
	addi $s1, $s1, 2048
	
second:	
	addi $t9, $zero, 0		#reset t9 to 0
	add $t9, $t2, $t3		#second parity bit is 1 if bits 2+3+6+7=an odd number
	add $t9, $t9, $t6
	add $t9, $t9, $t7
	div $t9, $t0
	mfhi $s0			#the remainder. if it is one than the first parity bit should be activated
	beq $s0, 0, D1
	
	addi $s1, $s1, 1024

D1:	
	bne $t1, 1, third		#if the first data bit is a zero skip to find the third parity bit	
	addi $s1, $s1, 512		#add 512 so that digit will have a one
third:
	addi $t9, $zero, 0		#reset t9 to 0
	add $t9, $t4, $t5		#third parity bit is 1 if bits 4+5+6+7=an odd number
	add $t9, $t9, $t6
	add $t9, $t9, $t7
	div $t9, $t0
	mfhi $s0			#the remainder. if it is one than the first parity bit should be activated
	beq $s0, 0, D2

	addi $s1, $s1, 256
D2:
	bne $t2, 1, D3			#if the 2nd data bit is a zero skip	
	addi $s1, $s1, 128		#add 512 so that digit will have a one
D3:
	bne $t3, 1, D4			#if the 36rd data bit is a zero skip	
	addi $s1, $s1,64 		#add 512 so that digit will have a one
D4:
	bne $t4, 1, fourth		#if the 2nd data bit is a zero skip	
	addi $s1, $s1,32 		#add 512 so that digit will have a one
fourth:		
	addi $t9, $t8, 0		#fourth parity bit is 1 if bits 8=an odd number
	beq $t9, 0, D5
	addi $s1, $s1, 16
D5:	
	bne $t5, 1, D6			#if the 5th data bit is a zero skip	
	addi $s1, $s1,8 		#add 512 so that digit will have a one
D6:
	bne $t6, 1, D7			#if the 5th data bit is a zero skip	
	addi $s1, $s1,4 		#add 512 so that digit will have a one
D7:
	bne $t7, 1, D8			#if the 5th data bit is a zero skip	
	addi $s1, $s1,2 		#add 512 so that digit will have a one
D8:
	bne $t8, 1, print		#if the 5th data bit is a zero skip	
	addi $s1, $s1,1 		#add 512 so that digit will have a one
print:
	li $v0, 4 			#code to print the string
	la $a0, ans			#telling the adddress of the string to print
	syscall 
	
	li $v0, 34 			#code to print hex
	move $a0, $s1	
	syscall
