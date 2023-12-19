		.data
prompt:		.asciiz "please enter a coordinate: \n"
promptSize:	.asciiz "please enter the number of coordinates: \n"
keyPrompt:	.asciiz "\n please enter a number between 1-9 \n"
plainText:	.space 10
		.text
		la	$t1, plainText				#$t1 has the adress of first element in the array of coordinates.
										#Prompt for how many coordinates
		li	$v0, 4
		la	$a0, promptSize
		syscall
										#syscall for reading user input for number of coordinates
		li	$v0, 5
		syscall
										#storing user input
										#moving the user input to $t0
		move	$t0, $v0
		move	$t4, $v0				#used for key loop and resetting byte position
										#syscall for printing the prompt
userInput:	li 	$v0, 4
		la 	$a0, prompt
		syscall
										#syscall for reading user input
		li 	$v0, 5
		syscall
										#storing user input
		sb 	$v0, 0($t1)
		addi	$t1, $t1, 1				#incrementing address so next iteration of loop will store at the next address
		sub	$t0, $t0, 1					#counter for the loop (number of coordinates)
		bgt	$t0, 0, userInput
		sub 	$t1, $t1, $t4			#resets the byte position to original position
										#Prompting for a key
keyInput:	li 	$v0, 4					#key loop begins
		la 	$a0, keyPrompt
		syscall
										#reading user input
		li 	$v0, 5
		syscall
										#loading data into a separate register
		la	$t2, ($v0)					#number used to add to the bytes
		lb	$t3, 0($t1)					#coordinate from $t1 into $t3 to add
		add	$t3, $t2, $t3 
		sb	$t3, 0($t1)					#stores modified coordinate
		
		addi	$t1, $t1, 1				#incrementing address so next iteration of loop will store at the next address
		sub	$t4, $t4, 1					#counter for the loop (number of coordinates)
		
		li	$v0, 1
		la	$a0, ($t3)					#prints result of modified coordinate
		syscall
		bne	$t4, 0, keyInput			#loop exit condition
		
		#exit
		li $v0, 10
		syscall
		
