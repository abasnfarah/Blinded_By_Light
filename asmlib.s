
.include "xc.inc"

.text                       ;BP (put the following data in ROM(program memory))

; This is a library, thus it can *not* contain a _main function: the C file will
; define main().  However, we
; we will need a .global statement to make available ASM functions to C code.
; All functions utilized outside of this file will need to have a leading 
; underscore (_) and be included in a comment delimited list below.
.global _wait_1ms, _wait_100us, 
    

_wait_1ms:; 16327 cycles = 1 ms
    ; 2 cycles
    repeat #16321   ; 1 cycle
    nop		    ; 1 cycle
    return; 3 cycles

_wait_100us: ; 817 cycles = 50 microseconds *2 = 100 microseconds
    ; 2 cycles
    repeat #1628 ; 1 cycle
    nop		 ; 1 cycle
    return ; 3 cycle



