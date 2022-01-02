extern printf
extern scanf

section .data
  ;arr: dw "NEKAJ", 10
  input: db "%s", 0                ;formating for scanf (ld - long decimal integer)
  input_text: db "Insert value:", 32, 0
  output: db "Reversed array: %s", 10, 0

section .bss ;section for assigning values (resq: 8 byte)
  val1 resb 1024
  val2 resb 1024

section .text
  global main

  main:
    mov rbp, rsp; for correct debugging
    push rbp ;save rbp register
  
    mov rdi, 0
    mov rsi, input_text
    mov rdx, 14
    mov rax, 1
    syscall             ;normal syswrite

    mov rdi, input
    mov rsi, val1
    mov rax, 0
    call scanf          ;call printf with previus arguments

    mov rsi, val1
    mov rdi, val2
    mov r13, 5
    call reverseArray

    mov rdi, output
    mov rsi, val2
    mov rax, 0
    call printf          ;call printf with previus arguments

    pop rbp
    mov rax, 0
    ret

  reverseArray:
    cld
    .getLen:
    lodsb               ;LODSB loads a byte from [DS:SI] or [DS:ESI] into AL. It then increments
                        ; or decrements (depending on the direction flag: increments if the flag
                        ; is clear, decrements if it is set) SI or ESI
    cmp al, 0
    jnz .getLen
    sub rsi, 2
    mov r14, rsi
    sub rsi, r13
    mov r13, rsi
    mov rsi, r14
  reverse:
    cmp rsi, r13
    jle .end
    mov byte dl, [rdi]
    std
    lodsb
    mov byte [rsi+1], dl
    cld
    stosb               ;STOSB stores the byte in AL at [ES:DI] or [ES:EDI], and sets the flags
                        ;accordingly. It then increments or decrements (depending on the direction
                        ;flag: increments if the flag is clear, decrements if it is set) DI (or EDI).
    jmp reverse

    .end:
    ret
