

all :
	g++ -std=c++0x -lc -Wall -lpthread -g ./main.cpp -o a.out &> ./build_log.txt

clean:
	rm -rf *.out *.o

test_mem :
	valgrind --leak-check=yes --track-origins=yes --leak-check=full --show-reachable=yes --log-file=./memleak.txt ./a.out

test :
	 ./a.out
