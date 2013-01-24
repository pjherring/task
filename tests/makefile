TEST_EXEC = test
SRC_FILES = $(wildcard *.c)
OBJ_FILES = $(TEST_SRC_FILES:.c=.o)

.PHONY : clean compile_all exec

exec : 
	./test

compile_all :
	gcc -c $(TEST_SRC_FILES)

clean : 
	-rm $(TEST_OBJ_FILES)
	-rm $(TEST_EXEC)


