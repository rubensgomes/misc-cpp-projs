######################################################################
##
## Copyright: Copyright (C) 2016 Rubens Gomes <rubens.s.gomes@gmail.com>
##      File:  Makefile
##   Created:  03/07/2016
##    Author:  Rubens S. Gomes
##
##  Abstract:  threadpool lower directory Makefile
##
##

##############################################################
##  Do not change!
CUR_DIR=threadpool
ifndef TOPDIR
# extract the top directory ...
TOPDIR=$(shell pwd | sed s/\\/${CUR_DIR}//)
endif
include ${TOPDIR}/makefiles/Defs.mk

##
##############################################################

# dependency settings
$(shell $(MDIR) -p $(DEP_DIR))
$(shell $(MDIR) -p $(DEP_DIR)/src)
$(shell $(MDIR) -p $(DEP_DIR)/test)

# the target main application
TARGET = pooltest

# the library
LIBRARY = libthreadpool.a

# linking pattern rule to create target
$(TARGET): $(TEST_OBJS) $(LIBRARY)
	$(CXX) $(LD_FLAGS) $(LIB_DIRS) -o $@ $(TEST_OBJS) $(LIBRARY) $(LIBS)

# archive pattern rule to create library
$(LIBRARY): $(OBJS)
	$(AR) $(AR_FLAGS) $@ $^

default all: $(TARGET) $(LIBRARY)

# cleans build
clean:
	$(RM) -f $(OBJS) $(TARGET) $(TARGET).stackdump
	$(RM) -f $(TEST_OBJS)
	$(RM) -fr $(DEP_DIR)
	$(RM) -f $(LIBRARY)

install: $(LIBRARY) uninstall
	@if $(TEST) ! -d $(INSTALL_DIR)/include/threadpool; then \
		$(MDIR) -p 755 -v $(INSTALL_DIR)/include/threadpool; \
	fi
	@if $(TEST) ! -d $(INSTALL_DIR)/lib; then \
		$(MDIR) -p 755 -v $(INSTALL_DIR)/lib; \
	fi
	$(INSTALL) -m 644 -v -t $(INSTALL_DIR)/include/threadpool $(CXX_HDRS)
	$(INSTALL) -m 644 -v -t $(INSTALL_DIR)/lib $(LIBRARY)

uninstall:
	$(RM) -rfv $(INSTALL_DIR)/include/threadpool
	$(RM) -fv $(INSTALL_DIR)/lib/$(LIBRARY)

include ${TOPDIR}/makefiles/Rules.mk

