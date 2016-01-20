#=======================================================================
# Copyright   : Copyright (C) 2016 Rubens Gomes <rubens.s.gomes@gmail.com>
# Name        : Makefile
# Author      : Rubens Gomes
# Description : GNU Makefile to build C++ projects
#=======================================================================
.PHONY: all clean default depend

.DEFAULT_GOAL = default

clean:
	$(MAKE) -C threadpool clean

depend:
	$(MAKE) -C threadpool depend

default:
	$(MAKE) -C threadpool default

all:
	$(MAKE) -C threadpool all
