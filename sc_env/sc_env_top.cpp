#include "systemc.h"
#include "systemperl.h"
#include "env_memory.h"
#include "tv_responder.h"
#include "Vtv80s.h"
#include "SpTraceVcd.h"

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
	sc_signal<uint32_t> di_mem;
	sc_signal<uint32_t> di_resp;
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
    env_memory0.reset_n (reset_n);
    
    tv_responder tv_resp0("tv_resp0");
    tv_resp0.clk (clk);
    tv_resp0.reset_n (reset_n);
    tv_resp0.wait_n (wait_n);
    tv_resp0.int_n (int_n);
    tv_resp0.nmi_n (nmi_n);
    tv_resp0.busak_n (busak_n);
    tv_resp0.busrq_n (busrq_n);
    tv_resp0.m1_n (m1_n);
    tv_resp0.mreq_n (mreq_n);
    tv_resp0.iorq_n (iorq_n);
    tv_resp0.rd_n (rd_n);
    tv_resp0.wr_n (wr_n);
    tv_resp0.addr (addr);
    tv_resp0.di_resp (di_resp);
    tv_resp0.dout (dout);
    tv_resp0.halt_n (halt_n);

    // create dumpfile
    /*
    sc_trace_file *trace_file;
    trace_file = sc_create_vcd_trace_file("sc_tv80_env");
    sc_trace (trace_file, clk, "clk");
    sc_trace (trace_file, reset_n, "reset_n");
    sc_trace (trace_file, wait_n, "wait_n");
    sc_trace (trace_file, int_n, "int_n");
    sc_trace (trace_file, nmi_n, "nmi_n");
    sc_trace (trace_file, busrq_n, "busrq_n");
    sc_trace (trace_file, m1_n, "m1_n");
    sc_trace (trace_file, mreq_n, "mreq_n");
    sc_trace (trace_file, iorq_n, "iorq_n");
    sc_trace (trace_file, rd_n, "rd_n");
    sc_trace (trace_file, wr_n, "wr_n");
    sc_trace (trace_file, halt_n, "halt_n");
    sc_trace (trace_file, busak_n, "busak_n");
    sc_trace (trace_file, di, "di");
    sc_trace (trace_file, dout, "dout");
    sc_trace (trace_file, addr, "addr");
    
    // Start Verilator traces
    Verilated::traceEverOn(true);
    SpTraceFile *tfp = new SpTraceFile;
    tv80s.trace (tfp, 99);
    tfp->open ("tv80.vcd");
    */

	// check for command line argument
	if (argc > 1) {
		env_memory0.load_ihex (argv[1]);
	}
	
	// set reset to 0 before sim start
	reset_n.write (0);

    sc_start();
    /*
    sc_close_vcd_trace_file (trace_file);
    tfp->close();
    */
    
    
    return 0;
}
