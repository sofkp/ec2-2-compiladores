#include <iostream>
#include "ast.h"
#include "visitor.h"
#include <unordered_map>
using namespace std;
unordered_map<std::string, int> memoria;
///////////////////////////////////////////////////////////////////////////////////
int BinaryExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int NumberExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int IdExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int AssignStm::accept(Visitor* visitor) {
    visitor->visit(this);
    return 0;
}

int PrintStm::accept(Visitor* visitor) {
    visitor->visit(this);
    return 0;
}

int IfStm::accept(Visitor* visitor) {
    visitor->visit(this);
    return 0;
}
int WhileStm::accept(Visitor* visitor) {
    visitor->visit(this);
    return 0;
}


///////////////////////////////////////////////////////////////////////////////////

int PrintVisitor::visit(BinaryExp* exp) {
    exp->left->accept(this);
    cout << ' ' << Exp::binopToChar(exp->op) << ' ';
    exp->right->accept(this);
    return 0;
}

int PrintVisitor::visit(NumberExp* exp) {
    cout << exp->value;
    return 0;
}

int PrintVisitor::visit(IdExp* exp) {
    cout << exp->value;
    return 0;
}

void PrintVisitor::visit(AssignStm* stm) {
    cout << stm->id << " = ";
    stm->e->accept(this);
    cout << ";";
}

void PrintVisitor::visit(PrintStm* stm) {
    cout << "print(";
    stm->e->accept(this);
    cout << ");";
}

void PrintVisitor::visit(IfStm* stm) {
}

void PrintVisitor::visit(WhileStm* stm) {
}
void PrintVisitor::imprimir(Program* program){
    for (Stm* s : program->slist) {
        s->accept(this);
        cout << endl;
    }
};

///////////////////////////////////////////////////////////////////////////////////
int EVALVisitor::visit(BinaryExp* exp) {
    int result;
    int v1 = exp->left->accept(this);
    int v2 = exp->right->accept(this);
    switch(exp->op) {
        case PLUS_OP: result = v1 + v2; break;
        case MINUS_OP: result = v1 - v2; break;
        case MUL_OP: result = v1 * v2; break;
        case DIV_OP:
            if(v2 != 0) result = v1 / v2;
            else {
                cout << "Error: división por cero" << endl;
                result = 0;
            }
            break;
        case LE_OP: result = v1 <= v2; break;
        case LT_OP: result = v1 < v2; break;
        case ET_OP: result = v1 == v2; break;
        default:
            cout << "Operador desconocido" << endl;
            result = 0;
    }
    return result;
}

int EVALVisitor::visit(NumberExp* exp) {
    return exp->value;
}

int EVALVisitor::visit(IdExp* exp) {
    return memoria[exp->value];
}

void EVALVisitor::visit(IfStm* stm) {
}

void EVALVisitor::visit(WhileStm* stm) {
}


void EVALVisitor::visit(AssignStm* stm) {
    memoria[stm->id] = stm->e->accept(this);
}

void EVALVisitor::visit(PrintStm* stm) {
    cout << stm->e->accept(this);
}
void EVALVisitor::interprete(Program* program){
    for (Stm* s : program->slist) {
        s->accept(this);
    }
};

