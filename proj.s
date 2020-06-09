.data
.globl loch
.globl loch1
.globl loch2
.globl mul

vala: .space 4
valb: .space 4
retV: .space 4
sizea: .space 4
sizeb: .space 4

.text

mul:
	push %ebp
	mov %esp, %ebp

	movl 8(%ebp), %eax
	movl %eax, vala
#	movl 12(%ebp), %eax
#	movl %eax, valb
#	movl 16(%ebp), %eax
#	movl %eax, retV
	movl 20(%ebp), %eax
	movl %eax, sizea
	movl 24(%ebp), %eax
	movl %eax, sizeb

	xor %edi, %edi # indeks zewnetrznej petli (iteracja po A)

	loopA: 		
		xor %ecx, %ecx  # indeks wewnetrznej petli (iteracja po B)
		movl 12(%ebp), %eax
		movl %eax, valb

		loopB:
#obliczenie adresu wyniku czastkowego			
			movl $4, %eax
			movl 16(%ebp), %ebx			
			movl %ecx, %edx
			mull %edx
			addl %eax, %ebx
			movl $4, %eax
			movl %edi, %edx
			mull %edx 
			addl %eax, %ebx
			movl %ebx, retV
#mnożenie
			movl vala, %eax
			movl (%eax), %eax
			movl valb, %edx
			movl (%edx), %edx
			mull %edx
#dodawanie młodszej częsci
			movl retV, %ebx
			movl (%ebx), %ebx
			addl %ebx, %eax 
			movl retV, %ebx
			movl %eax, (%ebx)
# przesuniecie na starszą o 1 pozycję (za pomoca inc aby nie zaburzyć CF)
			incl retV 
			incl retV 
			incl retV
			incl retV 
#dodawanie starszej częsci
			movl retV, %ebx
			movl (%ebx), %eax
			adcl %eax, %edx
			#movl retV, %ebx
			movl %edx, (%ebx)
#dodawanie ew. przeniesienia ze starszej części
			curry:
				jnc  curryEaten
				#addl $4, retV
				addl $4, %ebx
				#movl retV, %ebx
				movl (%ebx), %eax
				addl $1, %eax
				movl %eax, (%ebx)
				jmp curry
#przywrócenie wartości retV
			curryEaten:

			inc %ecx
			cmp sizeb, %ecx
			je endB

			addl $4, valb

			jmp loopB

		endB:

	
		inc %edi 
		cmp sizea, %edi
		je endA

		addl $4, vala

		jmp loopA

	endA:

	mov %ebp, %esp
	pop %ebp
ret
