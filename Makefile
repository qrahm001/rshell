all: 
	mkdir -p ./bin
	g++ -Wall -Werror -ansi -pedantic ./src/rshell.cpp -o ./bin/rshell
src:
	g++ -Wall -Werror -ansi -pedantic ./src/rshell.cpp -o ./bin/rshell
