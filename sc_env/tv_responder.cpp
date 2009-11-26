#include "tv_responder.h"

void tv_responder::event ()
{
	// init
	reset_n = 0;
	wait_n = 1;
	int_n = 1;
	nmi_n = 1;
	busrq_n = 1;
	di_resp = 0;
	
	for (int c=0; c<10; c++)
		wait();
	reset_n = 1;
	wait();
	printf ("Initialization complete.\n");
}
