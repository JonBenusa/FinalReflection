#Jonathan Benusa
#HW 9 this program ca;culates the maximum speed up for a number of processors
.data
prompt: .asciiz "Enter the number of processors:"
prompt2: .asciiz "Enter the percent that is sequential:"
one: .float 1.0
hundred: .float 100.0

.text
getNum:
	li $v0, 4		#print the prompt
	la $a0, prompt
	syscall
	li $v0, 5		#get the number of processers from the user
	syscall
	blt $v0, 0, getNum	#if the number is negative ask again
	beq $v0, 0, end		#if the number is equal to 0 end the program
	
	move $a1, $v0		#move to $a1 and converet to a float
	mtc1 $a1, $f0
  	cvt.s.w $f0, $f0

getPer:		
	li $v0, 4		#print the prompt
	la $a0, prompt2
	syscall
	li $v0, 5		#get the number of percent serial from the user
	syscall
	blt $v0, 1, getPer 	#number must be between 1 and 99
	bgt $v0, 99, getPer	
	
	move $a1, $v0		#move to $a1 and converet to a float
	mtc1 $a1, $f1
  	cvt.s.w $f1, $f1
	
	l.s $f2, one 		#set equal to 1.0
	l.s $f3, hundred		#set equal to 100.0
	
	sub.s $f4, $f3, $f1	#part parallel
	div.s $f4, $f4, $f3	#make a percent
	div.s $f1, $f1, $f3	#make a percent
	
	div.s $f5, $f4, $f0	#percent parallel/number of processors = $f5
	
	add.s $f6, $f5, $f1	
	
	div.s $f12, $f2, $f6	#1.o/preveious answer is the speedup
	
	li $v0, 2		#code to print a float
	syscall					

end:
	li $v0, 10 		#code to end the program
	syscall