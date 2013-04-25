all:	matrix

matrix: Matrix.o Morpheus.o BFSNeo.o SearchNode.o
	clang++ Matrix.o Morpheus.o BFSNeo.o SearchNode.o -o matrix

Matrix.o: code/Matrix.cpp
	clang++ code/Matrix.cpp -c

Morpheus.o: code/Morpheus.cpp
	clang++ code/Morpheus.cpp -c

BFSNeo.o: code/BFSNeo.cpp
	clang++ code/BFSNeo.cpp -c

SearchNode.o: code/SearchNode.cpp
	clang++ code/SearchNode.cpp -c

clean:
	rm -f *.o matrix 
