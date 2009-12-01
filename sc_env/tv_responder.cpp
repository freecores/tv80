#include "tv_responder.h"

void tv_responder::event ()
{
	// init
	//reset_n = 0;
	/*
	wait_n = 1;
	int_n = 1;
	nmi_n = 1;
	busrq_n = 1;
	di_resp = 0;
	*/
	
	if (reset_time > 0) {
		reset_n = 0;
	    wait_n = 1;
		int_n = 1;
		nmi_n = 1;
		busrq_n = 1;
		di_resp = 0;
		reset_time--;
		if (reset_time == 0)
			printf ("Initialization complete.\n");
		return;
	} else {
		if (reset_time == 0) {
			reset_n = 1;
			reset_time--;
		}
	}
		
	
    if (!iorq_n & !rd_n)
        {
          switch (addr) {
            case (0x82) : di_resp = timeout_ctl; break;
	  		case(0x83) : di_resp = max_timeout & 0xff; break;
	   		case(0x84) : di_resp = max_timeout >> 8; break;

	    	case(0x90) : di_resp = int_countdown; break;
            case(0x91) : di_resp = checksum; break;
            case(0x93) : di_resp = ior_value; break;
            case(0x94) : di_resp = rand();  break;
            case(0x95) : di_resp = nmi_countdown; break;
            case(0xA0) : di_resp = nmi_trigger; break;
            default : di_resp = 0;
          }
        } // if (!iorq_n & !rd_n)

//  wire wr_stb;
//  reg last_iowrite;

//  assign wr_stb = (!iorq_n & !wr_n);
  
//  always @(posedge clk)
//   begin
      //last_iowrite <= #1 wr_stb;
    //if (!iorq_n && !wr_n)
    //	printf ("DEBUG:  I/O Write detected addr=%02x\n", 0xff & (int) addr.read());
    	
    if (!iorq_n && !wr_n && !last_iowrite) {
    	int l_dout, l_addr;
    	
    	l_addr = addr.read();
    	l_dout = dout.read();
    	
      	last_iowrite = true;
		switch ( l_addr & 0xff) {
			case(0x80) :
			// dump control deprecated
			if (l_dout == 1) {
				printf ("%8d: --- TEST PASSED ---\n", 0);
				sc_stop();
			} else if (l_dout == 2) {
				printf ("%8d: !!! TEST FAILED !!!\n", 0);
				sc_stop();
			}
			break;

			case(0x81) :
	    
	      		//printf ("%s: DEBUG   : Detected write of character %x\n", sc_time_stamp().to_string(), l_dout);
	      		//cout << sc_time_stamp().to_string() << "DEBUG   : Detected write of character " << l_dout << endl;
	      		if (l_dout == 0x0A) {
					//printf ("%8d: PROGRAM : ", sc_simulation_time());
					cout << sc_time_stamp() << ": PROGRAM : ";

					for (int i=0; i<buf_ptr; i=i+1)
						//printf ("%s", str_buf[i]);
						cout << str_buf[i];
				  
					//printf ("\n");
					cout << endl;
		 			buf_ptr = 0;
				} else {
	      			str_buf[buf_ptr] = (char) (l_dout & 0xff);
	      			buf_ptr = buf_ptr + 1;
	      		}
		    break;

			case(0x82) :
		    	timeout_ctl = l_dout;
				break;

			case(0x83) :
				max_timeout = l_dout | (max_timeout & 0xFF00);
				break;
				
			case(0x84) :
				max_timeout = l_dout << 8 | (max_timeout & 0x00FF);
				break;

			case(0x90) : int_countdown = dout; break;
			case(0x91) : checksum = dout; break;
			case(0x92) : checksum = checksum + dout; break;
			case(0x93) : ior_value = dout; break;
			case(0x95) : nmi_countdown = dout; break;
			case(0xA0) : nmi_trigger = dout; break;
		}
    } else if (iorq_n)
    	last_iowrite = false;

	if (timeout_ctl & 0x2)
		cur_timeout = 0;
    else if (timeout_ctl & 0x1)
		cur_timeout = cur_timeout + 1;

    if (cur_timeout >= max_timeout) {
	  printf ("%8d: ERROR   : Reached timeout %d cycles\n", 0, max_timeout);
	  //tb_top.test_fail;
	  sc_stop();
    }

	if (int_countdown == 0) {
		int_n = 1;
	} else if (int_countdown == 1)
		int_n  = 0;
    else if (int_countdown > 1) {
	  int_countdown = int_countdown - 1;
	  int_n  = 1;
    }

    // when nmi countdown reaches 1, an NMI will be issued.
    // to clear the interrupt, write nmi_countdown to 0.
    if ((nmi_countdown == 0) && (nmi_trigger == 0))
		nmi_n = 1;
    else if (nmi_countdown == 1)
		nmi_n = 0;
    else if (nmi_countdown > 1) {
		nmi_countdown = nmi_countdown - 1;
		nmi_n = 1;
    }

    // when IR equals the target instruction, an NMI will be
    // issued.  To clear the interrupt, write nmi_trigger to
    // zero.
    /*  can't do this in systemc
    if (nmi_trigger != 0) {
          if (nmi_trigger === tb_top.tv80s_inst.i_tv80_core.IR[7:0])
            begin
              tb_top.nmi_n <= #80 0;
              tb_top.nmi_n <= #160 1;
            end
    } else if (nmi_countdown == 0)
        nmi_n = 1;
     */
}
