NAME = minishell
BUILD_DIR = debug
IMAGE_NAME = linux
CONTAINER_NAME = linux_container

EXECUTABLE = $(BUILD_DIR)/src/$(NAME)
TEST_EXECUTABLE = $(BUILD_DIR)/test/test

build: $(BUILD_DIR)
	cmake --build $(BUILD_DIR)

$(BUILD_DIR):
	cmake -B $(BUILD_DIR) -S .

run: build
	$(EXECUTABLE)

test: build
	$(TEST_EXECUTABLE)

docker:
	docker build -t $(IMAGE_NAME) .
	docker run --name $(CONTAINER_NAME) -v $(shell pwd):/app -d $(IMAGE_NAME)
	docker exec -it $(CONTAINER_NAME) bash

clean:
	$(RM) -r $(BUILD_DIR)

re: clean
	$(MAKE) build

.PHONY: build run clean re
