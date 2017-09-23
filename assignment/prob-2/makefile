CC = cc

CFLAGS  = -std=c99
CFLAGS += -fopenmp
CFLAGS += -Wall
CFLAGS += -Werror
CFLAGS += -Wextra
CFLAGS += -pedantic

test: test_mul.out
	@./test_mul.out
	
test_mul.out: test/test_mul_matrix.c  src/mul_matrix.c src/mul_matrix.h
	@echo Compiling $@
	@$(CC) $(CFLAGS) $^ test/vendor/unity.c -o $@

clean: 
	rm -f *.o *.out
