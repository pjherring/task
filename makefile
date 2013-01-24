MAIN_EXEC = task
TEST_EXEC = test

SRC_FILES = src/helper.c
TEST_SRC_FILES = tests/all_tests.c tests/helper_tests.c tests/CuTest.c


.PHONY : task compile clean compile_tests

task : compile
	gcc -o $(MAIN_EXEC) tmp/*.o

compile :
	gcc -c $(SRC_FILES)
	-mkdir -p tmp
	-mv *.o tmp

test : compile_tests 
	gcc -o $(TEST_EXEC) tmp/test/*.o
	./$(TEST_EXEC)

compile_tests : compile
	gcc -c $(TEST_SRC_FILES)
	-mkdir -p tmp/test
	-mv *.o tmp/test
	-cp tmp/*.o tmp/test

clean :
	-rm -rf tmp





