all: proj tests

proj: proj.s proj.cpp
	gcc proj.cpp proj.s -g -m32 -lstdc++ -o proj

tests: proj.s tests.cpp
	gcc tests.cpp proj.s -g -m32 -lstdc++ -o tests

clean: 
	rm proj
	rm tests
