.text

L0:
	li $t0,11
	move $s1,$t0
	jal L3
	li $v0, 10
	syscall
L3:
	li $t1,10
	move $s4,$t1
	li $v0, 1
	move $a0,$s4
	syscall

	jr $ra