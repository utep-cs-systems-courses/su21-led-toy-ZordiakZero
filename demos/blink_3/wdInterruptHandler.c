#include <msp430.h>
#include "stateMachines.h"

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char blink_count = 0;
  blink_count = (blink_count + 1) % 1;
  if(blink_count == 0)
    state_advance();
}
