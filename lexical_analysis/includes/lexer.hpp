#pragma once

#include "reader.hpp"
#include "lexer_rules.hpp"
#include "lexeme.hpp"

#include <map>
#include <regex>
#include <string>
#include <tuple>
#include <vector>

class lexer {
  public:
    lexer(lexerRules, sourceFile);
   
    std::tuple<int, int> span(std::string, std::regex, int*);
    void processFile();
    void processLine(int, std::vector<std::string>::iterator*, std::string, std::vector<std::tuple<int,int,int>>);

    std::vector<std::string>::iterator get_begin();
    std::vector<std::string>::iterator get_end();
    std::vector<lexeme> get_tokens();

    void remove_substring(std::string*, std::string);
    std::vector<lexeme> sortLexemes();
    void removeDuplicates(); // needs to be depreciated before final iteration
    lexeme get_next_token();

  private:
    lexerRules rules;
    sourceFile ingestedFile;
    std::vector<std::string>::iterator begin;
    std::vector<std::string>::iterator end;
    std::vector<lexeme> tokens;
    size_t location = 0;
};
