;--------------------------------------------------------------
section .data
    msg db "Hello, Holberton", 0      ; Message string
    fmt db "%s", 10, 0               ; Format string

section .text
    global main

main:
    ; Save the base pointer
    push rbp

    ; Set up the parameters for printf
    mov rdi, fmt        ; Format string
    mov rsi, msg        ; Message string
    xor rax, rax        ; Clear rax (no SIMD register needed)

    ; Call the printf function
    call printf

    ; Restore the base pointer
    pop rbp

    ; Exit with a return value of 0
    xor rax, rax
    ret
