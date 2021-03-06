flags=-Wno-deprecated -g -ggdb
comp=g++
prog=tsp

SEEDS = 1234 4321 8000 0

debug=0

exe:$(prog)
	#valgrind --leak-check=full --show-reachable=yes 
	./$(prog) $(SEEDS)

$(prog): tsp.cpp
	$(comp) $(prog).cpp -o $(prog)



clean:
	rm -f *~
	rm -f *.o
	rm -f $(prog)
	rm -f core*

