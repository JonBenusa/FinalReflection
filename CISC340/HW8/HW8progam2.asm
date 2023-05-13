#Jonathan Benusa
#HW 8 This takes a integer with a hamming code and checks if the hamming code is correct
.data
	prompt: .asciiz "Enter an 12 bit unsigned number: "
	ans: .asciiz "The hamming code for this integer is: "
	incorPrompt: .asciiz "The hamming code was incorrect for this integer. The correct code should be: "
	
.text
getNum:	
	li $v0, 4 		#print the prompt
	la $a0, prompt
	syscall
	
	li $v0, 5		#get the number from the user
	syscall
	
	add $t0, $zero, $v0	#move the number to a temporary register
	add $s7, $zero, $t0	#set $s5 to input 
	
	addi $t9, $zero, 2	#add 2 to t9 so it can be used to divide
	
	blt $v0, 0, getNum	#if the number isn't between 0 and 255 ask for the number again
	bgt $v0, 4095, getNum


bit8:		
	div $t0, $t9		#divide the remainder will be the least significant bit
	mfhi $t8 		# remainder to $t3 This is bit 8
	mflo $t0			# quotient 
bit7:	
	div $t0, $t9		#divide the remainder will be the least significant bit
	mfhi $t7 		# remainder to $t3 This is bit 7
	mflo $t0			# quotient 
bit6:	
	div $t0, $t9		#divide the remainder will be the least significant bit
	mfhi $t6 		# remainder to $t3 This is bit 6
	mflo $t0			# quotient 
bit5:	
	div $t0, $t9		#divide the remainder will be the least significant bit
	mfhi $t5 		# remainder to $t3 This is bit 5
	mflo $t0			# quotient 
par4:
	div $t0, $t9		#divide the remainder will be the least significant bit
	mfhi $s4 		# remainder to $t3 This is bit 1
	mflo $t0			# quotient		
bit4:	
	div $t0, $t9		#divide the remainder will be the least significant bit
	mfhi $t4 		# remainder to $t3 This is bit 4
	mflo $t0			# quotient 
bit3:	
	div $t0, $t9		#divide the remainder will be the least significant bit
	mfhi $t3 		# remainder to $t3 This is bit 3
	mflo $t0			# quotient 
bit2:	
	div $t0, $t9		#divide the remainder will be the least significant bit
	mfhi $t2 		# remainder to $t3 This is bit 2
	mflo $t0			# quotient
par3:
	div $t0, $t9		#divide the remainder will be the least significant bit
	mfhi $s3 		# remainder to $t3 This is bit 1
	mflo $t0			# quotient	 
bit1:	
	div $t0, $t9		#divide the remainder will be the least significant bit
	mfhi $t1 		# remainder to $t3 This is bit 1
	mflo $t0			# quotient
par2:
	div $t0, $t9		#divide the remainder will be the least significant bit
	mfhi $s2 		# remainder to $t3 This is bit 1
	mflo $t0			# quotient
par1:	
	div $t0, $t9		#divide the remainder will be the least significant bit
	mfhi $s1 		# remainder to $t3 This is bit 1
	mflo $t0			# quotient
	
	addi $t0, $zero, 2	#t0 gets 2
	addi $s5, $zero, 0	#this gets 0, it will be used to track which parity bits are wrong

	add $t9, $t1, $t3	#parity bit one should be 1 if bits 1+3+5+7 = an odd number
	add $t9, $t9, $t5
	add $t9, $t9, $t7
	div $t9, $t0
	mfhi $s0			#the remainder. if it is one than the first parity bit should be activated
	beq $s0, $s1, P2		#if parity bit is not equal to $s0 then the hammel code is incorrect
	addi $s5, $s5, 8
P2:
	add $t9, $t2, $t3		#parity bit one should be 2 if bits 2+3+6+7 = an odd number
	add $t9, $t9, $t6
	add $t9, $t9, $t7
	div $t9, $t0
	mfhi $s0			#the remainder. if it is one than the first parity bit should be activated
	beq $s0, $s2, P3		#if parity bit is not equal to $s2 then the hammel code is incorrect
	addi $s5, $s5, 4
P3:
	add $t9, $t4, $t5		#parity bit one should be 1 if bits 4+5+6+7 = an odd number
	add $t9, $t9, $t6
	add $t9, $t9, $t7
	div $t9, $t0
	mfhi $s0			#the remainder. if it is one than the first parity bit should be activated
	beq $s0, $s3, P4		#if parity bit is not equal to $s3 then the hammel code is incorrect
	addi $s5, $s5, 2
