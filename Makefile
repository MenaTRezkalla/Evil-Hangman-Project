CC = gcc 
CFLAGS = -g -Wall --std=c99 
OBJECTS = main.o my_string.o generic_vector.o associative_array.o
TEST_OBJECTS = unit_test.o test_defs.o

string_driver: $(OBJECTS) 
	$(CC) $(CFLAGS) -o string_driver $(OBJECTS) 
main.o: main.c 
	$(CC) $(CFLAGS) -c main.c -o main.o

my_string.o: my_string.c my_string.h status.h
	 $(CC) $(CFLAGS) -c my_string.c -o my_string.o

generic_vector.o: generic_vector.c generic_vector.h status.h
	$(CC) $(CFLAGS) -c generic_vector.c -o generic_vector.o

associative_array.o: associative_array.c associative_array.h status.h
	$(CC) $(CFLAGS) -c associative_array.c -o associative_array.o

unit_test: my_string.o unit_test.o test_defs.o 
	$(CC) $(CFLAGS) -o unit_test unit_test.o test_defs.o my_string.o

unit_test.o: unit_test.c unit_test.h
	$(CC) $(CFLAGS) -c unit_test.c -o unit_test.o

test_defs.o: test_defs.c
	$(CC) $(CFLAGS) -c test_defs.c -o test_defs.o

clean: 
	rm string_driver $(OBJECTS)
	rm unit_test $(TEST_OBJECTS)
