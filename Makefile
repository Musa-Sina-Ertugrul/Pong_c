CC := gcc
CFLAGS := -g -fPIC -Wall -Wextra
SRC_DIR := src
HEADER_DIR := include
LIBS := hashmap raylib pthread
FILE_NAMES := $(wildcard $(SRC_DIR)/*.c)
FILE_NAMES := $(foreach word, $(FILE_NAMES), $(patsubst $(SRC_DIR)/%.c,%,$(word)))
OBJ_DIR := build/lib
SRC_FILES := $(foreach word, $(FILE_NAMES), $(word).c)
LIB_SEARCH_DIRS := usr/lib user/local/lib
TEST_DIR := tests
TEST_FILES := $(wildcard $(TEST_DIR)/*.c)
TEST_FILES := $(foreach word, $(TEST_FILES), $(patsubst $(TEST_DIR)/%.c,%,$(word)))
BUILD_DIR := build
INCLUDE_LIBS := $(foreach word, $(LIBS),-l$(word))

all: build_dir $(FILE_NAMES) main

build_dir: 
	mkdir -p $(OBJ_DIR)

.PHONY: $(FILE_NAMES)
$(FILE_NAMES): $(SRC_FILES)

.PHONY: $(SRC_FILES)
$(SRC_FILES): 
	$(CC) $(CFLAGS) -c $(SRC_DIR)/$@ -o $(OBJ_DIR)/$(patsubst %.c,%.o,$@) $(INCLUDE_LIBS) -I$(HEADER_DIR)/ 

.PHONY: main
main:
	$(CC) $(CFLAGS) -o $@ $(wildcard $(OBJ_DIR)/*.o) $@.c -I$(HEADER_DIR) $(INCLUDE_LIBS)

test: $(TEST_FILES)

.PHONY: $(TEST_FILES)
$(TEST_FILES):
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$@ $(TEST_DIR)/$@.c $(wildcard $(OBJ_DIR)/*.o) $(INCLUDE_LIBS) -I$(HEADER_DIR)/
	chmod +x $(BUILD_DIR)/$@
	./$(BUILD_DIR)/$@

clean:
	rm -rf build
	rm -rf main