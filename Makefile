CC=g++
STD=-std=c++23
CFLAGS=-g -Wall -Wextra

SRCDIR=src
ODIR=obj

CLASSES = ASTBinaryNode ASTNumberNode ASTUnaryNode Token
DEPS = $(patsubst %,$(SRCDIR)/%.hpp,$(CLASSES) ASTNode) 
OBJ = $(patsubst %,$(ODIR)/%.o,$(CLASSES) main)

$(ODIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	$(CC) -c -g -o $@ $< $(STD) $(CFLAGS)

main: $(OBJ)
	$(CC) -g -o $@ $^ $(STD) $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
	rm -rf main $(ODIR)/*.o