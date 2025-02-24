CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic
DLFLAGS = -fPIC -shared

DLIBRARY_DIR = lib
APP_DIR = app
BUILD_DIR = build
BUFFER_DIR = buffer
INPUT_HANDLER_DIR = inputThreadHandler
LOGGER_HANDLER_DIR = loggerThreadHandler
RUN_FILE = run.cpp

APP_SRC_FILES = ../$(APP_DIR)/$(RUN_FILE) ../$(APP_DIR)/$(BUFFER_DIR)/*.cpp ../$(APP_DIR)/$(INPUT_HANDLER_DIR)/*.cpp \
				../$(APP_DIR)/$(LOGGER_HANDLER_DIR)/*.cpp

run:
	cd $(BUILD_DIR); LD_LIBRARY_PATH=../lib ./run $(journal) $(default_log_level)

logger:
	$(CXX) $(CXXFLAGS) $(DLFLAGS) ./$(DLIBRARY_DIR)/common/*.cpp -o ./$(DLIBRARY_DIR)/loggerlib.so

build:
	mkdir -p $(BUILD_DIR); cd $(BUILD_DIR); \
	$(CXX) $(CXXFLAGS) $(APP_SRC_FILES) -o ./run -ldl

clean:
	rm -rf $(BUILD_DIR)

.PHONY: run logger build clean