# use make file="test.cpp"
default: clean pre 
pre: $(file)
	g++ $(file) -o example -lpthread
	./example

clean:
	rm -f example
	rm -f *.bin
