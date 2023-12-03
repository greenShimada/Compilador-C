.text

L0:
	li $t0,11
	move $s1,$t0
	li $t1,5
	move $s2,$t1
	jal L3
WHILE1:
	li $t2,1
	bgt $s1,$s2,L1
	li $t2,0
L1:	beq $t2, 0, END_WHILE3
	li $v0, 1
	move $a0,$s2
	syscall
	li $v0,11
	li $a0,'\n'
	syscall
	li $t3,1
	add $t4,$s2,$t3
	move $s2,$t4
j WHILE1
END_WHILE3:
	jal L3
	li $v0, 10
	syscall
L3:
	li $t5,68
	move $s4,$t5
	li $v0, 1
	move $a0,$s4
	syscall
	li $v0,11
	li $a0,'\n'
	syscall

	jr $ra