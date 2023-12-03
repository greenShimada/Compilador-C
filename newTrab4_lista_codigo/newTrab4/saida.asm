.text
L0:
	li $t0,10
	move $s1,$t0
	li $t1,30
	move $s2,$t1
	li $v0, 1
	move $a0,$s1
	syscall
	li $v0,11
	li $a0,'\n'
	syscall
	li $v0, 1
	move $a0,$s2
	syscall
	li $v0,11
	li $a0,'\n'
	syscall
	li $v0, 10
	syscallL1:
	li $t2,20
	move $s3,$t2
	li $v0, 1
	move $a0,$s3
	syscall
	li $v0,11
	li $a0,'\n'
	syscall
	li $v0, 10
	syscall