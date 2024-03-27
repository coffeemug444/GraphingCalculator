CC=g++
CFLAGS = -g -std=c++23 -Wall -Wextra

main: main.cpp	ASTBinaryNode.cpp ASTUnaryNode.cpp ASTNumberNode.cpp Token.cpp
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f main