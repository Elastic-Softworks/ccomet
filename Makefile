#
# 		CCOMET MAKEFILE
#
# 	  CG MOON / ELASTIC WORDS 2025
#
# TARGETS:
#
# all	- (DEFAULT) Builds the library and the example program.
# clean - removes all build artifacts
#         (object files, library, executable)
#

# 	--- CONFIG ---

# 	COMPILER FLAGS

CC 	= i586-pc-msdosdjgpp-gcc
CFLAGS 	= -g -Wall -I$(INCDIR)

#	LINKER FLAGS

LDFLAGS = -Llib -lccomet

#	ARCHIVER

AR	= i586-pc-msdosdjgpp-ar
ARFLAGS = rcs

#	DIRECTORIES

SRCDIR	= src
OBJDIR	= obj
LIBDIR	= lib
BINDIR	= bin
INCDIR	= include

#	--- FILE DEFS ---

LIBRARY 	= libccomet.a
TARGET_LIB	= $(LIBDIR)/$(LIBRARY)
SOURCES		= $(wildcard $(SRCDIR)/*.c)
OBJECTS		= $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

#	--- COMPILE EXAMPLE PROGRAMS ---

EXAMPLE_SRC	= examples/demo.c
EXAMPLE_EXE	= ccomet_test.exe
TARGET_EXE	= $(BINDIR)/$(EXAMPLE_EXE)

#	--- BUILD RULES ---

all: $(TARGET_LIB) $(TARGET_EXE)

$(TARGET_LIB): $(OBJECTS)
	@echo ARCHIVING LIBRARY $@
	@mkdir -p $(LIBDIR)
	$(AR) $(ARFLAGS) $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo COMPILING $<
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET_EXE): $(EXAMPLE_SRC) $(TARGET_LIB)
	@echo COMPILING AND LINKING EXAMPLE $@
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

clean:
	@echo CLEANING UP...
	rm -rf $(OBJDIR) $(LIBDIR) $(BINDIR)/$(EXAMPLE_EXE)

.PHONY: all clean
