ifeq ($(TARGET), 1)
OUT_TARGET = libF87CD666E6314B33B2B4508FDCD4BE15.a
ifeq ($(DEBUG), 1)
CONFIG_TARGET = StaticDebug
CCFLAGS_TARGET = -Wall -O3 -g -DECO_LIB
LDFLAGS_TARGET =
else
CONFIG_TARGET = StaticRelease
CCFLAGS_TARGET = -O3 -DECO_LIB
LDFLAGS_TARGET =
endif
else
OUT_TARGET = F87CD666E6314B33B2B4508FDCD4BE15.so
ifeq ($(DEBUG), 1)
CONFIG_TARGET = DynamicDebug
CCFLAGS_TARGET = -Wall -O3 -fPIC -g -DECO_DLL
LDFLAGS_TARGET = -shared
else
CONFIG_TARGET = DynamicRelease
CCFLAGS_TARGET = -O3 -fPIC -DECO_DLL
LDFLAGS_TARGET = -shared
endif
endif

SRC = \
../../../SourceFiles/CEcoLab2.c \
../../../SourceFiles/CEcoLab2Factory.c

INCLUDES = \
-I ../../../HeaderFiles \
-I ../../../SharedFiles \
-I $(ECO_FRAMEWORK)/Eco.Core1/SharedFiles \
-I $(ECO_FRAMEWORK)/Eco.InterfaceBus1/SharedFiles \
-I $(ECO_FRAMEWORK)/Eco.MemoryManager1/SharedFiles \
-I $(ECO_FRAMEWORK)/Eco.FileSystemManagement1/SharedFiles

OBJ = $(SRC:.c=.o)

OUT = $(OUT_TARGET)
OUT_DIR = ../../../BuildFiles/Linux/x86_64/$(CONFIG_TARGET)

CC = gcc
AR = gcc-ar
RM = rm -f

CCFLAGS = $(CCFLAGS_TARGET) -DECO_LINUX -DECO_X86_64 -DUGUID_UTILITY
LDFLAGS = $(LDFLAGS_TARGET)
LIBS = -lc -lm -lgcc

ifeq ($(TARGET), 1)
CMD_TARGET = $(AR) rcs
LIBS =
else
CMD_TARGET = $(CC) -o
endif

.PHONY: all clean

all: $(OUT)

%.o: %.c
	$(CC) $(INCLUDES) $(CCFLAGS) -c $< -o $@

$(OUT): $(OBJ)
	mkdir -p $(OUT_DIR)
	$(CMD_TARGET) $(OUT_DIR)/$(OUT) $(OBJ) $(LDFLAGS) $(LIBS)
	$(RM) $(OBJ)

clean:
	$(RM) $(OBJ) $(OUT_DIR)/$(OUT)
