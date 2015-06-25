

all :
	g++ -std=c++0x -Wall -pthread -g ./thread.cpp -o a.out &> ./build_out.txt

clean:
	rm -rf *.out *.o

test_mem :
	valgrind --leak-check=yes --track-origins=yes --leak-check=full --show-reachable=yes --log-file=./memleak.txt ./a.out &> ./std.txt

test :
	 ./a.out &> ./std.txt

