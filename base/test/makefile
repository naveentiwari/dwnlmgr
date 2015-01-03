# -------------------------------------------------------------------------------------
# ---------------------------------- Executable makefile ------------------------------
#  ------------------------------------------------------------------------------------

# give the name of the target
TARGETNAME		:=basetest

# directories
DEBUGDIR		:=bin/debug
RELEASEDIR		:=bin/release

# include directory
INCLUDEDIR		:=../

# Source list, list of files that needs to be compiled
SRC				:=src/dlisttest.cpp src/slisttest.cpp src/mempool.cpp

# dependency list, list of directory that contains makefile that needs to be run before
# running the content of this makefile
DEPENDENCYLIST	:=../

# link requirements, libraries that needs to be linked without extension
DLINK			:=../$(DEBUGDIR)/base
RLINK			:=../$(RELEASEDIR)/base

ifeq ($(OS),Windows_NT)

	CC			:=cl #Compiler

	FLAGCHAR	:=/
	CCFLAG		:=/EHsc /c /nologo # common compile flags
	LNKFLAG		:=/nologo# common linker flags
	DCCFLAG		:=$(CCFLAG) /Zi /Od /DDEBUG # debug compile flags
	DLNKFLAG	:=$(LNKFLAG) # debug link flags
	RCCFLAG		:=$(CCFLAG) /O2 # release compile flags
	RLNKFLAG	:=$(LNKFLAG) # release link flags

	TARGETEXTN	:=.exe # final target extension
	OBJECTEXTN	:=.obj # object file extension

	OUTCFLAG	:=/Fo
	OUTLFLAG	:=/Fe
	PDBFLAG		:=/Fd$(DEBUGDIR)/$(TARGETNAME).pdb

	DLINKLIB 	:=$(patsubst %, %.lib, $(DLINK))
	RLINKLIB	:=$(patsubst %, %.lib, $(RLINK))

else

	CC			:=g++ #Compiler

	FLAGCHAR	:=-
	CCFLAG		:=-c# common compile flags
	LNKFLAG		:=# common linker flags
	DCCFLAG		:=$(CCFLAG) -g -DDEBUG # debug compile flags
	DLNKFLAG	:=$(LNKFLAG) # debug link flags
	RCCFLAG		:=$(CCFLAG) -O2 # release compile flags
	RLNKFLAG	:=$(LNKFLAG) # release link flags

	OUTCFLAG	:=-o
	OUTLFLAG	:=-L. -o

	TARGETEXTN	:=# final target extension
	OBJECTEXTN	:=.o # object file extension

	DLINKLIB 	:=$(patsubst %, %.a, $(DLINK))
	RLINKLIB	:=$(patsubst %, %.a, $(RLINK))
endif

# debug obj list
DOBJ			:=$(patsubst src/%.cpp, $(DEBUGDIR)/%$(OBJECTEXTN), $(SRC))
# release obj list
ROBJ			:=$(patsubst src/%.cpp, $(RELEASEDIR)/%$(OBJECTEXTN), $(SRC))

# debug exe list
DEXE			:=$(patsubst src/%.cpp, $(DEBUGDIR)/%$(TARGETEXTN), $(SRC))
# release exe list
REXE			:=$(patsubst src/%.cpp, $(RELEASEDIR)/%$(TARGETEXTN), $(SRC))

# includes
INCLUDES		:=$(patsubst %, $(FLAGCHAR)I%, $(INCLUDEDIR))

# top level rules
debug 	: depdebug selfdebug

selfdebug : $(DEXE)

depdebug :
	for i in $(DEPENDENCYLIST); do \
	make --no-print-directory -C $$i debug; \
	done

release : deprelease selfrelease

selfrelease : $(REXE)

deprelease :
	for i in $(DEPENDENCYLIST); do \
	make --no-print-directory -C $$i release; \
	done

selfclean	: debugselfclean releaseselfclean

debugselfclean	:
	rm -rf $(DEBUGDIR)/*

releaseselfclean	:
	rm -rf $(RELEASEDIR)/*

clean	: selfclean
	for i in $(DEPENDENCYLIST); do \
	make --no-print-directory -C $$i clean; \
	done

# helper rules for top rules

$(DEBUGDIR)/%$(TARGETEXTN): $(DEBUGDIR)/%$(OBJECTEXTN)
	@$(CC) $(DLNKFLAG) $(OUTLFLAG)$@ $^ $(DLINKLIB)

$(RELEASEDIR)/%$(TARGETEXTN): $(RELEASEDIR)/%$(OBJECTEXTN)
	@$(CC) $(RLNKFLAG) $(OUTLFLAG)$@ $^ $(RLINKLIB)

$(DEBUGDIR)/%$(OBJECTEXTN): src/%.cpp
	@echo $^
	@$(CC) $(DCCFLAG) $(INCLUDES) $^ $(OUTCFLAG)$@ $(PDBFLAG)

$(RELEASEDIR)/%$(OBJECTEXTN): src/%.cpp
	@echo $^
	@$(CC) $(RCCFLAG) $(INCLUDES) $^ $(OUTCFLAG)$@

# add the rules here for silent execution
.SILENT: debug depdebug selfdebug release deprelease selfrelease selfclean clean debugselfclean releaseselfclean

# set debug to default
.DEFAULT: debug

# set the phony targets
.PHONY: clean selfclean debugselfclean releaseselfclean
