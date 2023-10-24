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
#include <stdint.h>
#include <string.h>
extern "C" {

// [in, size=32]char *buf
int ocall_printf(char *buf)
{
    printf("Enter ocall: %s()\n", __func__);
    printf("%s",buf);
    return 0;
}

unsigned long read_cycles(void)
{
    unsigned long cycles;
    asm volatile ("rdcycle %0" : "=r" (cycles));
    return cycles;
}

uint64_t ocall_cc_fopen(const char *filename, size_t filename_len, const char *mode, size_t mode_len)
{
    // printf("Enter ocall: %s()\n", __func__);
    unsigned long start, end;
    start = read_cycles();
    FILE *file_host = fopen(filename, mode);
    end = read_cycles();
    printf("Host fopen: cycle: %ld\n", end-start);
    
    // printf("FILE* : %lx\n", (uint64_t)file_host);
    return (uint64_t)file_host;
}

int ocall_cc_fclose(uint64_t fp)
{
    // printf("Enter ocall: %s()\n", __func__);
    int ret;
    unsigned long start, end;
    start = read_cycles();
    ret = fclose((FILE *)fp);
    end = read_cycles();
    printf("Host fclose: cycle: %ld\n", end-start);

    return ret;
}

int ocall_cc_ferror(uint64_t fp)
{
    printf("Enter ocall: %s()\n", __func__);
    return ferror((FILE *)fp);
}

int ocall_cc_feof(uint64_t fp)
{
    printf("Enter ocall: %s()\n", __func__);
    return feof((FILE *)fp);
}

int ocall_cc_fflush(uint64_t fp)
{
    printf("Enter ocall: %s()\n", __func__);
    return fflush((FILE *)fp);
}

int ocall_cc_ftell(uint64_t fp)
{
    printf("Enter ocall: %s()\n", __func__);
    return ftell((FILE *)fp);
}

int ocall_cc_fseek(uint64_t fp, long offset, int origin)
{
    // printf("Enter ocall: %s()\n", __func__);
    unsigned long start, end;
    int ret;
    start = read_cycles();
    ret = fseek((FILE *)fp, offset, origin);
    end = read_cycles();
    printf("Host fseek: cycle: %ld\n", end-start);

    return ret;
}

void printHex(unsigned char *c, int n)
{
	int i;
	for (i = 0; i < n; i++) {
		printf("0x%02X, ", c[i]);
		if ((i%4) == 3)
		    printf(" ");

		if ((i%16) == 15)
		    printf("\n");
	}
	if ((i%16) != 0)
		printf("\n");
}

size_t ocall_cc_fread(void *buf, size_t total_size, size_t element_size, size_t cnt, uint64_t fp)
{
    size_t ret = 0;
    unsigned long start, end;
    start = read_cycles();
    
    // printf("Enter ocall: %s()\n", __func__);
    // printf("FILE* : %lx, total_size: %d, element: %d, cnt: %d\n", (uint64_t)fp, total_size, element_size, cnt);
    ret = fread(buf, element_size, cnt, (FILE *)fp);
    end = read_cycles();
    printf("Host fread: cycle: %ld\n", end-start);
    // printf("ret: %ld\n\ncontent: \n", ret);
    // printHex((unsigned char *)buf, ret);
    return ret;
}

size_t ocall_cc_fwrite(const void *buf, size_t total_size, size_t element_size, size_t cnt, uint64_t fp)
{
    // printf("Enter ocall: %s()\n", __func__);
    size_t ret = 0;
    unsigned long start, end;
    start = read_cycles();
    ret = fwrite(buf, element_size, cnt, (FILE *)fp);
    end = read_cycles();
    printf("Host fwrite: cycle: %ld\n", end-start);

    return ret;
}

int ocall_cc_fgets(char *str, int max_cnt, uint64_t fp)
{
    printf("Enter ocall: %s()\n", __func__);
    printf("FILE* : %lx\n", (uint64_t)fp);
    if (fgets(str, max_cnt, (FILE *)fp) != NULL) {
        printf("strlen: %ld\n\ncontent: %s\n", strlen(str), str);
        return 0;
    } else {
        return -1;
    }
}

int ocall_cc_fputs(const char *str, size_t total_size, uint64_t fp)
{
    printf("Enter ocall: %s()\n", __func__);
    return fputs(str, (FILE *)fp);
}
}
