#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>

enum Operand
{
    Op1,
    Op2,
    Result,
    Noperand
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

#endif // CONSTANTS_H
