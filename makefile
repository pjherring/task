MAIN_EXEC = task
TEST_EXEC = test

SRC_FILES = src/tk_string.c src/logger.c
TEST_SRC_FILES = tests/tester.c tests/suite.c tests/tk_string_test.c 

.PHONY : task compile clean test compile_tests sketch clean_tests test_debug

task : compile
	gcc -o $(MAIN_EXEC) tmp/*.o
	./$(MAIN_EXEC)

sketch :
	gcc -o sketch sketch.c
	-./sketch
	-rm sketch

compile :
	gcc -c $(SRC_FILES)
	-mkdir -p tmp
	-mv *.o tmp

clean :
	rm -rf tmp
	rm $(MAIN_EXEC)

test_debug : 
	gcc -o $(TEST_EXEC) -g $(TEST_SRC_FILES) $(SRC_FILES)
	-gdb $(TEST_EXEC)
	$(MAKE) clean_debug_tests

test : compile_tests
	gcc -o $(TEST_EXEC) tmp/test/*.o
	@echo "\nTESTING\n"
	-./$(TEST_EXEC)
	@echo "\nDONE TESTING\n"
	$(MAKE) clean_tests

compile_tests : compile
	gcc -c $(TEST_SRC_FILES)
	-mkdir -p tmp/test
	-mv *.o tmp/test
	-cp tmp/*.o tmp/test

clean_tests :
	rm -rf tmp
	rm $(TEST_EXEC)

clean_debug_tests :
	rm $(TEST_EXEC)
