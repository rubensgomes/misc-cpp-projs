######################################################################
##
## Copyright: Copyright (C) 2016 Rubens Gomes <rubens.s.gomes@gmail.com>
##      File:  Rules.mk
##   Created:  03/07/2016
##    Author:  Rubens S. Gomes
##
##  Abstract:  This file defines rules for make.
##
##
## IMPORTANT:  You must use the GNUMake (/usr/local/bin/make) because
##             the Makefiles use functions and syntax which are only
##             available in the GNUMake.
##
ifndef RULES_MK
RULES_MK:=1

.PHONY: default all clean clobber install uninstall

##
## only take the significant suffixes described in the second line.
##
.SUFFIXES:
.SUFFIXES: .cpp .o

##
## protect source and dependent files
##
.PRECIOUS: %.hpp %.cpp $(DEP_DIR)/%.d

clobber: clean

# compiling rule
%.o: %.cpp
	$(CXX) $(DEP_FLAGS) $(CXX_FLAGS) -o $@ $<  
	$(POSTCOMPILE)

# dependency rule
$(DEP_DIR)/%.d: ;

-include $(patsubst %,$(DEP_DIR)/%.d,$(basename $(SRCS)))

endif # ifndef RULES_MK
######################################################################
