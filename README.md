The goal of this project is to create a parser application that can
parse a variety of Context Free Grammars (CFGs)

I plan to start with a Top-Down Parser (Recursive Descent) with a stack (though I will have to check for Left-Recursion).

Also possible I may implement a Bottom-Up Parser to avoid having to check for left-recursion in the case of the Top-Down Parser.

Use attached makefile for compiling.

After running the makefile (the output executable should be grm), running 

> ./grm

should print a help message.

The format for command line arguments is:

> ./gram (Optional -t) filename (Optional:   (Optional -s) stringToParse (Optional -s) stringToParse (Optional -s) stringToParse ... )

The -t switch will display the grammar represented by the file (i.e. rules in the grammar)

The -s switch, if before a string, will display the stack trace for that string during parsing. The stack trace includes the current input, and backtracking changes (if needed)
