######################################################################
##
## Copyright:  Copyright (C) 2016 Rubens Gomes <rubens.s.gomes@gmail.com>
##      File:  Defs.mk
##   Created:  03/07/2006
##    Author:  Rubens S. Gomes
##
##  Abstract:  This file defines constant variables, vpaths
##             that remain constant throught the make process.  This
##             file only needs to be included once in the make process.
##
##      Note:  This file should NOT be changed.  If there is a need
##             to override any of the parameters specified here, you may
##             do so on the system prompt by doing the following:
##             $ make <VARIABLE>=<VALUE>
##
## IMPORTANT:  You must use the GNUMake (/usr/local/bin/make) because
##             the Makefiles use functions and syntax which are only
##             available in the GNUMake.
##

ifndef DEFS_MK
DEFS_MK:=1

######################################################################
#########################  V A R I A B L E S #########################
######################################################################

##
## Shell variables to be used by make.
##
AR      := /bin/ar
AWK     := /bin/awk
CD      := /bin/cd
CHMOD   := /bin/chmod
CP      := /bin/cp
CXX     := /bin/g++
ECHO    := /bin/echo
FALSE   := /bin/false
GREP    := /bin/grep
GZIP    := /usr/local/bin/gzip
MDIR    := /bin/mkdir
MV      := /bin/mv
PWD     := /bin/pwd
RM      := /bin/rm
SED     := /bin/sed
SHELL   := /bin/sh
TAR     := /usr/local/bin/tar
TEST    := /usr/bin/test
TOUCH   := /bin/touch
TRUE    := /bin/true
WC      := /bin/wc
ZIP     := /usr/local/bin/zip


# unames to identify OS
uname_S := $(shell sh -c 'uname -s 2>/dev/null || echo not')
uname_M := $(shell sh -c 'uname -m 2>/dev/null || echo not')
uname_O := $(shell sh -c 'uname -o 2>/dev/null || echo not')
uname_R := $(shell sh -c 'uname -r 2>/dev/null || echo not')
uname_P := $(shell sh -c 'uname -p 2>/dev/null || echo not')
uname_V := $(shell sh -c 'uname -v 2>/dev/null || echo not')

# boost must be installed in following path
BOOST_DIR := /usr/local/boost_1_60_0

# dependency settings
DEP_DIR     = .depend
DEP_FLAGS   = -MT $@ -MMD -MP -MF $(DEP_DIR)/$*.Td
POSTCOMPILE = $(MV) -f $(DEP_DIR)/$*.Td $(DEP_DIR)/$*.d

# preprocessor macro definitions
# BOOST_ALL_DYN_LINK to dynamic link to the Boost libraries
DEFS = \
  -DBOOST_ALL_DYN_LINK 

ifeq ($(uname_O),Cygwin)
# cancel definitioin of following names to fix
# compiling issue in cygwin
  UNDEF_NAMES = \
    -U__STRICT_ANSI__
else
  UNDEF_NAMES = 
endif

UNDEFS = \
  $(UNDEF_NAMES)

# preprocessor header files search paths
INCLUDES = \
  -I$(CURDIR)/src \
  -I$(CURDIR)/test \
  -I$(BOOST_DIR)

# compiling flags
# -Wextra -pedantic 
CXX_FLAGS = \
  -c -g -Wall -std=c++11 \
  $(DEFS) $(UNDEFS) $(INCLUDES) 

# linking flags
LD_FLAGS = \

# linking libs search paths
LIB_DIRS = \
  -L$(BOOST_DIR)/stage/lib

# linking libs to search
LIBS = \
  -lboost_system \
  -lboost_thread \
  -lboost_log 

# Archive flags
AR_FLAGS   = -rv

# C++ project sources + objects
CXX_SRCDIR = src
CXX_SRCS   = $(wildcard $(CXX_SRCDIR)/*.cpp) 
OBJS       = $(CXX_SRCS:.cpp=.o)

# C++ project test source + objects
TEST_DIR  = test
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp) 
TEST_OBJS = $(TEST_SRCS:.cpp=.o)


endif # ifndef DEFS_MK
######################################################################

