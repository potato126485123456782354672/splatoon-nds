include $(DEVKITARM)/ds_rules

TARGET		:=	splatoon_clone
BUILD		:=	build
SOURCES		:=	.
DATA		:=	data
INCLUDES	:=	.

CFLAGS	:=	-g -Wall -O2\
			-march=armv5te -mtune=arm946e-s -fomit-frame-pointer\
			-ffast-math

CXXFLAGS	:=	$(CFLAGS) -fno-rtti -fno-exceptions

ARCH	:=	-mthumb -mthumb-interwork

LINKFLAGS	:=	$(ARCH) -g -mno-fpu -specs=ds_arm9.specs

LIBS	:=	-lnds9

export BASEDIR	:=	$(CURDIR)
export OUTPUT	:=	$(BASEDIR)/$(TARGET)
export DEPSDIR	:=	$(BASEDIR)/$(BUILD)
export VPATH	:=	$(foreach dir,$(SOURCES),$(BASEDIR)/$(dir))
export INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(BASEDIR)/$(dir)) \
					$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
					-I$(DEVKITPRO)/libnds/include

.PHONY: all clean

all: $(TARGET).nds

$(TARGET).nds: $(TARGET).arm9
	@ndstool -c $(TARGET).nds -9 $(TARGET).arm9

$(TARGET).arm9: main.cpp
	@echo Compiling main.cpp...
	@$(CXX) $(CFLAGS) $(CXXFLAGS) $(INCLUDE) $(ARCH) -c main.cpp -o main.o
	@echo Linking...
	@$(CXX) $(LINKFLAGS) main.o $(LIBS) -o $(TARGET).arm9

clean:
	@rm -f *.o *.arm9 *.nds
