.text
	li $v0, 5
	syscall
	move $s1,$v0
	li $v0, 5
	syscall
	move $s2,$v0
	li $t0,1
	bgt $s1,$s2,L1
	li $t0,0
L1:	beq $t0,0,L2
	li $t1,20
	move $s1,$t1
	j L3
L2:	li $t2,10
	move $s1,$t2
L3:	li $v0, 1
	move $a0,$s1
	syscall
	li $v0,11
	li $a0,'\n'
	syscall
