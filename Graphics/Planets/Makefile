CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lGL -lglut -lGLU -lSDL -lSDLmain
BIN=./bin
SRC=./src
OBJ=./obj
RES=./results
TXT=./txt
vpath %.cpp src
vpath %.h include

PROGRAM=$(BIN)/planets
OBJS=$(OBJ)/planets.o
SRCS=$(SRC)/planets.cpp
PAINT=paint.py

all:$(PROGRAM)

git:
	make clean
	git add -A
	git commit -m "Planets program modifications"
	git push



$(PROGRAM): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJ)/%.o : $(SRC)/%.cpp
	$(CC) $(CFLAGS) -o $@ $<

%.txt:all
	$(PROGRAM) $(TXT)/$@ > $(RES)/results$@
	python paint.py $(RES)/results$@
	python paint2.py $(RES)/results$@


clean:
	rm $(BIN)/* $(OBJ)/* $(RES)/*
