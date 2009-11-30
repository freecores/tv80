#include "env_memory.h"
#include <stdio.h>

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

void inline readline(FILE *fh, char *buf)
{
	int c = 1;
	
	while (c) {
		c = fread (buf, 1, 1, fh);
		if (c && (*buf == '\n'))
			c = 0;
		else buf++;
	}
}

/*
        line = ifh.readline()
        while (line != ''):
            if (line[0] == ':'):
                rlen = int(line[1:3], 16)
                addr = int(line[3:7], 16)
                rtyp = int(line[7:9], 16)
                ptr = 9
                for i in range (0, rlen):
                    laddr = addr + i
                    val = int(line[9+i*2:9+i*2+2], 16)
                    self.map[laddr] = val
                    self.bcount += 1
                    if (laddr > self.max): self.max = laddr
                    if (laddr < self.min): self.min = laddr

            line = ifh.readline()
 */
 void env_memory::load_ihex(char *filename)
{
	FILE *fh;
	char line[80];
        char *lp;
        int rlen, addr, rtyp;
	
	fh = fopen (filename, "r");
	
	readline (fh, line);
        while (strlen(line) > 0) {
          printf ("DEBUG: strlen(line)=%d\n", strlen(line));
          sscanf (line, "%2x%2x%2x", &rlen, &addr, &rtyp);
          printf ("DEBUG: rlen=%d addr=%d rtyp=%d\n", rlen, addr, rtyp);
          lp = line + 6;
          for (int c=0; c<rlen; c++) {
          }
        }
	
	fclose (fh);
}
