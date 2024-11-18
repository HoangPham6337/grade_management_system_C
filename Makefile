# Directories
BINDIR = bin
LIBDIR = lib
OBJDIR = obj
INCDIR = . lib 

# Define the target executable
TARGET = gpa_management

# Compiler 
CC = gcc

# Define flags
OPT = -O1
# Add flags to ensure recompile when source file change
DEPFLAG = -MP -MD
CFLAGS = -Wall -Wextra -g $(foreach D,$(INCDIR),-I$(D)) $(OPT) $(DEPFLAG)

# Full path to executable
TARGET_BIN = $(BINDIR)/$(TARGET)

CFILES = $(foreach C, $(LIBDIR), $(wildcard $(C)/*.c))
OBJECTS= $(CFILES:$(LIBDIR)/%.c=$(OBJDIR)/%.o)
DEPFILES= $(OBJECTS:.o=.d)

# Default objects
all: directories $(TARGET_BIN)

# Ensure the directories exists
directories:
	@test -d $(BINDIR) || mkdir -p $(BINDIR)
	@test -d $(OBJDIR) || mkdir -p $(OBJDIR)

# Link the target with all objects
$(TARGET_BIN): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile .c to .o
$(OBJDIR)/%.o: $(LIBDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -rf $(BINDIR)/* $(OBJDIR)/* $(DEPFILES)

-include $(DEPFILES)

.PHONY: all clean directories
