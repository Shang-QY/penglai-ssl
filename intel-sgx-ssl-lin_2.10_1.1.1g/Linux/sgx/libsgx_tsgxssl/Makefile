#
# Copyright (C) 2011-2020 Intel Corporation. All rights reserved.
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
include ../../buildenv.mk
include ../buildenv.mk
######## SGX SDK Settings ########
SGX_MODE ?= HW
SGX_ARCH ?= x64


ifeq ($(shell getconf LONG_BIT), 32)
	SGX_ARCH := x86
else ifeq ($(findstring -m32, $(CXXFLAGS)), -m32)
	SGX_ARCH := x86
endif

SGX_COMMON_CFLAGS := -Wall

# please set penglai_sdk path
PENGLAI_SDK_DIR := /root/dev/sdk
PENGLAI_SDK_INCLUDE_DIR := ${PENGLAI_SDK_DIR}/lib/app/include
SECGEAR_DIR := /root/dev/secGear
SECGEAR_INCLUDE_DIR := $(SECGEAR_DIR)/inc

SGX_EDL_FILE := $(PACKAGE_INC)/sgx_tsgxssl.edl

Sgx_tssl_Cpp_Files := $(sort $(wildcard *.cpp))
Sgx_tssl_C_Files := $(sort $(wildcard *.c))
Sgx_tssl_S_Files := $(sort $(wildcard *.S))

Sgx_tssl_Cpp_Objects := $(addprefix $(OBJDIR)/, $(Sgx_tssl_Cpp_Files:.cpp=.o))
Sgx_tssl_C_Objects := $(addprefix $(OBJDIR)/, $(Sgx_tssl_C_Files:.c=.o))
Sgx_tssl_S_Objects := $(addprefix $(OBJDIR)/, $(Sgx_tssl_S_Files:.S=.o))

Sgx_tssl_Include_Paths := -I. -I$(PACKAGE_INC) -I $(PENGLAI_SDK_INCLUDE_DIR) \
	-I $(SECGEAR_INCLUDE_DIR)/host_inc	\
	-I $(SECGEAR_INCLUDE_DIR)/host_inc/penglai	\
	-I $(SECGEAR_INCLUDE_DIR)/enclave_inc	\
    -I $(SECGEAR_INCLUDE_DIR)/enclave_inc/penglai

Common_C_Cpp_Flags := $(SGX_COMMON_CFLAGS) -fdata-sections -ffunction-sections -Os -Wl,--gc-sections -fvisibility=hidden -fpie -fpic -fstack-protector -fno-builtin-printf -Wformat -Wformat-security $(Sgx_tssl_Include_Paths)
Sgx_tssl_C_Flags := $(Common_C_Cpp_Flags) $(MITIGATION_CFLAGS)
Sgx_tssl_Cpp_Flags := $(Common_C_Cpp_Flags) -std=c++11 -nostdinc++ $(MITIGATION_CFLAGS)
$(shell mkdir -p $(OBJDIR))

.PHONY: all run

all: $(TRUSTED_LIB)

######## sgx_tsgxssl Objects ########
sgx_tsgxssl_t.c: $(SGX_EDL_FILE)
	codegen --penglai --header-only --trusted $(SGX_EDL_FILE)
	@echo "GEN  =>  $@"

sgx_tsgxssl_t.o: sgx_tsgxssl_t.c
	$(VCC) $(Sgx_tssl_C_Flags) -c $< -o $@
	@echo "CC   <=  $<"

$(OBJDIR)/%.o : %.cpp
	$(VCXX) $(Sgx_tssl_Cpp_Flags) -c $< -o $@
	@echo "CXX  <=  $<"

$(OBJDIR)/%.o : %.c
	$(VCC) $(Sgx_tssl_C_Flags) -c $< -o $@
	@echo "CC  <=  $<"

$(OBJDIR)/%.o : %.S
	$(VCC) $(Common_C_Cpp_Flags) -c $< -o $@
	@echo "CC  <=  $<"

$(TRUSTED_LIB): sgx_tsgxssl_t.c $(Sgx_tssl_Cpp_Objects) $(Sgx_tssl_C_Objects) $(Sgx_tssl_S_Objects)
	ar rcs $(TRUSTED_LIB) $(Sgx_tssl_Cpp_Objects) $(Sgx_tssl_C_Objects) $(Sgx_tssl_S_Objects) 
	@echo "LINK =>  $@"
	@cp $@ $(PACKAGE_LIB)/$(TRUSTED_LIB)

clean:
	@rm -f libsgx_tsgxssl.* libsgx_tsgxssld.* sgx_tsgxssl_t.* $(Sgx_tssl_Cpp_Objects) $(Sgx_tssl_C_Objects) $(Sgx_tssl_S_Objects)
	
