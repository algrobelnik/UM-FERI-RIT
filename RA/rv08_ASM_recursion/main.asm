extern printf
extern scanf

section .data
  input: db "%ld", 0                ;formating for scanf (ld - long decimal integer)
  input_number: db "Insert value for num:", 32, 0
  output: db "%ld", 10, 0

section .bss ;section for assigning values (resq: 8 byte)
  i resq 1
  num resq 1

section .text
  global main

  main:
    push rbp ;save rbp register
      
    mov rax, 1
    mov rdi, 0
    mov rsi, input_number
    mov rdx, 22
    syscall             ;normal syswrite

    mov rdi, input
    mov rsi, num
    mov rax, 0
    call scanf          ;call scanf with previus arguments

    call recursion


  recursion:
  xor rax, rax
  mov dword [i], 2
  dec dword [num]

  .loop:
    mov rdi, [i]       ;fill rdi with value of i
    cmp rdi, [num]     ;cmp rdi with value of num
    jg .exit           ;jmp to .exit if i>num

    call func

    mov rdi, output
    mov rsi, rax
    mov rax, 0
    call printf        ;call printf with previus arguments
    inc dword [i]      ;increment i
    jmp .loop          ;jump to .loop row

  .exit:
    pop rbp
    mov rax, 0     ;return code 0
    ret            ;return

  func:
    cmp rdi, 0
    je case0
    cmp rdi, 1
    je case1
    cmp rdi, 2
    je case2
    ;mov rsi, rdi
    push rdi
    sub rdi, 3
    call func
    pop rdi
    
    push rax
    push rdi
    sub rdi, 2
    call func
    pop rdi

    pop rsi
    add rax, rsi
    add rax, 1
    ret

  case0:
    mov rax, 12
    ret

  case1:
    mov rax, 22
    ret

  case2:
    mov rax, 45
    ret

