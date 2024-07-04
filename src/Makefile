
# Define compiler and flags (adjust as needed)
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Source files
SOURCE_FILES = login.cpp db/database.cpp

# Include directories (assuming libraries are installed in standard locations)
RAYLIB_DIR = /usr/local/lib/raylib
SQLITE3_DIR = /usr/local/lib/sqlite3
INCLUDE_DIRS = -I$(RAYLIB_DIR)/include -I$(SQLITE3_DIR)/include

# Library names
RAYLIB_LIB = raylib
SQLITE3_LIB = sqlite3

# Object files
OBJECT_FILES = $(SOURCE_FILES:.cpp=.o)

# Executable name
TARGET = TypeOnMe
# Rules

# Compile source files to object files
%.o : %.cpp
			$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $< -o $@
# Link object files into executable
$(TARGET): $(OBJECT_FILES)
				$(CXX) $(CXXFLAGS) $(OBJECT_FILES) -L$(RAYLIB_DIR)/lib -L$(SQLITE3_DIR)/lib -l$(RAYLIB_LIB) -l$(SQLITE3_LIB) -o build/$(TARGET)

# Clean rule to remove object files and executable
clean:
	rm -f $(OBJECT_FILES) $(TARGET)
