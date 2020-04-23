	.file	"cpu.cpp"
	.text
/APP
	.global IsCPUIDSupported
IsCPUIDSupported:
pushfl
pushfl
xorl $0x00200000, (%esp)
popfl
pushfl
pop %eax
xorl (%esp), %eax
popfl
andl $0x00200000, %eax
shrl $21, %eax
ret

	# Function: check_a20## Purpose: to check the status of the a20 line in a completely self-contained state-preserving way.#          The function can be modified as necessary by removing push's at the beginning and their#          respective pop's at the end if complete self-containment is not required.## Returns: 0 in ax if the a20 line is disabled (memory wraps around)#          1 in ax if the a20 line is enabled (memory does not wrap around).global CheckA20
CheckA20:
pushf
push %ds
push %es
push %di
push %si
cli
xor %ax, %ax # ax = 0
mov %ax, %es
not %ax # ax = 0xFFFF
mov %ax, %ds
mov $0x0500, %di
mov $0x0510, %si
movb %es:(%di), %al
push %ax
mov al, byte [ds:si]
push ax
mov byte [es:di], 0x00
mov byte [ds:si], 0xFF
cmp byte [es:di], 0xFF
pop ax
mov byte [ds:si], al
pop ax
mov byte [es:di], al
mov ax, 0
je check_a20__exit
mov ax, 1
check_a20__exit:
pop si
pop di
pop es
pop ds
popf
ret

	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"eax"
.LC1:
	.string	"="
.LC2:
	.string	"\n"
.LC3:
	.string	"ebx"
.LC4:
	.string	"ecx"
.LC5:
	.string	"edx"
.LC6:
	.string	"esp"
.LC7:
	.string	"ebp"
.LC8:
	.string	"esi"
.LC9:
	.string	"edi"
/NO_APP
	.text
	.align 16
	.globl	_ZN5danos13DumpRegistersEv
	.type	_ZN5danos13DumpRegistersEv, @function
_ZN5danos13DumpRegistersEv:
.LFB7:
	.cfi_startproc
	pushl	%ebx
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	subl	$52, %esp
	.cfi_def_cfa_offset 60
/APP
/  32 "cpu.cpp" 1
	movl %eax, 12(%esp) ;movl %ebx, 16(%esp) ;movl %ecx, 20(%esp) ;movl %edx, 24(%esp) ;movl %esp, 28(%esp) ;movl %ebp, 32(%esp) ;movl %esi, 36(%esp) ;movl %edi, 40(%esp) ;
/  0 "" 2
/NO_APP
	movl	12(%esp), %ebx
	pushl	$.LC0
	.cfi_def_cfa_offset 64
	call	_ZN5danos3LogEPKc
	movl	$.LC1, (%esp)
	call	_ZN5danos3LogEPKc
	movl	%ebx, (%esp)
	call	_ZN5danos3LogEj
	movl	$.LC2, (%esp)
	call	_ZN5danos3LogEPKc
	movl	20(%esp), %ebx
	movl	$.LC3, (%esp)
	call	_ZN5danos3LogEPKc
	movl	$.LC1, (%esp)
	call	_ZN5danos3LogEPKc
	movl	%ebx, (%esp)
	call	_ZN5danos3LogEj
	movl	$.LC2, (%esp)
	call	_ZN5danos3LogEPKc
	movl	24(%esp), %ebx
	movl	$.LC4, (%esp)
	call	_ZN5danos3LogEPKc
	movl	$.LC1, (%esp)
	call	_ZN5danos3LogEPKc
	movl	%ebx, (%esp)
	call	_ZN5danos3LogEj
	movl	$.LC2, (%esp)
	call	_ZN5danos3LogEPKc
	movl	28(%esp), %ebx
	movl	$.LC5, (%esp)
	call	_ZN5danos3LogEPKc
	movl	$.LC1, (%esp)
	call	_ZN5danos3LogEPKc
	movl	%ebx, (%esp)
	call	_ZN5danos3LogEj
	movl	$.LC2, (%esp)
	call	_ZN5danos3LogEPKc
	movl	32(%esp), %ebx
	movl	$.LC6, (%esp)
	call	_ZN5danos3LogEPKc
	movl	$.LC1, (%esp)
	call	_ZN5danos3LogEPKc
	movl	%ebx, (%esp)
	call	_ZN5danos3LogEj
	movl	$.LC2, (%esp)
	call	_ZN5danos3LogEPKc
	movl	36(%esp), %ebx
	movl	$.LC7, (%esp)
	call	_ZN5danos3LogEPKc
	movl	$.LC1, (%esp)
	call	_ZN5danos3LogEPKc
	movl	%ebx, (%esp)
	call	_ZN5danos3LogEj
	movl	$.LC2, (%esp)
	call	_ZN5danos3LogEPKc
	movl	40(%esp), %ebx
	movl	$.LC8, (%esp)
	call	_ZN5danos3LogEPKc
	movl	$.LC1, (%esp)
	call	_ZN5danos3LogEPKc
	movl	%ebx, (%esp)
	call	_ZN5danos3LogEj
	movl	$.LC2, (%esp)
	call	_ZN5danos3LogEPKc
	movl	44(%esp), %ebx
	movl	$.LC9, (%esp)
	call	_ZN5danos3LogEPKc
	movl	$.LC1, (%esp)
	call	_ZN5danos3LogEPKc
	movl	%ebx, (%esp)
	call	_ZN5danos3LogEj
	movl	$.LC2, (%esp)
	call	_ZN5danos3LogEPKc
	addl	$56, %esp
	.cfi_def_cfa_offset 8
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE7:
	.size	_ZN5danos13DumpRegistersEv, .-_ZN5danos13DumpRegistersEv
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align 4
.LC10:
	.string	"cpuid instruction not supported by the CPU\n"
	.section	.rodata.str1.1
