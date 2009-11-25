#include "systemc.h"
#include "env_memory.h"
#include "Vtv80s.h"

int sc_main(int argc, char *argv[])
{
	sc_clock clk("clk125", 8, SC_NS, 0.5, 0.0, SC_NS);

	sc_signal<bool>	reset_n;
	sc_signal<bool>	wait_n;
	sc_signal<bool>	int_n;
	sc_signal<bool>	nmi_n;
	sc_signal<bool>	busrq_n;
	sc_signal<bool>	m1_n;
	sc_signal<bool>	mreq_n;
	sc_signal<bool>	iorq_n;
	sc_signal<bool>	rd_n;
	sc_signal<bool>	wr_n;
	sc_signal<bool>	rfsh_n;
	sc_signal<bool>	halt_n;
	sc_signal<bool>	busak_n;
	sc_signal<uint32_t>	di;
	sc_signal<uint32_t>	dout;
	sc_signal<uint32_t>	addr;
	
	Vtv80s tv80s ("tv80s");
	tv80s.A (addr);
	tv80s.reset_n (reset_n);
	tv80s.clk (clk);
	tv80s.wait_n (wait_n);
	tv80s.int_n (int_n);
	tv80s.nmi_n (nmi_n);
	tv80s.busrq_n (busrq_n);
	tv80s.m1_n (m1_n);
	tv80s.mreq_n (mreq_n);
	tv80s.iorq_n (iorq_n);
	tv80s.rd_n (rd_n);
	tv80s.wr_n (wr_n);
	tv80s.rfsh_n (rfsh_n);
	tv80s.halt_n (halt_n);
	tv80s.busak_n (busak_n);
	tv80s.di (di);
	tv80s.dout (dout);
	
    env_memory env_memory0("env_memory0");
    env_memory0.clk (clk);
    env_memory0.wr_data (dout);
    env_memory0.rd_data (di);
    env_memory0.mreq_n (mreq_n);
    env_memory0.rd_n (rd_n);
    env_memory0.wr_n (wr_n);
    env_memory0.addr (addr);

    sc_start(8000);
    return 0;
}