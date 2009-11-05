#include "tv80_env.h"

/*
 * This test covers interrupt handling routines.  The actual interrupt code
 * is in assembly, in bintr_crt0.asm.
 *
 * The test generates five interrupts, and clears the interrupt after
 * each one.
 *
 * The isr routine uses the two writes to intr_cntdwn to first clear
 * assertion of the current interrupt and then disable the countdown
 * timer.
 */

unsigned char foo;
volatile unsigned char test_pass;
static unsigned char triggers;
int phase;
char done;
char nmi_trig;

void nmi_isr (void)
{
  nmi_trig++;

  switch (phase) {
    // nmi test
  case 1 :
    if (nmi_trig > 5) {
      phase += 1;
      nmi_trig = 0;
      //intr_cntdwn = 255;
      //intr_cntdwn = 0;
      intr_cntdwn = 32;
      nmi_cntdwn = 0;
    } else
      nmi_cntdwn = 32;
    break;

    // just trigger once, and disable interrupt
  case 3 :
    nmi_cntdwn = 0;
    nmi_trig_opcode = 0; // pop AF opcode
    break;
  }
}

void isr (void)
{
  int i;
  triggers++;

  switch (phase) {
    // int test
  case 0 :
    if (triggers > 5) {
      phase += 1;
      triggers = 0;
      intr_cntdwn = 0;
      nmi_cntdwn = 64;
    } else {
      intr_cntdwn = 32;
      
    }
    break;


    // int / nmi interaction
    // in this phase set up interrupt call
    // which will be interrupted by an nmi
  case 2 :
    phase += 1;
    triggers = 0;
    nmi_trig = 0;
    intr_cntdwn = 20;
    nmi_trig_opcode = 0xF1; // pop AF opcode

    break;

    // wait for a while while servicing interrupt
    // nmi should interrupt us and increment nmi_trig
    // if test pass is true when we are done then exit
  case 3 :
    intr_cntdwn = 0;
    if (nmi_trig == 1)
      test_pass = 1;
    break;
    
  }
}

int main ()
{
  int i;
  unsigned char check;

  test_pass = 0;
  triggers = 0;
  nmi_trig = 0;

  phase = 0;

  // start interrupt countdown
  intr_cntdwn = 64;
  set_timeout (50000);

  for (i=0; i<1024; i++) {
    if (test_pass)
      break;
    check = sim_ctl_port;
  }

  if (test_pass)
    sim_ctl (SC_TEST_PASSED);
  else
    sim_ctl (SC_TEST_FAILED);

  return 0;
}

