#####################################################################################
###                       ADDING SOMETHING? READ THIS FIRST!                      ###
#####################################################################################
###   When adding a new C file to the source, you must do 2 things: 		      ###
###     - Add the file to the OBJS list below (with a .o extension) 		      ###
###     - If it is in a new directory, Add the directory to the EXTRA_VPATH list  ###
###       below (with a .c extension) 										      ###
###   Remember to add the trailing \ to the end of each line!                     ###
#####################################################################################

### ALL C FILES SHOULD HAVE AN OBJECT FILE LISTED HERE ###
export OBJS :=                                              	\
../src/main.o

### ALL DIRECTORIES WITH SOURCE FILES MUST BE LISTED HERE ###
### THESE ARE WRITTEN RELATIVE TO THE ./ASF/gcc/Makefile FILE ###
export EXTRA_VPATH := \
../../src

###################################################################
###   Compiler Flags and Build-Specific Configuration Options   ###
###################################################################

#Makefile usually uses /bin/sh to evaluate commands, so we need to change it to /bin/bash
#To allow for the if statement in the connect target to execute correctly
SHELL := /bin/bash 

#Path to the child makefile
#This makefile is used to build the ASF files, and is provided by Atmel Start
CHILD_MAKEFILE_PATH := ../ASF/gcc

# Ensure that MK_DIR is set even when none of the checks are hit
export MK_DIR := mkdir -p

# Use gsed on macOS
ifeq ($(shell uname), Darwin)
	SED = gsed
else
	SED = sed
endif

# Get git branch name and commit hash
GIT_AVAILABLE := $(shell git rev-parse > /dev/null 2>&1; echo $$?)
# ^ This is set to the return code of 'git rev-parse' (0 if successful, 1 if not)

ifeq ($(GIT_AVAILABLE),0) # Zero case means we *are* in a git repo
    GIT_BRANCH_NAME := \"$(shell git rev-parse --abbrev-ref HEAD)\"
    GIT_COMMIT_HASH := \"$(shell git rev-parse HEAD | tail -c 8)\"
else
    $(warning Not in a Git repository, proceeding without Git information)
    GIT_BRANCH_NAME := \"NONE\"
    GIT_COMMIT_HASH := \"NONE\"
endif

# Include git branch and commit hash in the build
CFLAGS += -D'GIT_BRANCH_NAME="$(GIT_BRANCH_NAME)"' -D'GIT_COMMIT_HASH="$(GIT_COMMIT_HASH)"'

# Robust error checking
CFLAGS += -Wextra -Werror -Werror=maybe-uninitialized
CFLAGS += -Wshadow -Wnull-dereference -Wduplicated-cond -Wlogical-op -Werror=return-type -Wfloat-equal
CFLAGS += -Wdangling-else -Wtautological-compare
CFLAGS += -fwrapv # Enable fwrapv (wrap on overflow of signed integers) just to be safe
CFLAGS += -fsigned-char # Ensure that char is signed as your average c programmer might expect -- it's actually default unsigned on arm!

# Disable warnings for unused parameters due to ASF functions having unused parameters
CFLAGS += -Wno-unused-parameter #Because some ASF functions have unused parameters, supress this warning

# Build-specific flags
CFLAGS_DEV := -DDEVBUILD
CFLAGS_UNITTEST := -DUNITTEST
CFLAGS_RELEASE := -DRELEASE

### All these variables are exported to the child makefile, and affect its behavior ###
export SUB_DIRS := $(shell for dir in $(EXTRA_VPATH); do echo $$dir | $(SED) 's|\.\./||g'; done)

export DIR_INCLUDES := $(foreach dir,$(EXTRA_VPATH),-I"$(dir)" )

export OBJS_AS_ARGS := $(foreach obj,$(OBJS),$(patsubst ../%,%,$(obj)))

export DEPS_AS_ARGS := $(patsubst %.o,%.d,$(OBJS_AS_ARGS))

all:
	@$(MAKE) -C $(CHILD_MAKEFILE_PATH) CFLAGS=" $(CFLAGS_DEV) $(CFLAGS)" \
	&& cp -f ../ASF/gcc/PVDXos.elf ./src.elf \
	&& arm-none-eabi-objcopy -O binary ./src.elf ./src.bin \
	&& arm-none-eabi-objcopy -O ihex ./src.elf ./src.hex

clean:
	@$(MAKE) -C $(CHILD_MAKEFILE_PATH) clean \
	&& rm -f ./src.elf ./src.bin ./src.hex