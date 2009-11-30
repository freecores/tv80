#ifndef TV_RESPONDER_H_
#define TV_RESPONDER_H_

#include "sc_env.h"

SC_MODULE(tv_responder)
{
	sc_in<bool>   clk;
	
	sc_out<bool>	reset_n;
	sc_out<bool>	wait_n;
	sc_out<bool>	int_n;
	sc_out<bool>	nmi_n;
	sc_out<bool>	busrq_n;
	sc_in<bool>	m1_n;
	sc_in<bool>	mreq_n;
	sc_in<bool>	iorq_n;
	sc_in<bool>	rd_n;
	sc_in<bool>	wr_n;
	sc_in<bool>	halt_n;
	sc_in<bool>	busak_n;
	sc_out<uint32_t>	di_resp; 
	sc_in<uint32_t>	dout;
	sc_in<uint32_t>	addr;
	
	void event();
	
	SC_CTOR(tv_responder) {
		SC_THREAD(event);
		sensitive << clk.pos();
	}
};
	
#endif /*TV_RESPONDER_H_*/
