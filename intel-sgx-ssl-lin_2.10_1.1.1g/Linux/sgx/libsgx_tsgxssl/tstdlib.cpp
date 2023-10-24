/*
 * Copyright (C) 2011-2017 Intel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Intel Corporation nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <string.h>
#include "tcommon.h"
#include "tSgxSSL_api.h"


#ifndef SE_SIM

// following definition is copied from common/inc/internal/se_cdefs.h

#define SGX_ACCESS_VERSION(libname, num)                    \
    extern "C" const char *sgx_##libname##_version;          \
    const char * __attribute__((destructor)) libname##_access_version_dummy##num()      \
    {                                                       \
        return sgx_##libname##_version;                     \
    } 


// add a version to libsgx_tsgxssl
SGX_ACCESS_VERSION(tssl, 1);

#endif

#define PATH_DEV_NULL				"/dev/null"

extern "C" {

#define MAX_ENV_BUF_LEN 4096
static char t_env_buf[MAX_ENV_BUF_LEN];

char *sgxssl_getenv(const char *name)
{
    FSTART;
    int ret = 0;
    int res;
    int buf_len = 0;
    
    if (t_env_buf == NULL || MAX_ENV_BUF_LEN <= 0) {
        FEND;
        return NULL;
    }
   
    memset(t_env_buf, 0, MAX_ENV_BUF_LEN);
    res = ocall_cc_getenv(&ret, name, strlen(name), t_env_buf, MAX_ENV_BUF_LEN, &buf_len);
    if (res != CC_SSL_SUCCESS || ret <= 0 || ret != buf_len) {
        FEND;
        return NULL;
    }
    FEND;
    return t_env_buf;
}

int sgxssl_atexit(void (*function)(void))
{
	// Do nothing, assuming that registered function does allocations cleanup.
	// This should be fine, as sgx_destroy_enclave cleans everything inside of enclave.
	FSTART;
    FEND;
    return 0;
}

}
