#include <avr/io.h>

; AVR assembly comments start with a semicolon 
// (or a double slash, like C)
; Lines without labels should be indented once.

; You can "call printRegs" in your code to help you understand the register values and how they change.

.global giveMeMax
giveMeMax:
  ldi r24, 255 // Load the value 1 into register 24
  ret

 // Define further "functions" below:
 // .global functionName
 // functionName:
 //   *code*
 //   ret

 
.global giveMeZero
giveMeZero:
//  call printRegs
  ldi r24, 0 // Load the value 1 into register 24
//  call printRegs
  ret

.global addFour
addFour:
 call printRegs
  ldi r22, 4 // Load the value 4 into register 22
  call printRegs
  add r24, r22
  call printRegs
  ret
