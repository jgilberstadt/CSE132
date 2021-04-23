#include <avr/io.h>
#include "asmMacros.s"  // Include macros to print log messages or a single register
.text


.global slowDivisionUint8
slowDivisionUint8:
  // TODO: uint8_t slowDivisionUint8(uint8_t a, uint8_t b)
  ldi r31, 1
  ldi r30, 0
  jmp startOfWhilePart
startOfWhilePart:
  cp r24, r22
  brlo endOfWhilePart
  sub r24, r22
  add r30, r31
  jmp startOfWhilePart
endOfWhilePart:
  mov r24, r30
  ret


.global greaterThanOrEqualUInt16 // line 23
greaterThanOrEqualUInt16:
  // TODO: bool greaterThanOrEqualUInt16(uint16_t a, uint16_t b)
  cp r25, r23
  breq ifEqual
  cp r25, r23
  brlo falsePart 
  ldi r24, 1
  ret
ifEqual:
  cp r24, r22
  brlo falsePart
  ldi r24, 1
  ret
falsePart:
  ldi r24, 0
  ret

  
.global slowDivisionUint16
slowDivisionUint16:
  // TODO: uint16_t slowDivisionUint16(uint16_t a, uint16_t b)
  /* we need a counter for how many times the divisor divides the dividend */
  ldi r27, 0 //  higher 8 bits of counter in r27
  ldi r26, 0 // lower 8 bits of counter in r26
  // let's save our stuff
  /* divisor is in r18 and r19 */
  mov r18, r22
  mov r19, r23
  /* dividend is in r20 and r21 */
  mov r20, r24
  mov r21, r25
beginWhileLoop:
  call greaterThanOrEqualUInt16
  ldi r25, 0
  cp r24, r25
  breq endOfWhileLoop
  // subtract stuff
  ldi r25, 1
  add r26, r25
  ldi r25, 0
  adc r27, r25
  sub r20, r18
  sbc r21, r19
  mov r24, r20
  mov r25, r21
  mov r22, r18
  mov r23, r19
  jmp beginWhileLoop
endOfWhileLoop:
  // we're done
  mov r24, r26
  mov r25, r27
  ret


.global slowModulusUint8 // line 57
slowModulusUint8:
  ldi r23, 0
  ldi r25, 0
  // TODO: uint16_t slowModulusUint8(uint8_t a, uint8_t b)
  mov r26, r24 // dividend in r26 
  mov r27, r22  // divisor in r27
  call slowDivisionUint8
  mul r24, r27
  mov r1, r25
  sub r26, r0
  mov r24, r26
  ret
  

.global sumOddsUint8
sumOddsUint8:
  // TODO uint16_t sumOddsUint8(uint8_t a, uint8_t b)
  push r16
  ldi r20, 0 // lower 8 bits of sum in r20
  ldi r21, 0 // higher 8 bits of sum in r21
  mov r18, r22 // max in 18
  mov r19, r24 // min in 19
beginOfWhile:
  cp r22, r24 // comparing max and min
  brlo endOfWhile // if max < min, end of loop // bug at max = 255
  ldi r22, 2 // setup r24 and r22 for call to slowModulus
  call slowModulusUint8
  ldi r16, 1
  cp r24, r16
  brne increment // if remainder of 0, then they're even, so increment min and repeat loop
  /* adding min to sum */
  add r20, r19
  push r25
  ldi r25, 0
  adc r21, r25
  pop r25
  cp r18, r19
  breq endOfWhile
  
increment:
  add r19, r16 // increment min
  mov r24, r19
  mov r22, r18
  jmp beginOfWhile
endOfWhile:
  mov r24, r20
  mov r25, r21
  pop r16
  ret 
