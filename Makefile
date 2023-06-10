CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -pedantic -g
INCLUDES = -I$(SFML_PATH)\include -Iimgui -Iinclude

SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

IMGUI_SOURCES=$(wildcard imgui/*.cpp)
IMGUI_OBJECTS=$(IMGUI_SOURCES:.cpp=.o)

ifeq ($(OS),Windows_NT)
	EXECUTABLE = doodle-jump.exe
	LIBS = $(SFML_PATH)\lib\libsfml-graphics.a $(SFML_PATH)\lib\libsfml-window.a $(SFML_PATH)\lib\libsfml-system.a $(SFML_PATH)\lib\libsfml-audio.a -lopengl32 -lpsapi
else
	EXECUTABLE = doodle-jump
	LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lGL
endif

.PHONY: all clean

all: $(SOURCES) $(IMGUI_SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(IMGUI_OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(IMGUI_OBJECTS) $(EXECUTABLE)
