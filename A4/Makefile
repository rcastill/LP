all: impl1 impl2 main rm-residuals

impl1:
	gcc -c -Wall -Werror -fpic impl1.c
	gcc -shared -o libimpl1.so impl1.o

impl2:
	gcc -c -Wall -Werror -fpic impl2.c
	gcc -shared -o libimpl2.so impl2.o

main:
	gcc -o main main.c

rm-residuals:
	rm -f *.o

clean: rm-residuals
	rm -f *.so main

