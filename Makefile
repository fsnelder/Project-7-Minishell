NAME = minishell
BUILD_DIR := debug

EXECUTABLE = $(BUILD_DIR)/src/$(NAME)

build: $(BUILD_DIR)
	cmake --build $(BUILD_DIR)

$(BUILD_DIR):
	cmake -B $(BUILD_DIR) -S .

run: build
	$(EXECUTABLE)

.PHONY: build run
