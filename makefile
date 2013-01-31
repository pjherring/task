MAIN_EXEC = task
TEST_EXEC = test

SRC_FILES = src/helper.c src/task_io.c src/command.c 
TEST_SRC_FILES = tests/all_tests.c tests/helper_tests.c tests/CuTest.c tests/task_io_test.c \
	tests/command_tests.c

.PHONY : task compile clean test compile_tests sketch

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

test : compile_tests 
	gcc -o $(TEST_EXEC) tmp/test/*.o
	-./$(TEST_EXEC)
	$(MAKE) clean

compile_tests : compile
	gcc -c $(TEST_SRC_FILES)
	-mkdir -p tmp/test
	-mv *.o tmp/test
	-cp tmp/*.o tmp/test

clean :
	-rm -rf tmp
	-rm $(MAIN_EXEC)
	-rm $(TEST_EXEC)





