#include <avr/io.h>
#include "asmMacros.s"  // Include macros to print log messages or a single register

.data
myGlobalVariable: .byte 0

.text

.global updateGlobal
updateGlobal:
  // TODO: void updateGlobal(byte a)
  // add a to our global variable
  ldi r30, lo8(myGlobalVariable)
  ldi r31, hi8(myGlobalVariable)
  ld r22, Z
  add r24, r22
  st Z, r24
  ret

.global getGlobal
getGlobal:
  // TODO: uint8_t getGlobal()
  // Z is registers 30 and 31, so let's load the lower 8 bits and higher 8 bits of our global variable in these registers, then move them to r24 and r25.
  ldi r30, lo8(myGlobalVariable)
  ldi r31, hi8(myGlobalVariable)
  ld r24, Z
  ret


.global cStringLength
cStringLength:
  // TODO: uint8_t cStringLength(const char aString[])
  ldi r22, 1 // incrementer
  ldi r20, 0 // length counter
  mov r30, r24
  mov r31, r25
whilePart:
  ld r24, Z+ 
  cp r24, r1 // checking if we've encountered the sentinel value
  breq endPart 
  add r20, r22
  jmp whilePart
endPart:
  mov r24, r20
  mov r25, r1
  ret
  
 
.global sumArrays

sumArrays:
  push r16
  push r17
  push r28
  push r29
  // TODO: void sumArrays(uint8_t *a, uint8_t *b, uint8_t *c, byte length)
  ldi r17, 1 // incrementer
  ldi r16, 0 // length tracker
  mov r26, r24 // a in X
  mov r27, r25
  mov r28, r22 // b in Y
  mov r29, r23
  mov r30, r20 // c in Z
  mov r31, r21
beginWhile:
  cp r16, r18 // length tracker to length
  breq endWhile
  ld r24, X+
  ld r22, Y+
  add r24, r22
  st Z+, r24
  add r16, r17
  jmp beginWhile
endWhile:
  ld r24, Z
  pop r29
  pop r28
  pop r17
  pop r16
  ret
  

.global dot
dot:
  push r16
  push r17 // need to push both registers, since we're returning a 16-bit value
  push r1
  // TODO uint16_t dot(uint8_t *a, uint8_t *b, byte length)
  ldi r16, 0 // result of dot product
  ldi r17, 0
  ldi r18, 0 // length tracker
  ldi r19, 1 // incrementer
  mov r26, r24 // a in X
  mov r27, r25
  mov r30, r22 // b in Z
  mov r31, r23
beginOfWhile:
  cp r18, r20
  breq endOfWhile
  ld r24, X+
  ld r22, Z+
  mul r22, r24
  add r16, r0
  adc r17, r1
  add r18, r19
  jmp beginOfWhile
endOfWhile:
  mov r24, r16
  mov r25, r17
  // resetting our registers
  pop r1
  pop r17
  pop r16
  ret
