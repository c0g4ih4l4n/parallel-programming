CC = cc

CFLAGS  = -std=c99
CFLAGS += -fopenmp
CFLAGS += -Wall
CFLAGS += -Werror
CFLAGS += -Wextra
CFLAGS += -pedantic

test_sum: test_sum.out
	@./test_sum.out
	
test_sum.out: test/test_sum_array_parallel.c  src/sum_array_parallel.c src/sum_array_parallel.h
	@echo Compiling $@
	@$(CC) $(CFLAGS) $^ test/vendor/unity.c -o $@

test_find_max: test_find_max.out
	@./test_find_max.out

test_find_max.out: test/test_find_max_array_parallel.c  src/find_max_array_parallel.c src/find_max_array_parallel.h
	@echo Compiling $@
	@$(CC) $(CFLAGS) $^ test/vendor/unity.c -o $@


clean: 
	rm -f *.o *.out
