/*
 * The MIT License (MIT)
 * 
 * Copyright (c) 2014 Krzysztof Narkiewicz <krzysztof.narkiewicz@ezaquarii.com>
 * 
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 * 
 */

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <vector>
#include <map>
#include <string>

#include "scanner.h"
#include "Symbol.hpp"
#include "SymbolTable.hpp"

// autogenerated by Bison, don't panic
// if your IDE can't resolve it - call make first
#include "../src/parser.hpp"

namespace Synthetic {

// forward declare our simplistic AST node class so we
// can declare container for it without the header
class Command;

/**
 * This class is the interface for our scanner/lexer. The end user
 * is expected to use this. It drives scanner/lexer, keeps
 * parsed AST and generally is a good place to store additional
 * context data. Both parser and lexer have access to it via internal 
 * references.
 * 
 * I know that the AST is a bit too strong word for a simple
 * vector with nodes, but this is only an example. Get off me.
 */
class Interpreter
{
public:
    Interpreter();
    
    /**
     * Run parser. Results are stored inside.
     * \returns 0 on success, 1 on failure
     */
    int parse();
    
    /**
     * Clear AST
     */
    void clear();
    
    /**
     * Print AST
     */
    std::string str() const;
    
    /**
     * Switch scanner input stream. Default is standard input (std::cin).
     * It will also reset AST.
     */
    void switchInputStream(std::istream *is);
    
    /**
     * This is needed so that Scanner and Parser can call some
     * methods that we want to keep hidden from the end user.
     */
    friend class Parser;
    friend class Scanner;
    
private:
    // Used internally by Parser to insert AST nodes.
    void addCommand(const Command &cmd);
    
    // Used internally by Scanner YY_USER_ACTION to update location indicator
    void increaseLocation(unsigned int loc);
    
    // Used to get last Scanner location. Used in error messages.
    unsigned int location() const;

    void addSymbol(Symbol);
    Symbol getSymbol(std::string); // returns infinity if not found
    
private:
    Scanner m_scanner; // reads in from file stream
    Parser m_parser; // 
    std::vector<Command> m_commands;  // Example AST
    unsigned int m_location;          // Used by scanner
    SymbolTable symbol_table; // Used across the program to give variable values
};

}

#endif // INTERPRETER_H
