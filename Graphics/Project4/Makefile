CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lGL -lglut -lGLU -lSDL -lSDLmain
SOURCES=f.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=f

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS) $(EXECUTABLE)
