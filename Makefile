CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall

studentai: main.cpp studentas.cpp funkcijos.h studentas.h
	$(CXX) $(CXXFLAGS) main.cpp studentas.cpp -o studentai

clean:
	rm -f studentai studentai.exe
