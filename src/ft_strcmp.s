global ft_strcmp
section .text

ft_strcmp:
xor rcx,rcx
.loop:
  movzx rax, byte [rdi, rcx]
  movzx rbx, byte [rsi, rcx]
  cmp rax, rbx
  jne .not_equal 
  cmp rax, 0
  je .equal
  inc rcx
  jmp .loop

.not_equal:
  sub rax, rbx
  ret

.equal:
  xor rax,rax
  ret
