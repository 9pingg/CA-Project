
all: clean compile

compile:
	g++ -c example.cpp -o example.o -pthread
	g++ example.o -o example -pthread
	./example

clean:
	rm -rf example