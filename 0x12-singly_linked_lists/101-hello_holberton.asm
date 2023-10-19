;-----------------------------------------------------------------------
; File: 101-hello_holberton.asm
;-----------------------------------------------------------------------
; Description: This is a 64-bit assembly program that prints the
; message "Hello, Holberton" followed by a new line using the printf
; function.
;
; Restrictions:
; - Only allowed to use the printf function.
; - Not allowed to use interrupts.
; - To compile, use nasm and gcc:
;   nasm -f elf64 101-hello_holberton.asm && gcc -no-pie -std=gnu89 101-hello_holberton.o -o hello
;
; Usage: ./hello
;
; Expected Output:
; Hello, Holberton
;-----------------------------------------------------------------------

section .data
    hello db "Hello, Holberton", 10, 0  ; Define a null-terminated string with a newline character

section .text
    global main
    extern printf

main:
    push rbp
    mov rdi, hello         ; Load the address of the string into rdi
    call printf            ; Call the printf function
    pop rbp
    ret
