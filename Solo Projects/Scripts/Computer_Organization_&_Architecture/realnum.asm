.data       
array: .space 6   
char: .space 2

prompt: .asciiz "Please input a number, then press ENTER:\n"
errorMessage: .asciiz "Your entry was insufficient\n "

nL: .asciiz "\n"

.text          
	
	la $a0, prompt					#load prompt message into $a0 for syscall
	li $v0, 4						#load syscall to print string
	syscall      
	j read							#call readInt function to get user input string         

gets:								#read multiple chars from keyboard buffer until ENTER key,
									#add NULL char and store into buffer pointed to by *array
									#passed to the subroutine
	la $s1, array					#set base address of array to s1
loop:								#start of read loop
	jal getc						#jump to getc subroutine
	lb $t0, char					#load the char from char buffer into t0, stripping null
	sb $t0, 0($s1)					#store the char into the nth elem of array
	
	jal store
	
	lb $t1, nL						#load newline char into t1
	beq $t0, $t1, done				#end of string?  jump to done
	addi $s1, $s1, 1				#increments base address of array
	add $t7, $t7, 1
	j loop							#jump to start of read loop

getc:								#read char from keyboard buffer and return ascii value
	li $v0, 8						#call code for read string
	la $a0, char					#load address of char for read
	li $a1, 2						#length of string is 1byte char and 1byte for null
	syscall							#store the char byte from input buffer into char
	jr $ra							#jump-register to calling function

read:          						#read string of ascii digits, store into a local variable and  
									#convert into integer, return that int unless string contains 
									#non-integers 
	j gets							#let s1 be top address of array, let s0 be the digitcounter
done:								#let s2 be the sum total
	subi $s1, $s1, 1				#reposition array pointer to last char before newline char
	la $s0, array					#set base address of array to s0 for use as counter
	subi $s0, $s0, 1				#reposition base array to read leftmost char in string
	add $s2, $zero, $zero			#initialize sum to 0
	li $t0, 10    					#set t0 to be 10, used for decimal conversion 
	li $t3, 1
	lb $t1, 0($s1)					#load char from array into t1
	
	#subi $t1, $t1, 48				#converts t1's ascii value to dec value
	#add $s2, $s2, $t1				#add dec value of t1 to sumtotal
	subi $s1, $s1, 1				#decrement array address
lp:									#loop for all digits preceeding the LSB
	mul $t3, $t3, $t0				#multiply power by 10
	beq $s1, $s0, return			#exit if beginning of string is reached
	lb $t1, ($s1)					#load char from array into t1
	
	#subi $t1, $t1, 48				#converts t1's ascii value to dec value
	mul $t1, $t1, $t7				#t1*10^(counter)
	#add $s2, $s2, $t1				#sumtotal=sumtotal+t1
	subi $s1, $s1, 1				#decrement array address
	j lp							#jump to start of loop




end:	
	li $v0, 10						#ends program
	syscall
	
error:								#if non digit chars are entered, displays error message and result returns 0
	la $a0, errorMessage
	li $v0, 4
	syscall
	j end

return:	li $v0, 1
	add $a0, $t1, $zero
	#bgt $a0, 65535, error
	#bltz $a0, error
	syscall 
	j end

store: 
	beq $t0, 46, transfer
	bne $t0, 46, storeB
	
	
transfer:	move  $t5, $t0

storeB:	
	beq $t0, 10, back
	sub $s1, $s1, $t7
	
	move $t4, $t0
	addi $s1, $s1, 1
	add $t8, $t8, 1
	beq $t0, 46, back
	
storeA:
	bnez $t6, back
	move $t6, $t0
	addi $s1, $s1, 1
	beq $s1, 0, back

back: 	jr $ra
