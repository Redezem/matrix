all:	greedy-search branch-search simanneal-hill clean-os

greedy-search: greedySearch.o SearchNode.o Morpheus.o Trinity.o
	g++ greedySearch.o SearchNode.o Morpheus.o Trinity.o -o greedy-search

greedySearch.o: code/greedySearch.cpp 
	g++ -c code/greedySearch.cpp

SearchNode.o: code/SearchNode.cpp code/SearchNode.h
	g++ -c code/SearchNode.cpp

Morpheus.o: code/Morpheus.cpp code/Morpheus.h
	g++ -c code/Morpheus.cpp

Trinity.o: code/Trinity.cpp code/Trinity.h
	g++ -c code/Trinity.cpp

branch-search: branchAndBoundSearch.o SearchNode.o Morpheus.o Cypher.o
	g++ branchAndBoundSearch.o SearchNode.o Morpheus.o Cypher.o -o branch-search

Cypher.o: code/Cypher.cpp code/Cypher.h
	g++ -c code/Cypher.cpp

branchAndBoundSearch.o: code/branchAndBoundSearch.cpp 
	g++ -c code/branchAndBoundSearch.cpp

simanneal-hill: Architect.o Neo.o simAnneal.o
	g++ Architect.o Neo.o simAnneal.o -o simanneal-hill

Architect.o: code/Architect.cpp code/Architect.h
	g++ code/Architect.cpp -c

Neo.o: code/Neo.cpp code/Neo.h
	g++ code/Neo.cpp -c

simAnneal.o: code/simAnneal.cpp
	g++ code/simAnneal.cpp -c -w

clean-os:
	rm *.o -f

clean:
	rm greedy-search branch-search simanneal-hill temp.heu Paths.txtSimAnnealOutput.txt -f
