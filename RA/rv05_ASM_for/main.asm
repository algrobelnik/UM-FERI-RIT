extern printf
extern scanf

section .data
  input: db "%ld", 0                ;formating for scanf (ld - long decimal integer)
  input_text: db "Insert value for N:", 32, 0
  output: db "%ld", 10, 0

section .bss ;section for assigning values (resq: 8 byte)
  i resq 1
  N resq 1

section .text
  global main

main:
  push rbp ;save rbp register
    
  mov rax, 1
  mov rdi, 0
  mov rsi, input_text 
  mov rdx, 20
  syscall             ;normal syswrite

  mov rdi, input
  mov rsi, N
  mov rax, 0
  call scanf          ;call scanf with previus arguments


  dec dword [N]       ;decrement N
  mov dword [i], 1    ;de
  
  .loop:               ;start of loop 
    mov rax, [i]       ;fill rax with value of i
    cmp rax, [N]       ;cmp rax with value of N
    jg .exit           ;jmp to .exit if i>N

    mov rdi, output 
    mov rsi, [i]
    mov rax, 0
    call printf        ;call printf with previus arguments
    inc dword [i]      ;increment i
    jmp .loop          ;jump to .loop row

  .exit:
    pop rbp 
    mov rax, 0     ;return code 0
    ret            ;return

