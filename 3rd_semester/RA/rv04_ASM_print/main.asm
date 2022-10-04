global _start

section .text
_start:
mov rax, 1      ;save for syscall 1 (write)
mov rdi, 1      ;set file descriptor 1 (stdout)
mov rsi, output ;fill rsi with output string
mov rdx, 63     ;set size of rdx register
syscall         ;kernel call sys_write(fd:rdi(1), buf: output, size: rdx(64))
mov rax, 60     ;save for syscall 60 (exit)
xor rdi, rdi    ;set error code 0 (return(0) in c)
syscall         ;kernel call sys_exit(error_code: rdi(0))

section .data
output: db "Ime: Aleksander", 10, "Priimek: Grobelnik", 10, "Vpisna številka: 1002462304" ;63 bits long text
