FILES = "./ledtoggle.c"

all:
	gcc -o ledtoggle ${FILES} 
install:
	gcc -o ledtoggle ${FILES} 
	cp ./ledtoggle /usr/local/bin
