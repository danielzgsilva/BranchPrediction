CXX = g++
OPT = -O3
#OPT = -g
WARN = -Wall
CFLAGS = $(OPT) $(WARN) $(INC) $(LIB)

# List of all .cpp files
SIM_SRC = main.cpp predictor.cpp smith.cpp bimodal.cpp gshare.cpp hybrid.cpp

# List corresponding compiled object files (.o files)
SIM_OBJ = main.o predictor.o smith.o bimodal.o gshare.o hybrid.o
 
#################################

# default rule

all: sim
	@echo "my work is done here..."
	

# rule for making sim

sim: $(SIM_OBJ)
	$(CXX) -o sim $(CFLAGS) $(SIM_OBJ) -lm
	@echo "-----------DONE WITH SIM-----------"


# generic rule for converting any .cpp file to any .o file
.cpp.o:
	$(CXX) $(CFLAGS)  -c $*.cpp


# type "make clean" to remove all .o files plus the sim binary

clean:
	rm -f *.o sim


# type "make clobber" to remove all .o files (leaves sim binary)

clobber:
	rm -f *.o


