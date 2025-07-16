PARSER_NAME=parse_while
all: build_antlr build_cpp
build_antlr:
	java -jar $(ANTLR) -Dlanguage=Cpp g_while.g4
build_cpp:
	g++ -std=c++17 -o ./$(PARSER_NAME) ./*.cpp  -I $(ANTLR_RUNTIME) $(ANTLR_RUNTIME_LIB)
clean:
	rm -f *.h *.tokens *Parser.cpp *Listener.cpp *Lexer.cpp *.interp