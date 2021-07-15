#include <msp430.h>
#include "stateMachines.h"

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char blink_count = 0;
  switch(current_state) {
  case 0:
    if(++blink_count >= 5)
      off();
    if(++blink_count >= 10){
      led_update();
      blink_count = 0;
    }
    break;
  case 1:
    if(++blink_count >= 2)
      off();
    if(++blink_count >= 5){
      led_update();
      blink_count = 0;
    }
    break;
  case 2:
    led_update();
    break;
  default:
    if(++blink_count >= 50)
      off();
    if(++blink_count >= 100){
      led_update();
      blink_count = 0;
    }
    break;
  }
}
}
