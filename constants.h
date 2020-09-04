#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>
#include <set>
#include <map>
#include <QDebug>

static const char* COLOR[6] = {"yellow", "green", "cyan", "blue", "magenta", "red"};

enum Operand
{
    Op1,
    Op2,
    Result,
    NumOperands
};

enum Operation
{
    Nop,
    Plus,
    Minus,
    Mal,
    Geteilt,
    Kreuzprodukt,
    Skalarprodukt
};

struct NamedOp
{
     QString    name;
     Operation  op;

//     bool operator<(const NamedOp &op) const
//     {
//         return name < op.name;
//     }
};

struct NamedOpLess1
{
    bool operator()(const NamedOp &op0, const NamedOp &op1) const
    {
        return op0.name < op1.name;
    }
};

struct NamedOpLess2
{
    bool operator()(const NamedOp &op0, const NamedOp &op1) const
    {
        return op0.op < op1.op;
    }
};

static const NamedOp NameOperation[] =
{
    {"+", Plus},
    {"-", Minus},
    {"*", Mal},
    {"/", Geteilt},
    {"x", Kreuzprodukt},
    {"°", Skalarprodukt},
    {"", Nop}
};

using NamedOperationSet = std::set<NamedOp, NamedOpLess1>;
using NamedOperationMap = std::map<QString, NamedOp>;

static NamedOperationMap   g_namedOperations;

inline Operation    getOp(const QString &opStr) {
    return g_namedOperations.find(opStr)->second.op;
}

#endif // CONSTANTS_H
