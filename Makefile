CC=g++
CFLAGS = -std=c++11 -Wall -Werror -g
OBJS = main.o Matrix.o SVD.o

all: svd

svd: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o svd 

main.o: main.cpp Matrix.h
	$(CC) $(CFLAGS) -c main.cpp

SVD.o: SVD.cpp SVD.h Matrix.h
	$(CC) $(CFLAGS) -c SVD.cpp

Matrix.o: Matrix.cpp Matrix.h 
	$(CC) $(CFLAGS) -c Matrix.cpp

clean:
	rm $(OBJS) svd 