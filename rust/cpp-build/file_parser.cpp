
    #include <strstream>
#include <string>
#include "antlr4-runtime.h"
#include "RustLexer.h"
#include "RustParser.h"

class MyErrorListener: public antlr4::BaseErrorListener {
  virtual void syntaxError(
      antlr4::Recognizer *recognizer,
      antlr4::Token *offendingSymbol,
      size_t line,
      size_t charPositionInLine,
      const std::string &msg,
      std::exception_ptr e) override {
    std::ostrstream s;
    s << "Line(" << line << ":" << charPositionInLine << ") Error(" << msg << ")";
    throw std::invalid_argument(s.str());
  }
};

int main(int argc, char *argv[]) {
  
      std::ifstream input_file(argv[1]);
  antlr4::ANTLRInputStream input(input_file);
    
  RustLexer lexer(&input);
  MyErrorListener errorListener;
  lexer.removeErrorListeners();
  lexer.addErrorListener(&errorListener);
  antlr4::CommonTokenStream tokens(&lexer);

  RustParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(&errorListener);
  try {
    antlr4::tree::ParseTree* tree = parser.crate();
    return 0;
  } catch (std::invalid_argument &e) {
    std::cerr << e.what() << std::endl;
    return 10;
  }
}
    