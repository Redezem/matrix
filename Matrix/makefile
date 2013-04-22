all:	matrix

matrix: Matrix.o Morpheus.o BFSNeo.o
	clang++ Matrix.o Morpheus.o BFSNeo.o -o matrix

morphTest: Matrix.o Morpheus.o
	clang++ Matrix.o Morpheus.o -o morphTest

Matrix.o: Matrix.cpp
	clang++ Matrix.cpp -c

Morpheus.o: Morpheus.cpp
	clang++ Morpheus.cpp -c

BFSNeo.o: BFSNeo.cpp
	clang++ BFSNeo.cpp -c

clean:
	rm -f *.o matrix morphTest
