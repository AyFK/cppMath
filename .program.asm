FILENAME = .program.exe
LINKER = c++ -std=c++17 -o
FILES = linAlgebra.cpp statistics.cpp

all:
	$(LINKER) $(FILENAME) $(FILES)

clean:
	rm *.o
