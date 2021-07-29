#/**
# * Final Homework: Working Library
# * File: makefile
# */
# This is the makefile for compiling using make...

.SUFFIXES : .cc
.SUFFIXES : .c
.SUFFIXES : .cpp

INCDIR =
LIBDIR =

CC = g++
CXXFLAGS = -g -std=c++14
LIBS = -lm
OBJS = main.o             #List of object required for your program

TARGET = library       #filename output like program.exe

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBDIR) $(LIBS)

.cc.o:
	$(CC) -c $(CXXFLAGS) $(INCDIR) $<
.c.o:
	$(CC) -c $(CXXFLAGS) $(INCDIR) $<
.cpp.o:
	$(CC) -c $(CXXFLAGS) $(INCDIR) $<

clean:
	rm -f $(OBJS) $(TARGET) core



