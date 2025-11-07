.section .rodata
print_fmt: .string "%ld\n" 
.text
.globl main
main:
pushq %rbp
movq %rsp, %rbp
sub $32, %rsp
movq $4, %rax
movq %rax,-8(%rbp)
movq $10, %rax
movq %rax,-16(%rbp)
movq $5, %rax
pushq %rax
movq -8(%rbp), %rax
movq %rax, %rcx
popq %rax
cmpq %rcx, %rax
movl $0, %eax
setg %al
movzbq %al, %rax
cmpq $0 ,%rax
je else_0
movq -16(%rbp), %rax
pushq %rax
movq $10, %rax
movq %rax, %rcx
popq %rax
cmpq %rcx, %rax
movl $0, %eax
sete %al
movzbq %al, %rax
cmpq $0 ,%rax
je else_1
movq $10, %rax
movq %rax, %rsi
leaq print_fmt(%rip), %rdi
movl $0, %eax
call printf@PLT
jmp endif_1
else_1:
movq $20, %rax
movq %rax, %rsi
leaq print_fmt(%rip), %rdi
movl $0, %eax
call printf@PLT
endif_1:
jmp endif_0
else_0:
movq $30, %rax
movq %rax, %rsi
leaq print_fmt(%rip), %rdi
movl $0, %eax
call printf@PLT
endif_0:
movl $0, %eax
leave
ret
.section .note.GNU-stack,"",@progbits
