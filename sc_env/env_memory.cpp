#include "env_memory.h"

void env_memory::event()
{
  int lcl_cs;
  int ad;
  
  if (!mreq_n && !wr_n && (addr < AM_DEPTH)) {
  	ad = (int) addr;
    memory[ad] = (unsigned char) wr_data.read();
#ifdef DEBUG
    printf ("Wrote %x to address %x\n", (int) wr_data.read(), ad);
#endif
  } else if (!mreq_n && !rd_n && (addr < AM_DEPTH)) {
  	ad = (int) addr;
  	rd_data.write ( (unsigned int) memory[ad] );
#ifdef DEBUG
    printf ("Read %x from address %x\n", memory[ad], ad);
#endif
  }
}
