SYSTEMC=/opt/systemc
VERILATOR_ROOT = /opt/verilator/share/verilator
VERIDIR=../obj_dir
INCLUDES=-I$(SYSTEMC)/include -I$(VERIDIR) -I$(VERILATOR_ROOT)/include
LINKOPT=-L$(SYSTEMC)/lib-linux64 -lsystemc -lm
DEFINES=-DDEBUG
OBJFILES=sc_env_top.o env_memory.o $(VERIDIR)/Vtv80s.o $(VERIDIR)/Vtv80s__Syms.o verilated.o

CXX=g++ -g $(INCLUDES) $(DEFINES)

all: sc_env_top

test: sc_env_top
	./sc_env_top

sc_env_top: $(OBJFILES)
	$(CXX) $^ -o $@ $(LINKOPT)

verilated.o : $(VERILATOR_ROOT)/include/verilated.cpp
	$(CXX) -c $^

$(VERIDIR)/Vtv80s.o:
	(cd $(VERIDIR); make -f Vtv80s.mk Vtv80s.o)

$(VERIDIR)/Vtv80s__Syms.o:
	(cd $(VERIDIR); make -f Vtv80s.mk Vtv80s__Syms.o)

clean:
	rm -f *.o

