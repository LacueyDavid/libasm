default rel
global ft_strdup
extern ft_strlen
extern ft_strcpy
extern malloc

section .text

ft_strdup:
  mov rbx, rdi
  call ft_strlen
  inc rax
  mov rdi, rax
  call malloc wrt ..plt
  cmp rax, 0
  je .done
  mov rdi, rax
  mov rsi, rbx
  call ft_strcpy

.done:
  ret
