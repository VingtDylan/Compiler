.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
read:
  li $v0, 4
  la $a0, _prompt
  syscall
  li $v0, 5
  syscall
  jr $ra

write:
  li $v0,1 
  syscall
  li $v0, 4
  la $a0, _ret
  syscall
  move $v0, $0
  jr $ra

fact:
  move $t0, $a0
  li $t1, 1
  beq $t0, $t1, label1
  j label2
label1:
  move $v0, $t0
  jr $ra
  j label3
label2:
  addi $t2, $t0, -1
  addi $sp, $sp, -8
  sw $ra, 0($sp)
  sw $a0, 4($sp)
  move $a0 $t2
  addi $sp, $sp, -4
  sw $t2, 0($sp)
  addi $sp, $sp, -4
  sw $t0, 0($sp)
  jal fact
  lw $t0, 0($sp)
  addi $sp, $sp, 4
  lw $t2, 0($sp)
  addi $sp, $sp, 4
  lw $a0, 4($sp)
  lw $ra, 0($sp)
  addi $sp, $sp, 8
  move $t3, $v0
  mul $t4, $t0, $t3
  move $v0, $t4
  jr $ra
label3:

main:
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal read
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  move $t0, $v0
  move $t1, $t0
  li $t2, 1
  bgt $t1, $t2, label4
  j label5
label4:
  addi $sp, $sp, -8
  sw $ra, 0($sp)
  sw $a0, 4($sp)
  move $a0 $t1
  addi $sp, $sp, -4
  sw $t1, 0($sp)
  addi $sp, $sp, -4
  sw $t0, 0($sp)
  jal fact
  lw $t0, 0($sp)
  addi $sp, $sp, 4
  lw $t1, 0($sp)
  addi $sp, $sp, 4
  lw $a0, 4($sp)
  lw $ra, 0($sp)
  addi $sp, $sp, 8
  move $t3, $v0
  move $t4, $t3
  j label6
label5:
  li $t4, 1
label6:
  move $a0, $t4
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  move $v0, $0
  jr $ra
