COMPILER = gcc
SOURCES = hashmap.c hmdebug.c tests.c
BINARY = tests


tests:
	$(COMPILER) $(SOURCES) -o $(BINARY)

clean:
	rm -f *~ $(BINARY)
