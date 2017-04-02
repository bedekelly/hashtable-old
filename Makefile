COMPILER = gcc
SOURCE_DIR = src
BUILD_DIR = build
TEST_BINARY = test
DEBUG_BINARY = debug
INCLUDES = include

test:
	mkdir -p $(BUILD_DIR) && \
	$(COMPILER) $(SOURCE_DIR)/*.c -I$(INCLUDES) \
	-o $(BUILD_DIR)/$(TEST_BINARY)
debug:
	mkdir -p $(BUILD_DIR) && \
	$(COMPILER) $(SOURCE_DIR)/*.c -DDEBUG -I$(INCLUDES) \
	-o $(BUILD_DIR)/$(DEBUG_BINARY)
clean:
	rm -f *~ $(SOURCE_DIR)/*~ $(BUILD_DIR)/*
