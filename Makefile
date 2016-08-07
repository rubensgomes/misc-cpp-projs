######################################################################
##
## Copyright:  Copyright (C) 2016 Rubens Gomes <rubens.s.gomes@gmail.com>
##      File:  Makefile
##   Created:  03/07/2016
##    Author:  Rubens S. Gomes
##
##  Abstract:  system top level Makefile.
##
## IMPORTANT:  You must use the GNUMake (/usr/local/bin/make) because
##             the Makefiles use functions and syntax which are only
##             available in the GNUMake.
##
##
.PHONY: default all clean clobber install 

##
## TOPDIR refers to the very top directory of the system, which
##        happens to be the directory where this Makefile is located.
##
TOPDIR= $(shell if [ "$$PWD" != "" ]; then echo $$PWD; else `pwd`; fi)

## 
## Do NOT remove this line.  It includes file with variable definitions
## used to make the Web Based system.
##
include ${TOPDIR}/makefiles/Defs.mk

##
## SUBDIR should contain a list of sub-directories starting from
##        this directory where source code files are located.
##
SUBDIRS = \
  threadpool \
  reactor \
  utility

######################################################################
###########################  T A R G E T S ###########################
######################################################################

###
###  Note:  All the target rules are defined in makefiles/Defs.mk.
###

###  Here is a list of possible targets:
###
###  1) "default target:  compiles everything
###

default all :
	${MAKE_SUBDIRS}

clean:
	${MAKE_SUBDIRS}

include ${TOPDIR}/makefiles/Rules.mk
######################################################################
