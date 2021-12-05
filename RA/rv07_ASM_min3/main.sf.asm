extern printf
extern scanf

section .data
  input: db "%ld", 0                ;formating for scanf (ld - long decimal integer)
  inputX1: db "Insert value for x1:", 32, 0
  inputX2: db "Insert value for x2:", 32, 0
  inputX3: db "Insert value for x3:", 32, 0
  output: db "%ld", 10, 0

section .bss ;section for assigning values (resq: 8 byte)
  res resq 1
  x1 resq 1
  x2 resq 1
  x3 resq 1

section .text
  global main

main:
  push rbp ;save rbp register
    
  mov rax, 1
  mov rdi, 0
  mov rsi, inputX1
  mov rdx, 21
  syscall             ;normal syswrite

  mov rdi, input
  mov rsi, x1
  mov rax, 0
  call scanf          ;call scanf with previus arguments

  mov rax, 1
  mov rdi, 0
  mov rsi, inputX2
  mov rdx, 21
  syscall             ;normal syswrite

  mov rdi, input
  mov rsi, x2
  mov rax, 0
  call scanf          ;call scanf with previus arguments

  mov rax, 1
  mov rdi, 0
  mov rsi, inputX3
  mov rdx, 21
  syscall             ;normal syswrite

  mov rdi, input
  mov rsi, x3
  mov rax, 0
  call scanf          ;call scanf with previus arguments

  mov rsi, [x1] 
  mov [res], rsi
  jmp .firstCalc



  .firstCalc:
    xor rdi, rdi
    xor rsi, rsi
    xor rdx, rdx
    mov rdi, [x1]
    mov rsi, [x2]
    mov rdx, [x3]
    cmp rdi, rsi
    jg .secondCalc
    cmp rdi, rdx
    jg .secondCalc
    mov [res], rdi
    jmp .secondCalc
  
  .secondCalc:
    xor rdi, rdi
    xor rsi, rsi
    xor rdx, rdx
    mov rdi, [x2]
    mov rsi, [x1]
    mov rdx, [x3]
    cmp rdi, rsi
    jg .thirdCalc
    cmp rdi, rdx
    jg .thirdCalc
    mov [res], rdi
    mov rax, 0
    jmp .thirdCalc

  .thirdCalc:
    xor rdi, rdi
    xor rsi, rsi
    xor rdx, rdx
    mov rdi, [x3]
    mov rsi, [x1]
    mov rdx, [x2]
    cmp rdi, rsi
    jg .result
    cmp rdi, rdx
    jg .result
    mov [res], rdi
    jmp .result

  .result:
    mov rdi, output
    mov rsi, [res]
    mov rax, 0
    call printf        ;call printf with previus arguments
    jmp .exit

  .exit:
    pop rbp
    mov rax, 0     ;return code 0
    ret            ;return
