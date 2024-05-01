###
### Makefile for Gerp Project
### April 11, 2024
### Authors: Peter Morganelli and Brendan Roy


CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 -O2

gerp: gerp.o FSTree.o DirNode.o main.o processing.o hashtable.o
	${CXX} ${CXXFLAGS} $^ -o $@

main.o: main.cpp hashtable.o
	$(CXX) $(CXXFLAGS) -c main.cpp

processing.o: processing.cpp processing.h DirNode.o
	$(CXX) $(CXXFLAGS) -c processing.cpp

hashtable.o: hashtable.cpp hashtable.h
	$(CXX) $(CXXFLAGS) -c hashtable.cpp

gerp.o: gerp.cpp gerp.h hashtable.o
	$(CXX) $(CXXFLAGS) -c gerp.cpp

unit_test: unit_test_driver.o processing.o DirNode.o FSTree.o gerp.o hashtable.o
	$(CXX) $(CXXFLAGS) $^

diff:
	make gerp
	./gerp test-dirs/smallGutenberg my_out.txt < variedIn.txt > myOut.txt
	./the_gerp test-dirs/smallGutenberg ref_out.txt < variedIn.txt > refOut.txt
	sort my_out.txt > my_sorted.txt
	sort ref_out.txt > ref_sorted.txt
	diff my_sorted.txt ref_sorted.txt
	diff myOut.txt refOut.txt
	
##
## Here is a special rule that removes all .o files besides the provided ones 
## (DirNode.o and FSTree.o), all temporary files (ending with ~), and 
## a.out produced by running unit_test. First, we find all .o files 
## that are not provided files, then we run rm -f on each found file 
## using the -exec find flag. Second, we delete the temporary files
## and a.out. @ is used to suppress stdout.
## 
## You do not need to modify or further comment this rule!
##
clean:
	@find . -type f \( \
		-name '*.o' ! -name 'FSTree.o' ! -name 'DirNode.o' \
		\) -exec rm -f {} \;
	@rm -f *~ a.out

