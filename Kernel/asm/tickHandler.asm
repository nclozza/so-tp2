GLOBAL tickHandler
EXTERN schedule

%include "./asm/macros.m"

section .text

tick_handler:
  pushState
  mov rdi, rsp
  mov rsp, rax
  ;call schedule
  mov rsp, rax
  popState
  endOfInterrupt
  iretq
