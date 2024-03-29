#
# Copyright (C) 2011-2018 Intel Corporation. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
#   * Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#   * Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in
#     the documentation and/or other materials provided with the
#     distribution.
#   * Neither the name of Intel Corporation nor the names of its
#     contributors may be used to endorse or promote products derived
#     from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#

include ../buildenv.mk

CXXFLAGS  += -Werror
CFLAGS	+= -Werror 

EPID_SDK_DIR := $(LINUX_EXTERNAL_DIR)/epid-sdk/
INCLUDE += -I$(LINUX_PSW_DIR)/ae/data/constants/linux 

INCLUDE += -I$(COMMON_DIR)/inc/tlibc                      \
		   -I$(SGX_IPP_INC)/                              \
		   -I$(EPID_SDK_DIR)                              \
		   -I$(LINUX_PSW_DIR)/ae/common                   \
		   -I$(LINUX_PSW_DIR)/ae/pve                      \
		   -I$(LINUX_PSW_DIR)/ae/inc/internal             \
		   -I../ascommon
				
TCRYPTO_LIBDIR := $(LINUX_SDK_DIR)/tlibcrypto
EPID_LIBDIR	   := $(EPID_SDK_DIR)

EXTERNAL_LIB += -L$(EPID_LIBDIR)/epid/member -lmember \
				-L$(EPID_LIBDIR)/epid/verifier -lverifier \
				-L$(EPID_LIBDIR)/epid/common -lcommon \
				-L$(TCRYPTO_LIBDIR) -lsgx_tcrypto


SRC := $(wildcard *.cpp)
SRC += pve_qe_common.cpp 			\
	   ../ascommon/as_util.cpp


OBJ := $(SRC:.cpp=.o)
OBJS := $(sort $(OBJ) version.o)

SIGNED_SONAME = $(AENAME).signed.so

.PHONY: all
all: $(SONAME) 

.PHONY: EPID
EPID:
	cd $(EPID_SDK_DIR) && ./configure prefix=/usr/local
	$(MAKE) -C $(EPID_SDK_DIR) 2> /dev/null


$(SONAME): $(OBJS) EPID
	$(CXX) $(CXXFLAGS) -o $@  $(OBJS)  -nostdlib -nodefaultlibs -nostartfiles $(LDTFLAGS) -fno-exceptions -fno-rtti $(EXTERNAL_LIB)  -lsgx_tcxx -lsgx_tstdc -lsgx_mage -lsgx_tcrypto
	$(STRIP)  --strip-unneeded $(SONAME)

$(OBJ): $(AENAME)_t.c $(AENAME)_u.c
$(OBJ): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -fno-exceptions -fno-rtti $(INCLUDE) $(DEFINES) -c $< -o $@

$(AENAME)_t.c: $(EDLFILE)
	@$(EDGER8R) --search-path $(COMMON_DIR)/inc --trusted $<
	
$(AENAME)_u.c: $(EDLFILE)
	@$(EDGER8R) --search-path $(COMMON_DIR)/inc --untrusted $<

.PHONY: clean
clean:
	@$(RM) *.o
	@$(RM) *.so
	@$(RM) *.map
	@$(RM) *_t.*
	@$(RM) *_u.*
ifeq ("$(shell test -f $(EPID_SDK_DIR)/Makefile && echo Makefile exists)", "Makefile exists")
	-$(MAKE) -C $(EPID_SDK_DIR) clean
endif
	@$(RM) -r $(EPID_SDK_DIR)/Makefile $(EPID_SDK_DIR)/config.log $(EPID_SDK_DIR)/config.status

.PHONY: rebuild
rebuild:
	$(MAKE) clean
	$(MAKE) all
