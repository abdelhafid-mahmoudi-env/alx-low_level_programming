section .data
    hello db "Hello, Holberton",10,0  ; The string to be printed with a newline character

section .text
    global main
    extern printf

main:
    push rbp                  ; Save the base pointer
    mov rdi, hello            ; Load the address of the string into rdi
    call printf               ; Call the printf function
    pop rbp                   ; Restore the base pointer
    ret                       ; Exit the program