//////////////////////////////////////////
int GencodeVisitor::visit(BinaryExp* exp) {
    switch(exp->op) {
        case PLUS_OP: {
            exp->left->accept(this);
            cout << "pushq %rax" << endl;
            exp->right->accept(this);
            cout << "movq %rax, %rcx" << endl;
            cout << "popq %rax" << endl;
            cout << "addq %rcx, %rax" << endl;
            break;
        }
        case LT_OP: {
            exp->left->accept(this);
            cout << "pushq %rax" << endl;
            exp->right->accept(this);
            cout << "movq %rax, %rcx" << endl;
            cout << "popq %rax" << endl;
            cout << "cmpq %rcx, %rax" << endl;
            cout << "movl $0, %eax" << endl;
            cout << "setl %al" << endl;
            cout << "movzbq %al, %rax" << endl;
            break;
        }
        case LE_OP: {
            exp->left->accept(this);
            cout << "pushq %rax" << endl;
            exp->right->accept(this);
            cout << "movq %rax, %rcx" << endl;
            cout << "popq %rax" << endl;
            cout << "cmpq %rcx, %rax" << endl;
            cout << "movl $0, %eax" << endl;
            cout << "setle %al" << endl;
            cout << "movzbq %al, %rax" << endl;
            break;
        }
        case ET_OP: {
            exp->left->accept(this);
            cout << "pushq %rax" << endl;
            exp->right->accept(this);
            cout << "movq %rax, %rcx" << endl;
            cout << "popq %rax" << endl;
            cout << "cmpq %rcx, %rax" << endl;
            cout << "movl $0, %eax" << endl;
            cout << "sete %al" << endl;
            cout << "movzbq %al, %rax" << endl;
            break;
        }
        case GT_OP: {
            exp->left->accept(this);
            cout << "pushq %rax" << endl;
            exp->right->accept(this);
            cout << "movq %rax, %rcx" << endl;
            cout << "popq %rax" << endl;
            cout << "cmpq %rcx, %rax" << endl;
            cout << "movl $0, %eax" << endl;
            cout << "setg %al" << endl;
            cout << "movzbq %al, %rax" << endl;
            break;
        }
    }
    return 0;
}

int GencodeVisitor::visit(NumberExp* exp) {
    cout << "movq $" << exp->value << ", %rax" << endl;
    return 0;
}

void GencodeVisitor::visit(PrintStm* stm) {
    stm->e->accept(this);
    cout << "movq %rax, %rsi" << endl;
    cout << "leaq print_fmt(%rip), %rdi" << endl;
    cout << "movl $0, %eax" << endl;
    cout << "call printf@PLT" << endl;
}

int GencodeVisitor::visit(IdExp* exp) {
    cout << "movq " << -8*env[exp->value] << "(%rbp), %rax" << endl;  
    return 0;
}

void GencodeVisitor::visit(AssignStm* stm) {
    if (env.count(stm->id)) {
        stm->e->accept(this);
        cout << "movq %rax," << -8*env[stm->id] << "(%rbp)"  << endl;
    }
    else {
        env[stm->id]=contador;
        stm->e->accept(this);
        cout << "movq %rax," << -8*contador << "(%rbp)"  << endl;
        contador++;
    }
}

void GencodeVisitor::visit(IfStm* stm) {
    int num = contador2++;
    string elsetag = "else_" + to_string(num); //para que cada else del if tenga un nombre diferente
    string endiftag = "endif_" + to_string(num);
    stm->condicion->accept(this);
    cout << "cmpq $0 ,%rax"  << endl;;
    cout << "je " << elsetag   << endl;
    for(auto i:stm->stlist1) {
        i->accept(this);
    }
    cout << "jmp " << endiftag  << endl;
    cout << elsetag << ":"   << endl;
    for(auto i:stm->stlist2) {
        i->accept(this);
    }
    cout << endiftag << ":"   << endl;
}


void GencodeVisitor::visit(WhileStm* stm) {
    int num = contador2++;
    string whiletag = "while_" + to_string(num);
    string endwhiletag = "endwhile_" + to_string(num);
    cout << whiletag << ":"   << endl;
    stm->condicion->accept(this);
    cout << "cmpq $0 ,%rax"  << endl;;
    cout << "je " << endwhiletag   << endl;
    for(auto i:stm->stlist) {
        i->accept(this);
    }
    cout << "jmp " << whiletag   << endl;
    cout << endwhiletag << ":"   << endl;
}

void GencodeVisitor::code(Program* program){
    cout << ".section .rodata" << endl; //esta parte lo cambie xq no me corria en mi ubuntu :,( pero se supone que es lo mismo
    cout << "print_fmt: .string \"%ld\\n\" " << endl;
    cout << ".text" << endl;
    cout << ".globl main" << endl;
    cout << "main:" << endl;
    cout << "pushq %rbp" << endl;
    cout << "movq %rsp, %rbp" << endl;
    cout << "sub $32, %rsp" << endl; 
    for (auto i:program->slist){
        i->accept(this);
    }
    cout << "movl $0, %eax" << endl;
    cout << "leave" << endl;
    cout << "ret" << endl;
    cout << ".section .note.GNU-stack,\"\",@progbits" << endl;
};

