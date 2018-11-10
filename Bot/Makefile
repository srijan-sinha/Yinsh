IDIR = ./include
CC = g++
CFLAGS = -I$(IDIR) -std=c++11

ODIR = ./build
EDIR = ./bin
SDIR = ./src

_DEPS = Board.h YinshBot.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = Board.o YinshBot.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) -g

$(EDIR)/bot: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -g

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(EDIR)/*