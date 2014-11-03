

# Makefile example -- scanner and parser.
#
CXX     = g++ -D_DEBUG
LEX     = flex
YACC    = bison -y -t 
YFLAGS  = -d
objects = parse.o scan.o

moc: $(objects)
	$(CXX) -o $@ $(objects) -lfl

parse.o: parse.y

#       parse.h: parse.c
#	mv -f y.tab.h parse.h

scan.o: scan.l 


clean:
	rm -f *.o parse.tab.c parse.tab.h

