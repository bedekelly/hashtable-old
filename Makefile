COMPILER = gcc
SOURCES = src/hashmap.c src/hmdebug.c src/tests.c
BINARY = build/tests
INCLUDES = include

tests:
	$(COMPILER) $(SOURCES) -I$(INCLUDES) -o $(BINARY)
debug:
	$(COMPILER) $(SOURCES) -DDEBUG -I$(INCLUDES) -o $(BINARY)
clean:
	rm -f *~ sources/*~ $(BINARY)
