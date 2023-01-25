# Specify the compiler and any flags
CXX = g++
CXXFLAGS = -g -pedantic -m64 -Wall -Werror -O2 -std=c++17

#Folders
BIN = bin
SRC = src

#Programs
PROG = roguelike
# Specify the target executables
TARGETS = $(addprefix $(BIN)/, $(PROG))

# Use the wildcard function to find all .c and .h files in the src/client and src/server directories
# Specify the object files for each target

$(foreach prog, $(PROG), \
$(eval $(prog)_SRC = $(wildcard $(SRC)/*.cpp)) \
$(eval $(prog)_OBJS = $(patsubst %.cpp,%.o,$($(prog)_SRC))) \
$(eval $(prog)_DEPS = $(patsubst %.cpp,%.d,$($(prog)_SRC))))

-include $(foreach prog, $(PROG), $($(prog)_DEPS))

#build all
.PHONY: all
all: $(BIN) $(TARGETS) $(foreach prog, $(PROG), $($(prog)_OBJS))

#build objects
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -std=c++17 -c $< -o $@

#create binaries directories if not exists

$(BIN):
	mkdir $(BIN)

#define building
define make-target
$(BIN)/$(1): $$($1_OBJS)
endef

$(info $(PROG))
$(info $(TARGETS))
#Create compiling rules
$(foreach prog,$(PROG), $(eval $(call make-target,$(prog))))

$(TARGETS):
	$(CXX) $(CXXFLAGS) $^ -o $@

# Create a rule to clean up the built executables and object files
.PHONY: clean
clean:
ifeq ($(OS),Windows_NT)
	del /F /Q $(BIN)\*
	del /F /s *.o *.d *.elf *.map *.log
else
	rm -f $(BIN)/* $(foreach prog, $(PROG), $($(prog)_OBJS), $($(prog)_DEPS) )
endif
