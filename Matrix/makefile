all:	greedy-search branch-search clean-os

greedy-search: greedySearch.o SearchNode.o Smith2.o Trinity.o
	g++ greedySearch.o SearchNode.o Smith2.o Trinity.o -o greedy-search

greedySearch.o: code/greedySearch.cpp 
	g++ -c code/greedySearch.cpp

SearchNode.o: code/SearchNode.cpp code/SearchNode.h
	g++ -c code/SearchNode.cpp

Smith2.o: code/Smith2.cpp code/Smith2.h
	g++ -c code/Smith2.cpp

Trinity.o: code/Trinity.cpp code/Trinity.h
	g++ -c code/Trinity.cpp

branch-search: branchAndBoundSearch.o SearchNode.o Smith2.o Cypher.o
	g++ branchAndBoundSearch.o SearchNode.o Smith2.o Cypher.o -o branch-search

Cypher.o: code/Cypher.cpp code/Cypher.h
	g++ -c code/Cypher.cpp

branchAndBoundSearch.o: code/branchAndBoundSearch.cpp 
	g++ -c code/branchAndBoundSearch.cpp

clean-os:
	rm *.o -f

clean:
	rm greedy-search branch-search temp.heu Paths.txt -f