P4:	
	div $t8, $t0
	mfhi $s0			#the remainder. if it is one than the first parity bit should be activated
	beq $s0, $s4, Check		#if parity bit is not equal to $s5 then the hammel code is incorrect
	addi $s5, $s5, 1
	
Check:		
	bne $s5, 0, incorrect		#if s5 is anything besides 0 then one or more of the bits are wrong
												
	li $v0, 4 			#code to print the string
	la $a0, ans			#telling the adddress of the string to print
	syscall 
	li $v0, 34 			#code to print hex
	move $a0, $s7	
	syscall
	li $v0, 10        		# Load exit code
        syscall              		# Exit
        
incorrect:
	addi $s7, $zero, 0		#reset to 0
	
	beq $s5, 1, eight			#figure out based on s5 which bit to flip
	beq $s5, 2, four
	beq $s5, 3, fourEight
	beq $s5, 4, two
	beq $s5, 5, twoEight
	beq $s5, 6, six
	beq $s5, 7, sixEight
	beq $s5, 8, one
	beq $s5, 9, oneEight
	beq $s5, 10, five
	beq $s5, 11, fiveEight
	beq $s5, 12, three
	beq $s5, 13, threeEight
	beq $s5, 14, seven
	beq $s5, 15, sevenEight

one:					#flip the incorrect bit		
	seq $t1,$t1, $zero		#if it is equal to 0 flip to one, otherwise flip to 0 	
	j print
oneEight:					#flip the incorrect bit		
	seq $t1,$t1, $zero		#if it is equal to 0 flip to one, otherwise flip to 0 	
	seq $t8,$t8, $zero
	j print	
two:
	seq $t2,$t2, $zero		#if it is equal to 0 flip to one, otherwise flip to 0
	j print
twoEight:
	seq $t2,$t2, $zero		#if it is equal to 0 flip to one, otherwise flip to 0
	seq $t8,$t8, $zero
	j print	
three:
	seq $t3,$t3, $zero		#if it is equal to 0 flip to one, otherwise flip to 0
	j print
threeEight:
	seq $t3,$t3, $zero		#if it is equal to 0 flip to one, otherwise flip to 0
	seq $t8,$t8, $zero
	j print	
four:
	seq $t4,$t4, $zero		#if it is equal to 0 flip to one, otherwise flip to 0
	j print
fourEight:
	seq $t4,$t4, $zero		#if it is equal to 0 flip to one, otherwise flip to 0
	seq $t8,$t8, $zero
	j print	
five:
	seq $t5,$t5, $zero		#if it is equal to 0 flip to one, otherwise flip to 0
	j print
fiveEight:
	seq $t5,$t5, $zero		#if it is equal to 0 flip to one, otherwise flip to 0
	seq $t8,$t8, $zero
	j print	
six:
	seq $t6,$t6, $zero		#if it is equal to 0 flip to one, otherwise flip to 0
	j print
sixEight:
	seq $t6,$t6, $zero		#if it is equal to 0 flip to one, otherwise flip to 0
	seq $t8,$t8, $zero
	j print	
seven:
	seq $t7,$t7, $zero		#if it is equal to 0 flip to one, otherwise flip to 0
	j print
sevenEight:
	seq $t7,$t7, $zero		#if it is equal to 0 flip to one, otherwise flip to 0
	seq $t8,$t8, $zero
	j print	
eight:
	seq $t8,$t8, $zero		#if it is equal to 0 flip to one, otherwise flip to 0
	j print
	
print:
	bne $t8, 1, fin7
	addi $s7, $zero, 1
fin7:
	bne $t7, 1, fin6
	addi $s7, $s7, 2
fin6:
	bne $t6, 1, fin5
	addi $s7, $s7, 4
fin5:
	bne $t5, 1, finP4
	addi $s7, $s7, 8
finP4:
	bne $s4, 1, fin4
	addi $s7, $s7, 16
fin4:
	bne $t4, 1, fin3
	addi $s7, $s7, 32
fin3:
	bne $t3, 1, fin2
	addi $s7, $s7, 64
fin2:
	bne $t2, 1, finP3
	addi $s7, $s7, 128
finP3:	
	bne $s3, 1, fin1
	addi $s7, $s7, 256
fin1:
	bne $t1, 1, finP2
	addi $s7, $s7, 512
finP2:	
	bne $s2, 1, finP1
	addi $s7, $s7, 1024
finP1:	
	bne $s1, 1, final
	addi $s7, $s7, 2048		
	
final:	
	li $v0, 4 		#code to print the string
	la $a0, incorPrompt	#telling the adddress of the string to print
	syscall 
	li $v0, 34 		#code to print hex
	move $a0, $s7	
	syscall
	li $v0, 10        # Load exit code
        syscall              # Exit
			
