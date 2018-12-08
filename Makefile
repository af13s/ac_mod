
all:
	g++ compress.cpp -std=c++11 -Wall

test:
	g++ test.cpp -std=c++11 -Wall 

clean:
	rm a.out

