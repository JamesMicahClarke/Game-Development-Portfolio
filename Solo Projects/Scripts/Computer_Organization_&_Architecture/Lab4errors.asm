#########################################################################################
#The .data section is memory that is allocated in the data segment of memory 		#
#Include the following in this section.  						#
#Use the .space directive to allocate several things:					#
#	space for user input								#
#Use .asciiz directive to create several things (not limited to):			#
#	a user prompt									#
#	a user notification of the legnth of their entry				#
#########################################################################################
	.data	
prompt:		.asciiz "Enter a string: "
buffer:		.space 256
#########################################################################################
#The .text section is executed at runtime.						#
#Include the following in this section.  						#	
#Ask user for a string input.								#
#Call the stringLen by using the jal instruction and the appropriate label.		#
#	use caller/callee convention							#
#	pass any argument(s) by placing them in the $a0-$a3 registers			#
#	#read any return values by looking in $v0-$v1 after calling the function	#
#Print out the length of the user input.						#					#
#Exit syscall										#
#########################################################################################
		.text
		li $v0, 4
		la $a0, prompt			#prints prompt
		syscall
		li $v0, 8				#read string syscall
		la $a0, buffer
		li $a1, 256				#max amount of characters allowed in string
		syscall

		jal StringLen
								#print out the results of stringlenth
		move $a0, $v1			#getting the result of the StringLen function from $v1 to $a0
		li $v0, 1
		syscall
		j exit
		
								#function to figure out string length
StringLen: 	move $t0, $a0		#moves address (from $a0 to $t0) that was passed in from the main part of the program
		li $t1, 0				 #counter for number of characters. Set to 0
		
loop:		lb $t2, 0($t0)		#loads the first byte of the word into $t2
		addiu $t0, $t0, 1		#increments the memory address by one
		addiu $t1, $t1, 1		#adds 1 to the counter
		beq $t2, 0, done		#if the current byte is a null space, go to exit
		j loop 
		

done:	blt $t1, $a1, reduce	#checks if $t1 equals the max chars for the string and sends to remove the null

moveAhead:	move $v1, $t1		#moves the result of counter to $v1 so the main part of the program can "see" it

		jr $ra					#jumps back to line 35
		
exit:		li $v0, 10			#exit the program
		syscall
		
reduce:		sub $t1, $t1, 2		#skims off the extra count from the newline and null if max chars are not reached for count accuracy
		j moveAhead