vishal: main.o pwd.o cd.o echo.o parse.o
	gcc main.o pwd.o cd.o echo.o parse.o -o vishal
main.o: main.c global.h
	gcc main.c -c -o main.o
pwd.o: pwd.c pwd.h
	gcc pwd.c -c -o pwd.o

cd.o: cd.c cd.h
	gcc cd.c -c -o cd.o
echo.o: echo.c echo.h
	gcc echo.c -c -o echo.o
parse.o: parse.c parse.h
	gcc parse.c -c -o parse.o
