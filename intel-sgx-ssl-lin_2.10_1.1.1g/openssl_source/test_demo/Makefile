all: test_lib
	
test_rsa: test_rsa.c
	gcc -o $@ $^ -lcrypto -ldl -lpthread

OPENSSL_INC := ../../Linux/package/include/openssl

test_lib: test_rsa.c ../../Linux/package/lib64/libsgx_tsgxssl_crypto.a
	gcc -o $@ -I$(OPENSSL_INC) $^

clean:
	rm test_rsa test_lib
