.PHONY: all
all:	algorithm

CC=g++
CPPFLAG=-c -g

PROJECT_ROOT = $(PWD)
INCLUDE_PATH=-I${PROJECT_ROOT}/include
LIB_PATH=-L${PROJECT_ROOT}/lib

DEPS = $(INCLUDE_PATH)/common.h

_OBJS := 
_OBJS += libAlgorithm.o
_OBJS += libHeap.o
_OBJS += libRmq.o
_OBJS += libIndexTree.o

OBJDIR = $(PROJECT_ROOT)/src/obj
SRCDIR = $(PROJECT_ROOT)/src
OBJS = $(patsubst %, $(OBJDIR)/%, $(_OBJS))

# generate the final target
algorithm: $(OBJS)
	$(CC) -o la  $(INCLUDE_PATH) $(LIB_PATH) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -o $@ $(CPPFLAG) $< $(INCLUDE_PATH)

.PHONY: clean
clean:
	find $(PROJECT_ROOT) -name *.o | xargs rm
	rm la
