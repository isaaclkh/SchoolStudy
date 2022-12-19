.data
  digit:   .word 10, 12, 23, 28, 7, 39, 10, 11, 23, 12, 3, 4, 5, 1, 34, 17, 0, 5, 24
  length:  .word 19 # the length of the digit list\

  str1: .asciiz "Enter the menu (s= sum, x= max, n: min, q: quit): "
  str2: .asciiz "\nThe sum is "
  str3: .asciiz "\nMax is "
  str4: .asciiz "\nMin is "
  str5: .asciiz "\nMenu q selected\nProcess finished\n"
  newLine: .asciiz "\n"


.text
.globl main

main:

# HERE, implement mips code
# to get the sum, max, and min of the ‘digit’ list above
# and to print the results (sum, max, and min)

# the printing format should be as follows:
# sum is xxx
# max is yyy
# min is zzz

    la $a0, str1
    li $v0, 4
    syscall

    li $v0, 12
    syscall

    move $s0, $v0

    bne $s0, 'q', loop

    la $a0, str5
    li $v0, 4
    syscall

    li $v0, 10
    syscall

loop:
    move $t0, $zero
    move $s1, $zero

    la $s2, digit
    la $t1, length
    lw $t1, 0($t1)

    beq $s0, 's', sum
    beq $s0, 'x', readyMax
    beq $s0, 'n', readyMin

sum:
    beq $s1, $t1, printSum
    sll $t3, $s1, 2

    add $t3, $t3, $s2
    lw $t4, 0($t3)

    add $t0, $t0, $t4
    addi $s1, $s1 , 1

    j sum

readyMax:
    add $t0, $zero, $zero
    j max

max:
    beq $s1, $t1, printMax
    sll $t3, $s1, 2

    add $t3, $t3, $s2
    lw $t4, 0($t3)

    slt $s3, $t0, $t4
    bne $s3, $zero, answerMax

movingMax:
    addi $s1, $s1 , 1
    j max

answerMax:
    move $t0, $t4
    j movingMax

readyMin:
    addi $t0, $zero, 50
    j min

min:
    beq $s1, $t1, printMin
    sll $t3, $s1, 2

    add $t3, $t3, $s2
    lw $t4, 0($t3)

    slt $s3, $t4, $t0
    bne $s3, $zero, answerMin

movingMin:
    addi $s1, $s1, 1
    j min

answerMin:
    move $t0, $t4
    j movingMin

printSum:
    li $v0, 4
    la $a0, str2
    syscall

    move $a0, $t0
    li $v0, 1
    syscall

    li $v0, 4
    la $a0, newLine
    syscall

    j main

printMax:
    li $v0, 4
    la $a0, str3
    syscall

    move $a0, $t0
    li $v0, 1
    syscall

    li $v0, 4
    la $a0, newLine
    syscall

    j main

printMin:
    li $v0, 4
    la $a0, str4
    syscall

    move $a0, $t0
    li $v0, 1
    syscall

    li $v0, 4
    la $a0, newLine
    syscall

    j main


.end
