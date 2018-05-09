GLOBAL tickHandler
EXTERN next_process
EXTERN timer_handler

%include "./asm/macros.m"

section .text

tick_handler:
  pushState

	call timer_handler

	mov rdi, rsp
	call next_process

	mov rsp, rax

	mov al, 0x20
	out 0x20, al

	popState

	iretq
