MAIN_EXEC = task
TEST_EXEC = test

SRC_FILES = src/tk_string.c src/logger.c src/common.c src/list.c src/dict.c src/command.c
TEST_SRC_FILES = tests/tester.c tests/suite.c tests/tk_string_test.c tests/list_test.c \
				tests/dict_test.c tests/command_test.c
CC = clang -Werror

.PHONY : task compile clean test compile_tests sketch clean_tests test_debug scan

task : build
	./$(MAIN_EXEC)

build : compile
	$(CC) -o $(MAIN_EXEC) tmp/*.o

scan : 
	scan-build $(CC) $(SRC_FILES)

scan_tests :
	scan-build $(CC) $(TEST_SRC_FILES) $(SRC_FILES)

sketch :
	$(CC) -o sketch sketch.c
	@./sketch
	-rm sketch

compile :
	$(CC) -c $(SRC_FILES)
	-mkdir -p tmp
	-mv *.o tmp

clean :
	rm -rf tmp
	rm $(MAIN_EXEC)

test_debug : 
	$(CC) -o $(TEST_EXEC) -g $(TEST_SRC_FILES) $(SRC_FILES)
	-gdb $(TEST_EXEC) core
	$(MAKE) clean_debug_tests


test : build_test
	@echo "\nTESTING\n"
	-./$(TEST_EXEC)
	@echo "\nDONE TESTING\n"
	$(MAKE) clean_tests

build_test : compile_tests
	$(CC) -o $(TEST_EXEC) tmp/test/*.o

compile_tests : compile
	$(CC) -c $(TEST_SRC_FILES)
	-mkdir -p tmp/test
	-mv *.o tmp/test
	-cp tmp/*.o tmp/test

clean_tests :
	rm -rf tmp
	rm $(TEST_EXEC)
	rm -rf test.dSYM/

clean_debug_tests :
	rm $(TEST_EXEC)
