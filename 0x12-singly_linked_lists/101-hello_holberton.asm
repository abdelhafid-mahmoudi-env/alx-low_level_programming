section .data
hello db "Hello, Holberton",10 ; The string to be printed (with newline)

section .text
global main

extern printf

main:
    push rbp
    mov rdi, hello ; Address of the string
    call printf
    pop rbp
    ret

