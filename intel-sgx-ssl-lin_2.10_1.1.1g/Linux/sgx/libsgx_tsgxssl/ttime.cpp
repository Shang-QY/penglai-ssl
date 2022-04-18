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
#include <assert.h>

#define CLOCK_REALTIME 0
struct timeb
{
   time_t         time;
   unsigned short millitm;
   short          timezone;
   short          dstflag;
};

extern "C" {


time_t sgxssl_time (time_t *timer)
{
	FSTART;

	struct timeb timeptr;
	
	cc_enclave_result_t sgx_ret = u_sgxssl_ftime(&timeptr, sizeof(struct timeb));
	if (sgx_ret != CC_SUCCESS)
	{
		errno = EFAULT;
		timeptr.time = (time_t)-1;
	}

	if (timer != NULL) {
		*timer = timeptr.time;
	}

	FEND;
	return timeptr.time;

}

int sgxssl_gettimeofday(struct timeval *tv, struct timezone *tz)
{
	FSTART;

	if (tz != NULL) {
		// It is unreachable based on the current OpenSSL usage.
		SGX_UNREACHABLE_CODE(SET_ERRNO);
		FEND;
		return -1;
	}

	struct timeb timeptr;
	
	cc_enclave_result_t sgx_ret = u_sgxssl_ftime(&timeptr, sizeof(struct timeb));
	if (sgx_ret != CC_SUCCESS)
	{
		errno = EFAULT;
		FEND;
		return -1;
	}

	if (tv != NULL) {
		tv->tv_sec = timeptr.time;
		tv->tv_usec = timeptr.millitm;
	}

	FEND;

	return 0;
}

int sgxssl_clock_gettime(int clk_id, struct timespec *tp)
{
	struct timeval temp_tv;
	FSTART;
	(void)(clk_id);

	if (clk_id != CLOCK_REALTIME) {
		errno = EINVAL;
		SGX_UNREACHABLE_CODE(SET_ERRNO);
		FEND;
		return -1;
	}

	if (sgxssl_gettimeofday(&temp_tv, NULL) != 0) {
		return -1;
	}

	tp->tv_sec = temp_tv.tv_sec;
	tp->tv_nsec = temp_tv.tv_usec / 1000;
	FEND;

	return 0;
}

}
