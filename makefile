all: Pach.cpp
	g++ -o main_test.exe -std=c++17 Graph_Colorize.cpp 
clean:
	rm *.o