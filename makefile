main_exec = task
test_exec = test

src = src/tk_string.c src/logger.c src/common.c src/list.c src/dict.c \
	src/task.c src/execute.c src/user_io.c
test_src = tests/tester.c tests/suite.c tests/tk_string_test.c \
	tests/list_test.c tests/dict_test.c tests/task_test.c

objects = src/tk_string.o src/logger.o src/common.o src/list.o src/dict.o \
	src/task.o src/execute.o src/user_io.o
main = src/main.o
test_objects = tests/tester.o tests/suite.o tests/tk_string_test.o \
	tests/list_test.o tests/dict_test.o tests/task_test.o

linked_libs = -ljansson
CC = gcc

task: $(objects)
	$(CC) -o $(main_exec) -g $(main) $(objects) $(linked_libs)

test: $(test_objects) $(objects)
	$(CC) -o $(test_exec) -g $(test_objects) $(objects) $(linked_libs)

memcheck_tests: 
	$(CC) -g -o $(test_exec) $(src) $(test_src) $(linked_libs) 
	valgrind --dsymutil=yes --tool=Memcheck ./$(test_exec)

.PHONY : clean clean_tests run_tests

clean: 
	-rm $(objects)
	-rm $(main_exec)

clean_tests: 
	-rm $(test_objects)
	-rm $(test_exec)

run_tests: test
	-./$(test_exec)
	-$(MAKE) clean_tests
