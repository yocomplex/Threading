section .data
;------------- Constants -------------
EXIT_SUCCESS    equ     0   ;Exit code for success
TRUE            equ     1
FALSE           equ     0

;External function to print an integer for debugging purpose
;Single arg (rdi) is integer to print by value
extern printInt

section .text
global findSum

;############## YOUR CODE HERE ############# 
;Finish the one findSum function. Since main is in the C program, no _start here. The C program will call your function

;The findSum function should find the sum of a subarray given its length and start_index. For example, if we had the array
;{4, 5, 3, 2, 6, 9, 8, 7, 1, 0, 4}, start_index = 3, and length = 4
;The sum would be 2 + 6 + 9 + 8 = 25

;This function takes four arguments
;rdi = address of the array
;esi = index to start the sum at by value
;edx = length of the sub array
;rcx = address of the variable to store the dword result sum to
;No return value, sum will be pass by reference (How threads usually operate)
;Takes a reference to the array, its length by value, the start_index by value, and the address of where to store the sum (check function comments)
findSum:
;-- Finish the function
;Preserve any registers you need
;Then, find the sum of the sub array and store the result using the reference to the sum variable
;Use the above argument descriptions

    push rbp
    mov rbp, rsp

    mov eax, 0 ;eax = 0 used as counter
    mov r10d, esi ;index to reg r10d
    add r10d, eax ;index + counter
    mov ebx, 0 ;ebx = 0 used for the sum

    loopStart:
        add ebx, dword [edi + 4 * r10d] ;gran value of array and store into the sum(ebx)
        inc r10d ;incrmeent r10d
        inc eax ;increment eax
        cmp eax, edx ;compare if eax is < edx
        jl loopStart ;if less than, jump to loopStart

    mov dword[ecx], ebx ;store ebx into address of ecx

    pop rbp 
    ret
