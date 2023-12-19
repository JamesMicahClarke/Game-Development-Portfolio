.data
allocate: .space 4
allocateB: .space 4
allocateC: .space 4
symbols:   .space 256
prompt:	 .asciiz "Please enter 4 single digit coordinates with the following format: 1,2;3,4;5,6;7,8\n"
promptB: .asciiz "Enter your translation value x\n"
promptC: .asciiz "Enter your translation value y\n"
line:	.asciiz "\n"

.text
	la $a0, prompt
	li $v0, 4
	syscall	#prompt
	
	li $v0, 8
	la $a0, allocate
	li $a1, 23
	syscall						#user input
	move $t0, $a0				#allocates space for user input to be kept
	
	la $a0, promptB
	li $v0, 4
	syscall						#prompt for translations
	
	li $v0, 5
	syscall
	move $s1, $v0
	
	la $a0, promptC
	li $v0, 4
	syscall
	
	li $v0, 5
	syscall
	move $s2, $v0
	
	la $t4, allocateB
	la $t5, allocateC
	la $t6, symbols
	li $t3, 0
	
loop:							#loads numbers into t2
	lb $t2, 0($t0)
	beq $t2, 0, resetCount
	blt $t2, 48, storeOther
	bgt $t2, 57, storeOther
	
	add $t3, $t3, 1
	addiu $t0, $t0, 1
	bnez $t2, store
	
done:							#once all values are in place, it's time to sort the Y values. shifts the address space of t4 by 2 spaces
	addiu $t4, $t4, 1
	add $t3, $t3, 1
	beq $t3, 2, load
	j done
load:							#sorts the Y values into t5
	move $t3, $zero
	lb $t7, 20($t4)
	sb $t7, 59($t5)
	addiu $t5, $t5, 1
	beq $t7, 0, check
	j done
	
end:	li $v0, 10
	syscall
	
store:							#decides which value goes where
	beq $t2, 48, storeZero
	beq $t2, 49, storeOne
	beq $t2, 50, storeTwo
	beq $t2, 51, storeThree
	beq $t2, 52, storeFour
	beq $t2, 53, storeFive
	beq $t2, 54, storeSix
	beq $t2, 55, storeSeven
	beq $t2, 56, storeEight
	beq $t2, 57, storeNine
	
storeZero: 
	sb $t2, 28($t4)
	addiu $t4, $t4, 1
	j loop	
	
	
storeOne:
	sb $t2, 28($t4)
	addiu $t4, $t4, 1
	j loop	
	
storeTwo:
	sb $t2, 28($t4)
	addiu $t4, $t4, 1
	j loop	
	
storeThree:
	sb $t2, 28($t4)
	addiu $t4, $t4, 1
	j loop	
	
storeFour:
	sb $t2, 28($t4)
	addiu $t4, $t4, 1
	j loop	
	
storeFive:
	sb $t2, 28($t4)
	addiu $t4, $t4, 1
	j loop	
	
storeSix:
	sb $t2, 28($t4)
	addiu $t4, $t4, 1
	j loop	
	
storeSeven:
	sb $t2, 28($t4)
	addiu $t4, $t4, 1
	j loop		
	
storeEight:	
	sb $t2, 28($t4)
	addiu $t4, $t4, 1
	j loop	
	
storeNine:
	sb $t2, 28($t4)
	addiu $t4, $t4, 1
	j loop	

storeOther:
	sb $t6, 96($t4)
	addiu $t0, $t0, 1
	add $t3, $t3, 1
	j loop
	

check:							#checks to see if t4's address is not right here
	lb $t8, ($t4)
	beq $t8, 0, correct

prints:							#prints out each stored X value into 32 bit binary	
	lb $a0, ($t4)
	beq $a0, 0, printsTwo
	sub $a0, $a0, 48
	addiu $t4, $t4, 1
	li $v0, 35
	syscall
	beq $a0, 0, printsTwo
	j prints
	
printsTwo:						#prints out each stored Y value into 32 bit binary
	lb $a0, 62($t5)
	beq $a0, 0, end
	sub $a0, $a0, 48
	addiu $t5, $t5, 1
	li $v0, 35
	syscall
	beq $a0, 0, end
	j printsTwo

resetCount: li $t3, 1			#used to reset the count to 1 to prevent skipping the first X value
	j done
	
correct: bne $t4, 268501024, change
change:	li $t4, 268501024				#corrects the adress before printing the X values
	j prints

bin:							#used for testing
	li $t0, 1
	sll $t0, $t0, 24
	move $a0, $t0
	li $v0, 35
	syscall
	j end

	
