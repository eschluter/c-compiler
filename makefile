IDIR		= include
OUTDIR		= bin
SRCDIR 		= src
OBJDIR		= src/obj
TESTDIR		= testfiles

CC 		= gcc
CFLAGS 		= -I$(IDIR) -std=c99
SOURCES 	= y.tab.c compilerAPI.c symboltable.c hashtable.c linkedlist.c istack.c
OBJECTS 	= $(SOURCES:.c=.o)
TESTING		= $(shell ls $(TESTDIR))
EXEC	 	= bin/cstr-compiler

all: $(EXEC) run


%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $(OBJDIR)/$@

$(EXEC): y.tab.c lex.yy.c $(OBJECTS)
	$(CC) $(addprefix $(OBJDIR)/,$(OBJECTS)) -o $@


y.tab.c: src/cstr-parser.y
	yacc -d $^; mv $@ $(SRCDIR)

lex.yy.c: src/cstr-lexer.l
	flex $^; mv y.tab.h $(IDIR); mv lex.yy.c $(IDIR)

y.tab.o: $(SRCDIR)/y.tab.c
	$(CC) $(CFLAGS) -c $^ -o $(OBJDIR)/$@


.PHONY : run
run: $(EXEC)
	for file in $(TESTING); do \
		echo FILENAME: $$file; ./scc $(TESTDIR)/$$file; echo; echo; \
	done
