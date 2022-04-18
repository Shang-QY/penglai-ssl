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

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>
#include "tcommon.h"
#include "sgx_tsgxssl_t.h"
#include "tSgxSSL_api.h"
#include "tsgxsslio.h"

extern "C" {

static int penglai_vsnprintf(char* out, size_t n, const char* s, va_list vl)
{
    bool format = false;
    bool longarg = false;
    size_t pos = 0;
    for( ; *s; s++)
    {
        if(format)
        {
            switch(*s)
            {
                case 'l':
                    longarg = true;
                    break;
                case 'p':
                    longarg = true;
                    if (++pos < n) out[pos-1] = '0';
                    if (++pos < n) out[pos-1] = 'x';
                case 'x':
                {
                    long num = longarg ? va_arg(vl, long) : va_arg(vl, int);
                    for(int i = 2*(longarg ? sizeof(long) : sizeof(int))-1; i >= 0; i--) {
                        int d = (num >> (4*i)) & 0xF;
                        if (++pos < n) out[pos-1] = (d < 10 ? '0'+d : 'a'+d-10);
                    }
                    longarg = false;
                    format = false;
                    break;
                }
                case 'd':
                {
                    long num = longarg ? va_arg(vl, long) : va_arg(vl, int);
                    if (num < 0) {
                        num = -num;
                        if (++pos < n) out[pos-1] = '-';
                    }
                    long digits = 1;
                    for (long nn = num; nn /= 10; digits++)
                        ;
                    for (int i = digits-1; i >= 0; i--) {
                        if (pos + i + 1 < n) out[pos + i] = '0' + (num % 10);
                        num /= 10;
                    }
                    pos += digits;
                    longarg = false;
                    format = false;
                    break;
                }
                case 's':
                {
                    const char* s2 = va_arg(vl, const char*);
                    while (*s2) {
                        if (++pos < n)
                            out[pos-1] = *s2;
                        s2++;
                    }
                    longarg = false;
                    format = false;
                    break;
                }
                case 'c':
                {
                    if (++pos < n) out[pos-1] = (char)va_arg(vl,int);
                    longarg = false;
                    format = false;
                    break;
                }
                default:
                    break;
            }
        }
        else if(*s == '%')
            format = true;
        else
        if (++pos < n) out[pos-1] = *s;
    }
    if (pos < n)
        out[pos] = 0;
    else if (n)
        out[n-1] = 0;
    return pos;
}

void *sgxssl_fopen(const char *filename, const char *mode)
{
    uint64_t ret = 0;
    int res;

    if (filename == NULL || mode == NULL) {
        return NULL;
    }

    res = ocall_cc_fopen(&ret, filename, strlen(filename) + 1, mode, strlen(mode) + 1);
    if (res != CC_SSL_SUCCESS) {
        return NULL;
    }
    return (void *)ret;
}

int sgxssl_fclose(void *fp)
{
    int ret = -1;
    int res;

    if (fp == NULL) {
        return -1;
    }
    
    res = ocall_cc_fclose(&ret, (uint64_t)fp);
    if (res != CC_SSL_SUCCESS) {
        return -1;
    }
    return ret;
}

int sgxssl_ferror(void *fp)
{
    int ret = -1;
    int res;

    if (fp == NULL) {
        return -1;
    }

    res = ocall_cc_ferror(&ret, (uint64_t)fp);
    if (res != CC_SSL_SUCCESS) {
	return -1;
    }
    return ret;
}

int sgxssl_feof(void *fp)
{
    int ret = 0;
    int res;
    
    if (fp == NULL) {
	return 0;
    }
    
    res = ocall_cc_feof(&ret, (uint64_t)fp);
    if (res != CC_SSL_SUCCESS) {
	return 0;
    }
    return ret;
}

int sgxssl_fflush(void *fp)
{
    int ret = -1;
    int res;

    if (fp == NULL) {
        return -1;
    }

    res = ocall_cc_fflush(&ret, (uint64_t)fp);
    if (res != CC_SSL_SUCCESS) {
        return -1;
    }
    return ret;
}

long sgxssl_ftell(void *fp)
{
    long ret = -1;
    int res;

    if (fp == NULL) {
	return -1;
    }

    res = ocall_cc_ftell(&ret, (uint64_t)fp);
    if (res != CC_SSL_SUCCESS) {
        return -1;
    }
    return ret;
}

int sgxssl_fseek(void *fp, long offset, int origin)
{
    int ret = -1;
    int res;

    if (fp == NULL) {
        return -1;
    }

    res = ocall_cc_fseek(&ret, (uint64_t)fp, offset, origin);
    if (res != CC_SSL_SUCCESS) {
        return -1;
    }
    return ret;
}

int sgxssl_vfprintf(void *fp, const char *format, va_list vl)
{
    if (fp == stdout) {
        char buffer[512];
        int retval;
        penglai_vsnprintf(buffer, 512, format, vl);
        ocall_printf(&retval, buffer);
    }

    return -1;
}

int sgxssl_fprintf(void *fp, const char *format, ...)
{
    if (fp == stdout) {
        va_list vl;
        va_start(vl, format);
        sgxssl_vfprintf(stdout, format, vl);
        va_end(vl);
	    return 0;
    }

    return -1;
}

size_t sgxssl_fread(void *dest, size_t element_size, size_t cnt, void *fp)
{
    size_t ret = 0;
    int res;

    if (fp == NULL || dest == NULL || element_size == 0 || cnt == 0) {
        return 0;
    }
    if (element_size > (SIZE_MAX - 1) / cnt + 1) {
        return 0;
    }

    res = ocall_cc_fread(&ret, dest, element_size * cnt, element_size, cnt, (uint64_t)fp);
    if (res != CC_SSL_SUCCESS) {
        return 0;
    }
    return ret;
}

size_t sgxssl_fwrite(const void *src, size_t element_size, size_t cnt, void *fp)
{
    size_t ret = 0;
    int res;

    if (fp == NULL || src == NULL || element_size == 0 || cnt == 0) {
        return 0;
    }
    if (element_size > (SIZE_MAX - 1) / cnt + 1) {
        return 0;
    }

    res = ocall_cc_fwrite(&ret, src, element_size * cnt, element_size, cnt, (uint64_t)fp);
    if (res != CC_SSL_SUCCESS) {
        return 0;
    }
    return ret;
}

char *sgxssl_fgets(char *dest, int max_cnt, void *fp)
{
    int ret = -1;
    int res;

    if (fp == NULL || dest == NULL || max_cnt <= 0) {
        return NULL;
    }
    
    res = ocall_cc_fgets(&ret, dest, max_cnt, (uint64_t)fp);
    if (res != CC_SSL_SUCCESS || ret < 0) {
        return NULL;
    }
    return dest;
}

int sgxssl_fputs(const char *src, void *fp)
{
    int ret = -1;
    int res;

    if (fp == NULL || src == NULL) {
        return -1;
    }

    res = ocall_cc_fputs(&ret, src, strlen(src) + 1, (uint64_t)fp);
    if (res != CC_SSL_SUCCESS || ret < 0) {
        return -1;
    }
    return ret;
}

int sgx_print(const char *format, ...)
{
	va_list vl;

    va_start(vl, format);
    sgxssl_vfprintf(stdout, format, vl);
    va_end(vl);
    return 0;
}

}
