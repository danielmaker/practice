TARGET := wstring_example

INCLUDES := 
LIB_DIR  :=
LIBS     :=

################################################################################

# source files
SOURCES_C   := $(wildcard *.c)
SOURCES_CPP := $(wildcard *.cpp)

# object files
OBJDIR      := objs
OBJS        += $(patsubst %.c,$(OBJDIR)/%.o,$(SOURCES_C))
OBJS        += $(patsubst %.cpp,$(OBJDIR)/%.o,$(SOURCES_CPP))

# Build flags
CC          := gcc
CXX         := g++
LD          := g++
RM          := rm

CFLAGS      := -g $(INCLUDES)
CXXFLAGS    := -g -std=c++11 $(INCLUDES)
LDFLAGS     :=


# build rules
################################################################################
# $@: The file name of the target.
# $^: The names of all them. dependencies, with spaces between them.
# $<: The first dependency
# $?: The dependencies newer than the target, with spaces between them.

.PHONY: all
all: $(TARGET)

include $(wildcard $(OBJDIR)/*.d)

.PHONY: clean
clean:
	$(RM) -f $(OBJS) $(TARGET)


$(TARGET): $(OBJS)
	$(LD) -o $@ $(LDFLAGS) $(LIB_DIR) $(LIBS) $(OBJS)


$(OBJDIR):
	mkdir $@

# C.
$(OBJDIR)/%.o: %.c $(OBJDIR) Makefile
	$(CC) -o $@ $(CFLAGS) -c $<

# CPP.
$(OBJDIR)/%.o: %.cpp $(OBJDIR) Makefile
	$(CXX) -o $@ $(CXXFLAGS) -c $<




