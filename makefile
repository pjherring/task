main_exec = task
test_exec = test

src = src/tk_string.c src/logger.c src/common.c src/list.c src/dict.c \
	src/task.c src/execute.c src/user_io.c
test_src = tests/tester.c tests/suite.c tests/tk_string_test.c \
	tests/list_test.c tests/dict_test.c tests/task_test.c tests/execute_tests.c

objects = src/tk_string.o src/logger.o src/common.o src/list.o src/dict.o \
	src/task.o src/execute.o src/user_io.o
main = src/main.o
test_objects = tests/tester.o tests/suite.o tests/tk_string_test.o \
	tests/list_test.o tests/dict_test.o tests/task_test.o tests/execute_tests.o

linked_libs = -ljansson
CC = gcc

task: $(objects) $(main)
	$(CC) -o $(main_exec) -g $(main) $(objects) $(linked_libs)

test: $(test_objects) $(objects)
	$(CC) -o $(test_exec) -g $(test_objects) $(objects) $(linked_libs)

debug: 
	$(CC) -o $(main_exec) -g $(src) $(main) $(linked_libs)

.PHONY : clean clean_tests run_tests memcheck_tests

memcheck_tests: 
	$(CC) -g -o $(test_exec) $(src) $(test_src) $(linked_libs) 
	valgrind --dsymutil=yes --tool=Memcheck ./$(test_exec)

memcheck:
	$(CC) -g -o $(main_exec) $(src) src/main.c $(linked_libs)
	valgrind --dsymutil=yes --tool=Memcheck ./$(main_exec)
	
clean: 
	-rm $(objects)
	-rm $(main_exec)
	-rm -rf $(main_exec).dSYM

clean_tests: 
	-rm $(test_objects)
	-rm $(test_exec)
	-rm -rf $(test_exec).dSYM


run_tests: test
	-./$(test_exec)
	-$(MAKE) clean_tests
