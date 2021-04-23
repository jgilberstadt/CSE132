#include <avr/io.h>
#include "asmMacros.S"
//done


// TODO: Complete functions!

.global lessThan
lessThan:
  cp 24, 22
  brlt less
  ldi 24, 0
  ret
less:
  ldi 24, 1
  ret

.global lessThanOrEqualUnsigned
lessThanOrEqualUnsigned:
  cp 22, 24
  brlo lesseq
  ldi 24, 1
  ret
lesseq:
  ldi 24, 0
  ret

.global slowMultiply
slowMultiply:
mov 20, 24
ldi 24, 0
ldi 21, -1
start:
  cpi 22, 0
  breq done
  adc 24, 20
  adc 22, 21
  jmp start
done:
  ret

.global slowExponent
slowExponent:
// a: 24
// power: 22
// sum: 20
// i: 19
// innerSum: 18
// j: 17
  ldi 21, 1
  ldi 20, 1
  ldi 19, 0
start1:
    cp 19, 22
    brsh done2
    
    ldi 18, 0
    ldi 17, 0
start2:
      cp 17, 24
      brsh done1
      
      add 18, 20
      add 17, 21
      jmp start2
done1:
    mov 20, 18
    add 19, 21
    jmp start1
done2:
  mov 24, 20
  ret
