#include <msp430.h>
#include "stateMachines.h"
#include "led.h"

char toggle_red()		/* always toggle! */
{
  static char state = 0;

  switch (state) {
  case 0:
    red_on = 1;
    state = 1;
    break;
  case 1:
    red_on = 0;
    state = 0;
    break;
  }
  return 1;			/* always changes an led */
}

char toggle_green()	/* only toggle green if red is on!  */
{
  char changed = 0;
  if (red_on) {
    green_on ^= 1;
    changed = 1;
  }
 return changed;
}
char green_dim() {
  static char state = 1;
  char rtn = 1;

  if(state == 0) {
    green_on = 1;
    rtn = 1;
  } else if(state == 3) {
    green_on = 0;
    rtn = 1;
  }

  state = (state + 1) % 8;
  return rtn;
}

char turn_on_green() {
  static char superState = 0; // For seconds
  static unsigned char state = 0; // For 1/250 seconds
  char rtn = 0;

  // For ON
  if(superState == 0) {
    if(state == 0) { // Beginning of state
      green_on = 1;
      rtn = 1;
    }
  }
  // For Dim
  else if(superState == 1) {
    rtn = green_dim();
  }
  // For off
  else if(superState == 2) {
    if(state == 0) { // Beginning of state
      green_on = 0;
      rtn = 1;
    }
  }

  state = (state + 1) % 250;
  // If after incrementing state the result is 0, it indicates that a new superState iteration is in place
  if(state == 0) superState = (superState + 1) % 3;
  return rtn;
}

char turn_on_red() {
  red_on = 1;
  return 1;
}


void state_advance() {
  char changed = 0;
  changed = turn_on_green() || turn_on_red();

  led_changed = changed;
  led_update();
}
