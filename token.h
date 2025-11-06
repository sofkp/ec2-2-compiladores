#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <ostream>

using namespace std;

class Token {
public:
    // Tipos de token
    enum Type {
        PLUS,    // +
        MINUS,   // -
        MUL,     // *
        DIV,     // /
        POW,     // **
        LPAREN,  // (
        RPAREN,  // )
        SQRT,    // sqrt
        NUM,     // Número
        ERR,     // Error
        ID,      // ID
        LE, // less equal
        LT, // less than
        SEMICOL,    
        ASSIGN,
        PRINT,
        IF,
        WHILE,
        DO,
        THEN,
        ENDIF,
        ENDWHILE,
        ELSE,
        ET, //equal to, ns si se llame asi pero esto ==
        END      // Fin de entrada
    };

    // Atributos
    Type type;
    string text;

    // Constructores
    Token(Type type);
    Token(Type type, char c);
    Token(Type type, const string& source, int first, int last);

    // Sobrecarga de operadores de salida
    friend ostream& operator<<(ostream& outs, const Token& tok);
    friend ostream& operator<<(ostream& outs, const Token* tok);
};

#endif // TOKEN_H