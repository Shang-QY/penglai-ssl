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

#include "tcommon.h"
#include "sgx_tsgxssl_t.h"

extern "C" {

void * sgxssl_mmap (void *addr, size_t len, int prot, int flags, int fd, __off_t offset)
{
	FSTART;

	SGX_UNREACHABLE_CODE(SET_ERRNO);
	FEND;

	return NULL;
}

int sgxssl_munmap (void *addr, size_t len)
{
	FSTART;

	SGX_UNREACHABLE_CODE(SET_ERRNO);
	FEND;

	return -1;
}

int sgxssl_mprotect (void *addr, size_t len, int prot)
{
	FSTART;

	SGX_UNREACHABLE_CODE(SET_ERRNO);
	FEND;

	return -1;
}

int sgxssl_madvise (void *addr, size_t len, int advice)
{
	FSTART;

	SGX_UNREACHABLE_CODE(SET_ERRNO);
	FEND;

	return -1;
}

int sgxssl_mlock (const void *__addr, size_t __len)
{
	FSTART;
    // Silently ignore - doesn't impact the application semantic.
    FEND;
	return 0;
}

}
