.text
main:
    addi $s0, $zero, 0
   	addi $t0, $zero, 5
	  addi $t1, $zero, 10
    addi $t2, $zero, 4

	  add $s0, $t0, $t1
    add $s1, $s0, $t2

    li $v0, 10 # terminate program
    syscall
.end
