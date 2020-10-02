#pragma once
#include <iostream>
#include <regex>
#include <tuple>
#include <vector>

class lexeme {
  public:
    lexeme(std::tuple<size_t, size_t, size_t>, std::string, std::string);
    friend std::ostream& operator<<(std::ostream& out, const lexeme& lex);
    const std::string get_substring();
    std::string get_tag();

    friend bool operator== (const lexeme &l1, const lexeme &l2);
     
    friend bool operator!= (const lexeme &l1, const lexeme &l2);
    friend bool operator <(const lexeme& l1, const lexeme& l2);

  private:
    std::tuple<size_t, size_t, size_t> slice;
    std::string identifier;
    std::string substring;
};

