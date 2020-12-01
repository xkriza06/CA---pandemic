CC=g++
FLAGS=-g -pedantic -std=c++11
FILE=ca

all:
	$(CC) $(FLAGS) $(FILE).cpp cell.cpp site.cpp -o $(FILE)
