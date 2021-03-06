# give the name of the target
TARGETNAME		:=disk

# directories
SOURCEDIR		:=src
DEBUGDIR		:=bin/debug
RELEASEDIR		:=bin/release
INCLUDEDIR		:=./ ../base/

# Source list
SRC				:=src/fileheader.cpp src/helper.cpp src/contentpage.cpp src/directfile.cpp

# dependency list
DEPENDENCYLIST	:=../base

ifeq ($(OS),Windows_NT)

	CC			:=cl #Compiler
	LNK			:=lib #linker

	FLAGCHAR	:=/
	CCFLAG		:=/EHsc /c /nologo # common compile flags
	LNKFLAG		:=/nologo # common linker flags
	DCCFLAG		:=$(CCFLAG) /Zi /Od /DDEBUG # debug compile flags
	DLNKFLAG	:=$(LNKFLAG) # debug link flags
	RCCFLAG		:=$(CCFLAG) /O2 # release compile flags
	RLNKFLAG	:=$(LNKFLAG) # release link flags

	TARGETEXTN	:=.lib # final target extension
	OBJECTEXTN	:=.obj # object file extension

	OUTCFLAG	:=/Fo
	OUTLFLAG	:=/OUT:
	PDBFLAG		:=/Fd$(DEBUGDIR)/$(TARGETNAME).pdb

else

	CC			:=g++ #Compiler
	LNK			:=ar #linker

	FLAGCHAR	:=-
	CCFLAG		:=-c -std=c++0x -W -Wall -Wextra -pedantic# common compile flags
	LNKFLAG		:=rs # common linker flags
	DCCFLAG		:=$(CCFLAG) -g -DDEBUG # debug compile flags
	DLNKFLAG	:=$(LNKFLAG) # debug link flags
	RCCFLAG		:=$(CCFLAG) -O2 # release compile flags
	RLNKFLAG	:=$(LNKFLAG) # release link flags

	OUTCFLAG	:=-o 
	OUTLFLAG	:= 

	TARGETEXTN	:=.a # final target extension
	OBJECTEXTN	:=.o # object file extension
endif

# debug obj list
DOBJ			:=$(patsubst src/%.cpp, $(DEBUGDIR)/%$(OBJECTEXTN), $(SRC))
# release obj list
ROBJ			:=$(patsubst src/%.cpp, $(RELEASEDIR)/%$(OBJECTEXTN), $(SRC))
# includes
INCLUDES		:=$(patsubst %, $(FLAGCHAR)I%, $(INCLUDEDIR))

# top level rules
debug 	: depdebug selfdebug

selfdebug : $(DEBUGDIR)/$(TARGETNAME)$(TARGETEXTN)

depdebug :
	echo "Making dependencies...";
	for i in $(DEPENDENCYLIST); do \
	make --no-print-directory -C $$i debug; \
	done

release : deprelease selfrelease

selfrelease : $(RELEASEDIR)/$(TARGETNAME)$(TARGETEXTN)

deprelease :
	echo "Making dependencies...";
	for i in $(DEPENDENCYLIST); do \
	make --no-print-directory -C $$i release; \
	done

selfclean	: dselfclean rselfclean

dselfclean	:
	rm -rf $(DEBUGDIR)/*

rselfclean	:
	rm -rf $(RELEASEDIR)/*

clean	: selfclean
	echo "Cleaning dependencies...";
	for i in $(DEPENDENCYLIST); do \
	make --no-print-directory -C $$i clean; \
	done

# helper rules for top rules
$(DEBUGDIR)/$(TARGETNAME)$(TARGETEXTN) : $(DOBJ)
	@$(LNK) $(DLNKFLAG) $(OUTLFLAG)$@ $(DOBJ)

$(RELEASEDIR)/$(TARGETNAME)$(TARGETEXTN) : $(ROBJ)
	@$(LNK) $(RLNKFLAG) $(OUTLFLAG)$@ $(ROBJ)

$(DEBUGDIR)/%$(OBJECTEXTN): src/%.cpp
	@$(CC) $(DCCFLAG) $(INCLUDES) $^ $(OUTCFLAG)$@ $(PDBFLAG)

$(RELEASEDIR)/%$(OBJECTEXTN): src/%.cpp
	@$(CC) $(RCCFLAG) $(INCLUDES) $^ $(OUTCFLAG)$@

# add the rules here for silent execution
.SILENT: debug depdebug selfdebug release deprelease selfrelease selfclean clean dselfclean rselfclean

# set debug to default
.DEFAULT: debug

# set the phony targets
.PHONY: clean selfclean debugselfclean releaseselfclean
