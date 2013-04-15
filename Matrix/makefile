all:	matrix

matrix: Matrix.o Morpheus.o BFSNeo.o
	g++ Matrix.o Morpheus.o BFSNeo.o -o matrix

morphTest: Matrix.o Morpheus.o
	g++ Matrix.o Morpheus.o -o morphTest

Matrix.o: Matrix.cpp
	g++ Matrix.cpp -c

Morpheus.o: Morpheus.cpp
	g++ Morpheus.cpp -c

BFSNeo.o: BFSNeo.cpp
	g++ BFSNeo.cpp -c

clean:
	rm *.o matrix morphTest
