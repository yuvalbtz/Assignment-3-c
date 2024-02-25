all: StrList

StrList: Main.c StrList.c
	gcc -o StrList Main.c StrList.c -Wall

clean: 
	rm -f StrList
