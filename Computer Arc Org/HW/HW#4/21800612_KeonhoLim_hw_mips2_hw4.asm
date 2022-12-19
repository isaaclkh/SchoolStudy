.data
matrixA:   .float 1.5, -1.2, 2.3, -2.8, 0.7, 3.9, 1.3, 1.3, 1.4, 1.0, 0.5, -1.2, 1.2, -2.1, 1.8
vectorX:   .float 3.2, -1.5, 1.1 # 3 dimension
vectorB:   .float 0.3, -0.5, 1.3, -2.1, 0.1 # 5 dimension
shapeA:    .word 5, 3 # matrix size is 5 x 3
str1: .asciiz "\nshape\n"
str2: .asciiz "\nmatrix elements at (0,0) and (0,1)\n"
space: .asciiz " "
to: .asciiz "to"
open: .asciiz "("
close: .asciiz ")"

.text

main:

  # print the values of y,
  # where y = max(0, matrixA * vectorX + vectorB)
  # $s0 = shapeA, $s1 = matrixA

  li $v0, 4 # system call code for printing string = 4
  la $a0, str1
  syscall # call operating system to perform operation

  # printing shape
  li $v0, 1
  la $s0, shapeA
  lw $a0, 0($s0)
  syscall

  li $v0, 4 # system call code for printing string = 4
  la $a0, space
  syscall # call operating system to perform operation

  li $v0, 1
  lw $a0, 4($s0)
  syscall

  li $v0, 4 # system call code for printing string = 4
  la $a0, str2
  syscall # call operating system to perform operation

  # printing the first two elements
  li $v0, 2
  la $s1, matrixA
  lwc1 $f12, 0($s1)
  syscall

  li $v0, 4 # system call code for printing string = 4
  la $a0, space
  syscall # call operating system to perform operation

  li $v0, 2
  lwc1 $f12, 4($s1)
  syscall

  #shape
  #5 3
  #matrix elements at (0,0) and (0,1)
  #1.50000000 -1.20000005

  la $a0, vectorB
  la $a1, matrixA
  la $a2, vectorX

  #여기까지 skeleton
  #li $t1, 32               # $t1 = 32 (row size/loop end)
  lw $t1, 0($s0)            # $t1 = 5
  lw $t5, 4($s0)            # $t5 = 3
  li $s0, 0                 # i = 0; initialize 1st for loop

L1: li $s1, 0             # j = 0; restart 2nd for loop

L2: li $s2, 0             # k = 0; restart 3rd for loop
    #sll $t2, $s0, 5      # $t2 = i * 32 (size of row of x)
    mul $t2, $s0, $t1
    addu $t2, $t2, $s1    # $t2 = i * size(row) + j
    sll $t2, $t2, 3       # $t2 = byte offset of [i][j]
    addu $t2, $a0, $t2    # $t2 = byte address of x[i][j]
    l.d $f4, 0($t2)       # $f4 = 8 bytes of x[i][j]

L3: #sll $t0, $s2, 5       # $t0 = k * 32 (size of row of z)
    mul $t0, $s2, $t5
    addu $t0, $t0, $s1    # $t0 = k * size(row) + j
    sll $t0, $t0, 3       # $t0 = byte offset of [k][j]
    addu $t0, $a2, $t0    # $t0 = byte address of z[k][j]
    l.d $f16, 0($t0)      # $f16 = 8 bytes of z[k][j]

    #sll $t0, $s0, 5       # $t0 = i*32 (size of row of y)
    mul $t0, $s0, $t1
    addu $t0, $t0, $s2    # $t0 = i*size(row) + k
    sll $t0, $t0, 3       # $t0 = byte offset of [i][k]
    addu $t0, $a1, $t0    # $t0 = byte address of y[i][k]
    l.d $f18, 0($t0)      # $f18 = 8 bytes of y[i][k]

    mul.d $f16, $f18, $f16  # $f16 = y[i][k] * z[k][j]
    add.d $f4, $f4, $f16    # $f4=x[i][j] + y[i][k]*z[k][j]

    addiu $s2, $s2, 1     # k = k + 1
    bne $s2, $t5, L3      # if (k != 32) go to L3
    s.d $f4, 0($t2)       # x[i][j] = $f4

    addiu $s1, $s1, 1     # j = j + 1
    #bne $s1, $t1, L2      # if (j != 32) go to L2
    move $t6, $zero
    addi $t6, $t6, 1
    bne $s1, $t6, L2

    addiu $s0, $s0, 1     # i = i + 1
    bne $s0, $t1, L1      # if (i != 32) go to L1

    move $t7, $zero
    addi $t7, $t7, 1

show1: slt $t6, $t1, $t7
       bne $t6, $zero, printClosepar

       sll $t4, $t7, 2
       add $t4, $t4, $a0
       lw $t3, 0($t4)

       li $v0, 4
       la $a0, open
       syscall

       move $a3, $t3
       li $v0, 1
       syscall

       li $v0, 4
       la $a0, space
       syscall

printClosepar: li $v0, 4
               la $a0, close
               syscall

               li $v0, 4
               la $a0, to
               syscall

               move $t7, $zero
               addi $t7, $t7, 1

               li $v0, 4
               la $a0, open
               syscall

               j show2

show2: slt $t6, $t1, $t7
       bne $t6, $zero, exit

       sll $t4, $t7, 3
       add $t4, $t4, $a0
       lw $t3, 0($t4)

       slt $t2, $zero, $t3
       bne $t2, $zero, print
       move $t3, $zero
       j print

print: move $a3, $t3
       li $v0, 1
       syscall

       li $v0, 4
       la $a0, space
       syscall

       j show2

exit: li $v0, 4
      la $a0, close
      syscall

      li $v0, 10
      syscall

.end
