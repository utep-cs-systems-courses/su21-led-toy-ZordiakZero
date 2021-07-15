#include <msp430.h>
#include "stateMachines.h"
#include "switches.h"
#include "led.h"

char switch_state_down_1, switch_state_down_2, switch_state_down_3, switch_state_down_4, switch_state_changed;

static char 
switch_update_interrupt_sense()
{
  char p1val = P1IN;
  /* update switch interrupt to detect changes from current buttons */
  P1IES |= (p1val & SWITCHES);	/* if switch up, sense down */
  P1IES &= (p1val | ~SWITCHES);	/* if switch down, sense up */
  return p1val;
}

void 
switch_init()			/* setup switch */
{  
  P1REN |= SWITCHES;		/* enables resistors for switches */
  P1IE |= SWITCHES;		/* enable interrupts from switches */
  P1OUT |= SWITCHES;		/* pull-ups for switches */
  P1DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
  led_update();
}

void
switch_interrupt_handler()
{
  char p1val = switch_update_interrupt_sense();
  switch_state_down_1 = (p1val & SW1) ? 0 : 1;
  switch_state_down_2 = (p1val & SW2) ? 0 : 1;
  switch_state_down_3 = (p1val & SW3) ? 0 : 1;
  switch_state_down_4 = (p1val & SW4) ? 0 : 1;
  switch_state_changed = 1;
  if(switch_state_down_1)
    buzzer_set_period(250);
  if(switch_state_down_2)
    buzzer_set_period(500);
  if(switch_state_down_1)
    buzzer_set_period(750);
  led_update();
}
