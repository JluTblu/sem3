CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iheaders

OBJS = main.o other.o gray.o multiset.o

all: app

app: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o app

main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) -c src/main.cpp

other.o: src/other.cpp
	$(CXX) $(CXXFLAGS) -c src/other.cpp

gray.o: src/gray.cpp
	$(CXX) $(CXXFLAGS) -c src/gray.cpp

multiset.o: src/multiset.cpp
	$(CXX) $(CXXFLAGS) -c src/multiset.cpp

clean:
	rm -f *.o app
