.data
digit:
   .word 10, 12, 23, 28
str:
   .asciiz " \n"
.text
main:
  la $s1, digit
  lw $t0, 0($s1)     # t0 = 10
  lw $t1, 4($s1)     # t1 = 12
  lw $t2, 8($s1)     # t2 = 23
  lw $t3, 12($s1)    # t3 = 28

  addi $t4, $t0, 5   # t4 = 15
  sw  $t4, 20($s1)

  lw $t0, 20($s1)    # t0 = 15

  li $v0, 1
  add $a0, $t0, $t1  # a0 = 27
  syscall

  li $v0, 4
  la $a0, str        # print new line
  syscall

  li $v0, 1
  sub $a0, $t2, $t3  # a0 = -5
  syscall
.end
