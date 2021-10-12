build: src/*.c
	gcc src/*.c -lncurses -o 3a
install: build
	install ./3a /usr/bin