.LC11:
	.string	"CPUID Vendor ID: "
.LC12:
	.string	"GenuineIntel"
	.section	.rodata.str1.4
	.align 4
.LC13:
	.string	"DanOS is only built for CPUs with the \"GenuineIntel\" vendor ID\n"
	.align 4
.LC14:
	.string	"A20 memory line has been enabled\n"
	.text
	.align 2
	.align 16
	.globl	_ZN5danos3CPU10InitializeEv
	.type	_ZN5danos3CPU10InitializeEv, @function
_ZN5danos3CPU10InitializeEv:
.LFB8:
	.cfi_startproc
	pushl	%esi
	.cfi_def_cfa_offset 8
	.cfi_offset 6, -8
	pushl	%ebx
	.cfi_def_cfa_offset 12
	.cfi_offset 3, -12
	subl	$36, %esp
	.cfi_def_cfa_offset 48
	call	IsCPUIDSupported
	testb	%al, %al
	je	.L10
/APP
/  120 "cpu.cpp" 1
	mov $0, %eax ;cpuid ;movl %ebx, 4(%esp) ;movl %edx, 8(%esp) ;movl %ecx, 12(%esp) ;
/  0 "" 2
/NO_APP
	movl	%eax, %ebx
	movl	4(%esp), %eax
	movb	$0, 31(%esp)
	subl	$12, %esp
	.cfi_def_cfa_offset 60
	movl	%eax, 31(%esp)
	movl	20(%esp), %eax
	movl	%eax, 35(%esp)
	movl	24(%esp), %eax
	movl	%eax, 39(%esp)
	pushl	$.LC11
	.cfi_def_cfa_offset 64
	call	_ZN5danos3LogEPKc
	popl	%eax
	.cfi_def_cfa_offset 60
	leal	31(%esp), %esi
	pushl	%esi
	.cfi_def_cfa_offset 64
	call	_ZN5danos3LogEPKc
	movl	$.LC2, (%esp)
	call	_ZN5danos3LogEPKc
	popl	%edx
	.cfi_def_cfa_offset 60
	popl	%ecx
	.cfi_def_cfa_offset 56
	pushl	$.LC12
	.cfi_def_cfa_offset 60
	pushl	%esi
	.cfi_def_cfa_offset 64
	call	_ZN4core6String7CompareEPKcS2_
	addl	$16, %esp
	.cfi_def_cfa_offset 48
	testb	%al, %al
	je	.L11
/APP
/  23 "../kernel/io.h" 1
	inb $112, %al
/  0 "" 2
/NO_APP
	orl	$-128, %eax
/APP
/  16 "../kernel/io.h" 1
	outb %al, $112
/  0 "" 2
/  139 "cpu.cpp" 1
	cli

/  0 "" 2
/NO_APP
	call	CheckA20
	testl	%eax, %eax
	je	.L12
.L8:
	subl	$12, %esp
	.cfi_def_cfa_offset 60
	xorl	%ebx, %ebx
	pushl	$.LC14
	.cfi_def_cfa_offset 64
	call	_ZN5danos3LogEPKc
	addl	$16, %esp
	.cfi_def_cfa_offset 48
	movl	%ebx, %eax
	addl	$36, %esp
	.cfi_remember_state
	.cfi_def_cfa_offset 12
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 8
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 4
	ret
	.align 16
.L11:
	.cfi_restore_state
	subl	$12, %esp
	.cfi_def_cfa_offset 60
	pushl	$.LC13
	.cfi_def_cfa_offset 64
	call	_ZN5danos3LogEPKc
	addl	$16, %esp
	.cfi_def_cfa_offset 48
	movl	%ebx, %eax
	addl	$36, %esp
	.cfi_remember_state
	.cfi_def_cfa_offset 12
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 8
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 4
	ret
	.align 16
.L10:
	.cfi_restore_state
	subl	$12, %esp
	.cfi_def_cfa_offset 60
	movl	$1, %ebx
	pushl	$.LC10
	.cfi_def_cfa_offset 64
	call	_ZN5danos3LogEPKc
	addl	$16, %esp
	.cfi_def_cfa_offset 48
	movl	%ebx, %eax
	addl	$36, %esp
	.cfi_remember_state
	.cfi_def_cfa_offset 12
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 8
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 4
	ret
	.align 16
.L12:
	.cfi_restore_state
	call	_ZN5danos18KeyboardController13InitializeA20Ev
	jmp	.L8
	.cfi_endproc
.LFE8:
	.size	_ZN5danos3CPU10InitializeEv, .-_ZN5danos3CPU10InitializeEv
	.ident	"GCC: (GNU) 9.2.0"
