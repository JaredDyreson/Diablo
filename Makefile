# This Makefile attempts to create a components that all can be linked together to create a compiler
#

COMPILER = clang++
CFLAGS = -Wc++17-extensions -Wall
OUTPUT = diablo
INCS = -Ilexical_analysis/includes
LIBS = -L lexical_analysis/bin/static/lexiLib


all: diablo.cpp prereqs lexical syntax collate

run: all
	./$(OUTPUT)
collate:
	$(COMPILER) $(CFLAGS) diablo.cpp $(INCS) $(shell ls -d build/*) $(LIBS) -o $(OUTPUT)
clean:
	rm -rf build/* $(OUTPUT)
	cd lexical_analysis/ && $(MAKE) clean
	cd syntax_analysis/ && $(MAKE) clean
prereqs:
	mkdir build 2>/dev/null || echo "Already present"

# LEXI

lexical:
	cd lexical_analysis/ && $(MAKE) create_static
	cp lexical_analysis/*.o build
syntax:
	cd syntax_analysis/ && $(MAKE) create_static
	cp syntax_analysis/*.o build
