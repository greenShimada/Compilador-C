.text

L2:
	li $t0,1
	move $s1,$t0
	jal L0
	jal L1
	li $t1,4
	move $s2,$t1
	li $v0, 1
	move $a0,$s2
	syscall
	li $v0, 10
	syscall
L3:
	li $t2,3
	move $s7,$t2
	li $v0, 1
	move $a0,$s7
	syscall

	jr $ra
L4:
	li $t3,2
	move $s3,$t3
	li $v0, 1
	move $a0,$s3
	syscall

	jr $ra