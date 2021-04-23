#include <avr/io.h>

; AVR assembly comments start with a semicolon 
// (or a double slash, like C)
; Lines without labels should be indented once.

; You can "call printRegs" in your code to help you understand the register values and how they change.

.global hasAOne
hasAOne:
  CPSE r24, r1
  ldi r24, 1
  ret


.global byteToAscii
byteToAscii:
  ADIW r24, 48
  ret
  

.global int8ToInt
int8ToInt:
  ldi r25, 0
  SBRC r24, 7
  SUBI r25, 1
  ret
  

.global addInt8ToInt
addInt8ToInt:
  call int8ToInt
  add r24, r22
  adc r25, r23
  ret


.global add4Int8
add4Int8:
  push r18
  push r20
  push r22
  call int8ToInt
  mov r22, r24
  mov r23, r25
  pop r24
  call addInt8ToInt
  mov r22, r24
  mov r23, r25
  pop r24
  call addInt8ToInt
  mov r22, r24
  mov r23, r25
  pop r24
  call addInt8ToInt
  ret


.global average
average:
  add r24, r22
  ror r24
  ret
