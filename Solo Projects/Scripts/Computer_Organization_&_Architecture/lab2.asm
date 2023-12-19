	.data
hello:	.asciiz "Hello World!"
line:	.asciiz "\n" 


	.text
	li	$v0, 4
	la 	$a0, hello
	syscall
	
	
	la $a0, line
	syscall
	
	
	li $t1, 5
	li $t2, 2
	li $t3, 10
	
	mul $t0, $t2, $t3
	add $t0, $t1, $t0
	sub $t0, $t0, $t2
	
	li $v0, 1
	la $a0, ($t0)
	syscall
	
	move $t0, $zero
	move $t1, $zero
	move $t2, $zero
	move $t3, $zero
	
	
	li	$v0, 4
	la 	$a0, line
	syscall

	
loopUno:	blt $t1, 5, accumulate
accumulate:	add $t3, $t3, 1
		add $t1, $t1, 1
		
loopDos:	blt $t2, 3, accumulateDos
accumulateDos:	add $t3, $t3, 2
		add $t2, $t2, 1
		
		blt $t2, 3, loopDos
		move $t2, $zero
		blt $t1, 5, loopUno
		
		li $v0, 1
		la $a0, ($t3)
		syscall
		
		li $v0, 10
		syscall
		
