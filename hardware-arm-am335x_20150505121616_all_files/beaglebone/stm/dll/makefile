# Make file for Visual C++
# Requires that "nmake", "cl" and "link" are in DOS path
# Call with
#
# nmake -f makefile

COPT = /c /W3

!IFDEF DEBUG
COPT   = /Od /Zi
LOPT   = /DEBUG
OF     = debug
!ELSE
COPT   = /Gd /Ot
LOPT   =
OF     = release
!ENDIF

NAME   = pproto

!IF ("$(PLATFORM)"=="x64")||("$(PLATFORM)"=="X64")
BIN    = $(NAME)64.dll
CPU    = /D_AMD64_=1
OF     = $(OF)64
!ELSE
BIN    = $(NAME)32.dll
CPU    = /D_X86_=1
OF     = $(OF)32
!ENDIF

INCLUDES = .
SEARCH   = {.}

all: $(OF) $(OF)\$(BIN)
	copy $(OF)\$(BIN) $(BIN)

$(OF):
	md $@

$(OF)\$(NAME).obj : $(SEARCH)$$(@B).c $(SEARCH)pipeproto.h makefile
	$(CC) /c /Gs $(COPT) $(CPU) /I$(INCLUDES) /Fd$*.pdb /Fo$@ %s

$(OF)\pipeproto.obj : $(SEARCH)$$(@B).c $(SEARCH)pipeproto.h makefile
	$(CC) /c /Gs $(COPT) $(CPU) /I$(INCLUDES) /Fd$*.pdb /Fo$@ %s

$(OF)\$(BIN): $(OF)\$(NAME).obj $(OF)\pipeproto.obj
	link  $(LOPT) /def:.\pipeproto.def /dll /out:"$@" $**

clean:
	-rd /s /q $(OF)
