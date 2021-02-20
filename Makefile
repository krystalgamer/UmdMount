TARGET = umdmount
OBJS = main.o 

BUILD_PRX=1

INCDIR = 
CFLAGS = -Os -G0 -Wall 
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

PSP_FW_VERSION = 620
PRX_EXPORTS = exports.exp

LIBS = -lpspsystemctrl_kernel
LIBDIR = .
LDFLAGS =

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build_prx.mak
