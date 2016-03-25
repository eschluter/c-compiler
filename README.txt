SCHLUTER C COMPILER (SCC)

	Included is a makefile which builds the compiler then calls each of the test cases located in directory "testfiles". I also included a shell script called "scc" (schluter c compiler) which invokes the preprocessor (cpp), passes the output to my cstr compiler, links lib/lib.c, then executes the output program. This is what I use in the makefile to run each of the test cases.

Supported types:
	32-bit signed integer:
		All operations supported. Declare with keyword "int"
	string:
		Equivalent to a c-style string. Declare with keyword "string". Literals are in double quotes.
		
No user defined types allowed (no structs, enums, or typedefs)
	
Strings:

	There are two supported operations with strings: addition and comparison. Addition (+) concatenates two strings. The addition of a string and an integer first converts the integer to a string then concatenates. Only "equal" (==) and "not equal' (!=) comparisons are allowed.
	
Ascii character literals (TODO):
	At this point the compiler cannot handle ascii character literals.

Loop peculiarity:

	An early design decision forces the use of brackets for all nested for and if loops. Brackets are 	required for all while and do-while loops.
	
Matrices and arrays:

	Both arrays and matrices are create on the stack by offsetting the required amount according to row major order. Therefore only local function block declarations are allowed, no global. both arrays and matrices can be indexed by a constant, a global or local integer reference, or an arithmetic expression producing an integer result. All indices are type checked.

Output:

	Assembly code is written to "out.s" located at the top level directory. The compiler binary result is named "test" and it is located in the bin folder. Assembly code is 32-bit GNU assembler (att) syntax.
	
Erik Schluter
March 24, 2016
