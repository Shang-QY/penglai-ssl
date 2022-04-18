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

int sgxssl_pthread_rwlock_init (pthread_rwlock_t *rwlock, const pthread_rwlockattr_t * attr)
{
	FSTART;

	SGX_UNREACHABLE_CODE(SET_ERRNO);
	FEND;

	return -1;
}

int sgxssl_pthread_rwlock_destroy (pthread_rwlock_t *rwlock)
{
	FSTART;

	SGX_UNREACHABLE_CODE(SET_ERRNO);
	FEND;

	return -1;
}

int sgxssl_pthread_rwlock_rdlock (pthread_rwlock_t *rwlock)
{
	FSTART;

	SGX_UNREACHABLE_CODE(SET_ERRNO);
	FEND;

	return -1;
}


int sgxssl_pthread_rwlock_wrlock (pthread_rwlock_t *rwlock)
{
	FSTART;

	SGX_UNREACHABLE_CODE(SET_ERRNO);
	FEND;

	return -1;
}

int sgxssl_pthread_rwlock_unlock (pthread_rwlock_t *rwlock)
{
	FSTART;

	SGX_UNREACHABLE_CODE(SET_ERRNO);
	FEND;

	return -1;
}

int sgxssl_pthread_once (pthread_once_t *once_control, void (*init_routine) (void))
{
	FSTART;

	SGX_UNREACHABLE_CODE(SET_ERRNO);
	FEND;

	return -1;
}

int sgxssl_pthread_key_create (pthread_key_t *key, void (*destr_function) (void *))
{
	FSTART;

	SGX_UNREACHABLE_CODE(SET_ERRNO);
	FEND;

	return -1;
}

int sgxssl_pthread_key_delete (pthread_key_t key)
{
	FSTART;

	SGX_UNREACHABLE_CODE(SET_ERRNO);
	FEND;

	return -1;
}

void * sgxssl_pthread_getspecific (pthread_key_t key)
{
	FSTART;

	SGX_UNREACHABLE_CODE(SET_ERRNO);
	FEND;

	return NULL;
}

int sgxssl_pthread_setspecific (pthread_key_t key, const void *data)
{
	FSTART;

	SGX_UNREACHABLE_CODE(SET_ERRNO);
	FEND;

	return -1;
}

pthread_t sgxssl_pthread_self (void)
{
	FSTART;

	SGX_UNREACHABLE_CODE(SET_ERRNO);
	FEND;

	return -1;
}

//Thread forking isn't supported inside enclave.
int sgxssl_pthread_atfork(void (*prepare)(void), void (*parent)(void), void (*child)(void))
{
    FSTART;
    SGX_UNREACHABLE_CODE(SET_ERRNO);

    FEND;
    //Operation not permitted
    return EPERM;
}

// Return 0 if the threads are not equal
int sgxssl_pthread_equal (pthread_t thread1, pthread_t thread2)
{
	FSTART;
	
	int retval = 0;

	if (thread1 == thread2)
		retval = 1;

	FEND;

	return retval;
}

}

