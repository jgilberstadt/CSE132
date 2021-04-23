#include <avr/io.h>
#include "asmMacros.S"

.data
  counter: .byte 0


.text

.global increment
increment:
  ldi 30, lo8(counter)
  ldi 31, hi8(counter)
  ldi r22, 1
  ld r24, Z
  adc r24, r22
  st Z, r24
  ret

.global decrement
decrement:
  ldi 30, lo8(counter)
  ldi 31, hi8(counter)
  ldi r22, 1
  ld r24, Z
  sub r24, r22
  st Z, r24
  ret

.global sumArray
sumArray:
  mov r30, r24
  mov r31, r25
  ldi r25, 0
  ldi r24, 0
  ldi r20, 1
  
startLoop:
    ldi r19, 0
    cp r22, r23
    breq checkZero
checkZero:
    cpi r22, 0
    breq done

    sub r22, r20
    ld r18, Z+
    adc r24, r18
    adc r25, r19
    jmp startLoop

done:
  ret
