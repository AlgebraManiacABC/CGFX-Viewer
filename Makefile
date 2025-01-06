# Compiler and flags
CC = gcc
CFLAGS = -Wall -Werror
#CFLAGS = -Wall -g `sdl2-config --cflags`
#LDFLAGS = `sdl2-config --libs` -lGL -lm

TARGET = viewer
SRC_DIR = src
LIB_DIR = lib
BUILD_DIR = build

RM = rm -rf
ifeq ($(OS), Windows_NT)
#SDL2_CFLAGS = -IC:/path/to/SDL2/include
#SDL2_LDFLAGS = -LC:/path/to/SDL2/lib -lSDL2
	TARGET := $(TARGET).exe
	LDIRFLAGS += -L"C:\Program Files (x86)\SDL2\lib"
	LDIRFLAGS += -L"C:\Program Files (x86)\glew\lib"

	IDIRFLAGS += -I"C:\Program Files (x86)\glew\include"
	IDIRFLAGS += -I"C:\Program Files (x86)\SDL2\include"
	IDIRFLAGS += -I"C:\Program Files (x86)\cglm\include"
	LFLAGS += -lmingw32 -lglew32 -lopengl32
# Uncomment the following line to hide the terminal on Windows
    #LFLAGS += -mwindows
	BUILD_DIR := $(BUILD_DIR)_NT
else
	LFLAGS += -lGLEW -lGL
endif

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
LIBS = $(wildcard $(LIB_DIR)/*.h)
IDIRFLAGS += -I$(LIB_DIR)
LFLAGS += -lSDL2main -lSDL2 -lm

# Build the target executable
$(TARGET): $(OBJS) $(LIBS)
	$(CC) $(OBJS) -o $(TARGET) $(LDIRFLAGS) $(LFLAGS)

# Compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(IDIRFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

# Clean up generated files
.PHONY: clean
clean:
	$(RM) $(BUILD_DIR) $(TARGET)