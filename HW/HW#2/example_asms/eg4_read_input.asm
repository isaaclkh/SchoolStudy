.data
buffer: .space 20
str1: .asciiz "Enter string(max 20 chars): "
str2: .asciiz "You wrote:\n"

.text
.globl main

main:
   la $a0, str1   # print str1
   li $v0, 4
   syscall

   li $v0, 8      # read a string
   la $a0, buffer
   syscall

   la $a0, str2   # print str2
   li $v0, 4
   syscall

   la $a0, buffer # print the input string 
   li $v0, 4
   syscall

   li $v0, 10
   syscall
