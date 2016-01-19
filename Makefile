#=======================================================================
# Name        : Makefile
# Author      : Rubens Gomes
# Copyright   : Copyright (C) 2016 Rubens Gomes <rubens.s.gomes@gmail.com>
# Description : GNU Makefile to build C++ projects
#=======================================================================
.PHONY: clean clobber default all 

.DEFAULT_GOAL = default

clean:
	$(MAKE) -C threadpool clean

clobber:
	$(MAKE) -C threadpool clobber

default:
	$(MAKE) -C threadpool default

all:
	$(MAKE) -C threadpool all
