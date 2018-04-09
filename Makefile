CC = g++
CFLAGS = -std=c++14 -c
LDFLAGS =
OBJFILES = json.o menuNavigator.o main.o
TARGET = main

fast: src link
all : lib src link
lib:
	$(CC) $(CFLAGS) -x c++ json.hpp
src:
	$(CC) $(CFLAGS) main.cpp
	$(CC) $(CFLAGS) menuNavigator.cpp
link:
	$(CC) $(OBJFILES) -o $(TARGET)
