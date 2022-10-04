section .text
global toLowerUnderscore
toLowerUnderscore:
  mov rsi, rdi
  jmp .calc
.calc:
  lodsb
  cmp al, 0
  je .end
  cmp al, 'A'
  jge .next
  cmp al, ' '
  je .replace
  jmp .calc
  .next:
    cmp al, 'Z'
    jge .calc
    xor al, 0x20
    mov byte [rsi-1], al
    jmp .calc
  .replace:
    mov byte [rsi-1], '_'
  .end:
    ret
