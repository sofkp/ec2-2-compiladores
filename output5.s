.section .rodata
print_fmt: .string "%ld\n" 
.text
.globl main
main:
pushq %rbp
movq %rsp, %rbp
sub $32, %rsp
movq $10, %rax
movq %rax,-8(%rbp)
movq $5, %rax
movq %rax,-16(%rbp)
while_0:
movq -16(%rbp), %rax
pushq %rax
movq -8(%rbp), %rax
movq %rax, %rcx
popq %rax
cmpq %rcx, %rax
movl $0, %eax
setl %al
movzbq %al, %rax
cmpq $0 ,%rax
je endwhile_0
movq $0, %rax
movq %rax,-24(%rbp)
while_1:
movq -24(%rbp), %rax
pushq %rax
movq -16(%rbp), %rax
movq %rax, %rcx
popq %rax
cmpq %rcx, %rax
movl $0, %eax
setl %al
movzbq %al, %rax
cmpq $0 ,%rax
je endwhile_1
movq -24(%rbp), %rax
pushq %rax
movq $5, %rax
movq %rax, %rcx
popq %rax
cmpq %rcx, %rax
movl $0, %eax
setl %al
movzbq %al, %rax
cmpq $0 ,%rax
je else_2
movq $10, %rax
movq %rax, %rsi
leaq print_fmt(%rip), %rdi
movl $0, %eax
call printf@PLT
jmp endif_2
else_2:
movq $20, %rax
movq %rax, %rsi
leaq print_fmt(%rip), %rdi
movl $0, %eax
call printf@PLT
endif_2:
movq -24(%rbp), %rax
pushq %rax
movq $1, %rax
movq %rax, %rcx
popq %rax
addq %rcx, %rax
movq %rax,-24(%rbp)
jmp while_1
endwhile_1:
movq -16(%rbp), %rax
pushq %rax
movq $1, %rax
movq %rax, %rcx
popq %rax
addq %rcx, %rax
movq %rax,-16(%rbp)
jmp while_0
endwhile_0:
movl $0, %eax
leave
ret
.section .note.GNU-stack,"",@progbits
