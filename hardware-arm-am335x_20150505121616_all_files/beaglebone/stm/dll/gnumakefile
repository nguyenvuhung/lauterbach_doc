# please use GNU MAKE
export SHELLOPTS := igncr


NAME  := pproto
OF    := build
VPATH := . ..
CC    := gcc
COPT  := -Wall
LOPT  :=


ifneq ($(findstring .exe,$(SHELL))$(findstring .EXE,$(SHELL)),)
  ENV_NAME := WINDOWS
  PATH+=;C:\MinGW\bin;C:\MinGW\msys\1.0\bin
  SHELL := C:\MinGW\msys\1.0\bin\bash.exe
else
  ENV_NAME := $(shell uname -s)
endif
$(info $(ENV_NAME))

ifneq ($(findstring CYGWIN,$(ENV_NAME))$(findstring MINGW,$(ENV_NAME))$(findstring WINDOWS,$(ENV_NAME)),)
  BIN  := $(NAME).dll
  LOPT += -def ./pipeproto.def -s
  ifneq ($(findstring CYGWIN,$(ENV_NAME)),)

    PLATFORM ?= $(if $(ProgramW6432)$(PROGRAMW6432),64,32)

    ifeq ($(findstring 64,$(PLATFORM)),64)
      OF  := build64
      CC  := x86_64-w64-mingw32-gcc
      BIN := $(NAME)64.dll
    else
      OF  := build32
      CC  := i686-pc-mingw32-gcc
      VER := $(shell gcc -dumpversion)

      $(info $(subst ., ,$(VER)))

      ifeq ($(firstword $(subst ., ,$(VER))),3)
        CC := gcc -mno-cygwin
      endif
    endif
  endif
else
  BIN  = $(NAME).so.1
endif


.PHONY : all
all: $(OF)/$(BIN)
	cp $(OF)/$(BIN) $(BIN)

$(OF):
	mkdir $@

$(OF)/%.o: %.c pipeproto.h $(MAKEFILE_LIST) | $(OF)
	$(CC) $(addprefix -I,$(VPATH)) -c $(COPT) -o $@ $<

$(OF)/$(BIN): $(OF)/$(NAME).o $(OF)/pipeproto.o
	$(CC) -shared $^ $(LOPT) -o $@

.PHONY : clean
clean:
	rm -rf $(OF)

