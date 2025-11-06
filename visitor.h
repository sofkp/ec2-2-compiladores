#ifndef VISITOR_H
#define VISITOR_H
#include "ast.h"
#include <list>
#include <unordered_map>

class BinaryExp;
class NumberExp;
class IdExp;
class AssignStm;
class PrintStm;
class IfStm;
class WhileStm;
class Program;

class Visitor {
public:
    virtual int visit(BinaryExp* exp) = 0;
    virtual int visit(NumberExp* exp) = 0;
    virtual int visit(IdExp* exp) = 0;
    virtual void visit(AssignStm* stm) = 0;
    virtual void visit(IfStm* stm) = 0;
    virtual void visit(WhileStm* stm) = 0;
    virtual void visit(PrintStm* stm) = 0;
};

class PrintVisitor : public Visitor {
public:
    void imprimir(Program* program);
    int visit(BinaryExp* exp) override;
    int visit(NumberExp* exp) override;
    int visit(IdExp* exp) override;
    void visit(AssignStm* stm) override;
    void visit(IfStm* stm) override;
    void visit(WhileStm* stm) override;
    void visit(PrintStm* stm) override;
};


class GencodeVisitor : public Visitor {
public:
    int contador =1 ;
    int contador2 =0 ; //para stmts dentro de otros stmts
    unordered_map<string , int> env;
    void code(Program* program);
    int visit(BinaryExp* exp) override;
    int visit(NumberExp* exp) override;
    int visit(IdExp* exp) override;
    void visit(IfStm* stm) override;
    void visit(WhileStm* stm) override;
    void visit(AssignStm* stm) override;
    void visit(PrintStm* stm) override;
};


class EVALVisitor : public Visitor {
public:
    void interprete(Program* program);
    int visit(BinaryExp* exp) override;
    int visit(NumberExp* exp) override;
    int visit(IdExp* exp) override;
    void visit(IfStm* stm) override;
    void visit(WhileStm* stm) override;
    void visit(AssignStm* stm) override;
    void visit(PrintStm* stm) override;
};

#endif // VISITOR_H