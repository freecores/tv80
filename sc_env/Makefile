SYSTEMC=/opt/systemc
VERILATOR_ROOT = /opt/verilator/share/verilator
VERIDIR=../obj_dir
INCLUDES=-I$(SYSTEMC)/include -I$(VERIDIR) -I$(VERILATOR_ROOT)/include -I$(SYSTEMPERL)
LINKOPT=-L$(SYSTEMC)/lib-linux64 -lsystemc -lm
DEFINES=-DDEBUG
OBJFILES=sc_env_top.o env_memory.o tv_responder.o z80_decoder.o \
$(VERIDIR)/Vtv80s.o $(VERIDIR)/Vtv80s__Syms.o \
$(VERIDIR)/Vtv80s__Trace.o \
$(VERIDIR)/Vtv80s__Trace__Slow.o \
verilated.o Sp.o
OPT_FAST=-O2

CXX=g++ -g $(OPT_FAST) $(INCLUDES) $(DEFINES)

all: sc_env_top

test: sc_env_top
	./sc_env_top

sc_env_top: $(OBJFILES)
	$(CXX) $^ -o $@ $(LINKOPT)

verilated.o : $(VERILATOR_ROOT)/include/verilated.cpp
	$(CXX) -c $^

$(VERIDIR)/Vtv80s.o:
	make OPT_FAST="$(OPT_FAST)" -f $(VERIDIR)/Vtv80s.mk -C $(VERIDIR) Vtv80s.o
	#(cd $(VERIDIR); make -f Vtv80s.mk Vtv80s.o)

$(VERIDIR)/Vtv80s__Syms.o:
	make OPT_FAST="$(OPT_FAST)" -f $(VERIDIR)/Vtv80s.mk -C $(VERIDIR) Vtv80s__Syms.o
	#(cd $(VERIDIR); make -f Vtv80s.mk Vtv80s__Syms.o)

$(VERIDIR)/Vtv80s__Trace.o:
	(cd $(VERIDIR); make -f Vtv80s.mk Vtv80s__Trace.o)

$(VERIDIR)/Vtv80s__Trace__Slow.o:
	(cd $(VERIDIR); make -f Vtv80s.mk Vtv80s__Trace__Slow.o)

Sp.o: $(SYSTEMPERL)/Sp.cpp
	$(CXX) -I$(SYSTEMPERL) -c $^

clean:
	rm -f *.o
	rm -f ../obj_dir/*.o

