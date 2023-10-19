		extern printf			; the C function to be called

		SECTION .data			; Data section, initialized variables
message:    	db "Hello, Holberton", 0	; strings must be terminated with 0 in C
format:    	db "%s", 10, 0			; the printf format, "\n", '0'

		SECTION .text

		global main
main:						; the program label for the entry point
		push rbp			; set up stack frame, must be alligned

		mov rdi,format
		mov rsi,message
		mov rax,0			; or can be  xor  rax,rax
		call printf			; Call C function

		pop rbp				; restore stack

		mov rax,0			; normal, no error, return value
		ret				; return
