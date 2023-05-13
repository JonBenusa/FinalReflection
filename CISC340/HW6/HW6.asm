#Jonathan Bensua
#HW 6

.data
	first: .asciiz "\n(A+B)+C = "
	second: .asciiz "\nA+(B+C) = "
	num1: .float 1e30
	num2: .float -1e30
	num3: .float 1e2
	A: .asciiz "\nA = "
	B: .asciiz "\nB = "
	C: .asciiz "\nC = "
	
.text
	l.s $f0, num1
	l.s $f1, num2
	l.s $f2, num3
	
	li $v0, 4	#print the value of A with a label
	la $a0, A
	syscall
	l.s $f12, num1
	li $v0, 3
	syscall
	
	li $v0, 4	#print the value of A with a label
	la $a0, B
	syscall
	l.s $f12, num2
	li $v0, 3
	syscall
	
	li $v0, 4	#print the value of A with a label
	la $a0, C
	syscall
	l.s $f12, num3
	li $v0, 3
	syscall
	
	add.s $f3, $f0, $f1 	#first combination of additions
	add.s $f12, $f3, $f2
	
	li $v0, 4	#print the results
	la $a0, first
	syscall
	li $v0, 3 
	syscall  
	
	 
	add.s $f3, $f1, $f2	#second combinitions of additions
	add.s $f12, $f3, $f0
	
	li $v0, 4	#print the results
	la $a0, second
	syscall
	li $v0, 3
	syscall 
