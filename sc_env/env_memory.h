#include "systemc.h"

#ifndef ENV_MEMORY_H
#define ENV_MEMORY_H
#define AM_ASZ 16
#define AM_DEPTH (1<<16)

SC_MODULE(env_memory) {

  sc_in<bool > clk;  
  sc_in<uint32_t> wr_data;
  sc_in<bool> mreq_n;
  sc_in<bool> rd_n;
  sc_in<bool> wr_n;
  sc_in<uint32_t> addr;
  sc_out<uint32_t> rd_data; 

  unsigned char *memory;

  void event();

  SC_CTOR(env_memory) {
  	memory = new unsigned char[AM_DEPTH];
    SC_METHOD(event);
    sensitive_pos << clk;
  }
};

#endif