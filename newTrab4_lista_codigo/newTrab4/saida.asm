.text

L0:
	li $t0,1
	move $s1,$t0
	li $v0, 1
	move $a0,$s1
	syscall
	jal L1
	jal L2
	li $t1,4
	move $s2,$t1
	li $v0, 1
	move $a0,$s2
	syscall
	li $v0, 10
	syscall
L1:
	li $t2,2
	move $s3,$t2
	li $v0, 1
	move $a0,$s3
	syscall

	jr $ra
L2:
	li $t3,3
	move $s7,$t3
	li $v0, 1
	move $a0,$s7
	syscall

	jr $ra