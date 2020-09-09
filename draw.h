#ifndef DRAW_H
#define DRAW_H

#include <QPainter>
#include <cmath>
#include <map>
#include <memory>

#include "utils.h"
#include "constants.h"

struct DrawOperation
{
        DrawOperation() = default;

        virtual Operation operation() const = 0;
        virtual mats::Vec3 calcResult(const mats::Vec3 &v1, const mats::Vec3 &v2) = 0;
        virtual void draw(QPainter &p, const mats::Vec3 &v1, const mats::Vec3 &v2,
                          const mats::Vec3 &vResult, bool result) const = 0;
        virtual bool op2IsScalar() const {return false;}

        virtual ~DrawOperation() = default;
};

struct PlusDrawOperation : public DrawOperation
{

    Operation operation() const override {return Plus;}

    mats::Vec3 calcResult(const mats::Vec3 &v1, const mats::Vec3 &v2) override
    {
        return v1 + v2;
    }

    void draw(QPainter &p, const mats::Vec3 &v1, const mats::Vec3 &v2, const mats::Vec3 &vResult, bool result) const override
    {
        p.scale(1.0, -1.0);

        p.drawLine(QPointF(), v2q(v1));
        p.drawLine(QPointF(), v2q(v2));
        if(result)
        {
            QPen pen(Qt::darkBlue, 1.0, Qt::DotLine);
            pen.setCosmetic(true);
            p.setPen(pen);
            p.drawLine(v2q(v1), v2q(vResult));
            p.drawLine(v2q(v2), v2q(vResult));
            QPen pen2(Qt::blue, 1.0, Qt::SolidLine);
            pen2.setCosmetic(true);
            p.setPen(pen2);
            p.drawLine(QPointF(), v2q(vResult));
        }

        p.scale(1.0, 1.0);
    }
};

struct MinusDrawOperation : public DrawOperation
{

    Operation operation() const override {return Minus;}

    mats::Vec3 calcResult(const mats::Vec3 &v1, const mats::Vec3 &v2) override
    {
        return v1 - v2;
    }

    void draw(QPainter &p, const mats::Vec3 &v1, const mats::Vec3 &v2, const mats::Vec3 &vResult, bool result) const override
    {
        p.scale(1.0, -1.0);

        p.drawLine(QPointF(), v2q(v1));
        p.drawLine(QPointF(), v2q(v2));
        if(result)
        {
            QPen pen(Qt::darkBlue, 1.0, Qt::DotLine);
            pen.setCosmetic(true);
            p.setPen(pen);
            p.drawLine(v2q(v1), v2q(vResult));
            p.drawLine(v2q(v1), v2q(v2));
            QPen pen2(Qt::blue, 1.0, Qt::SolidLine);
            pen2.setCosmetic(true);
            p.setPen(pen2);
            p.drawLine(QPointF(), v2q(vResult));
        }

        p.scale(1.0, 1.0);
    }
};

struct MultiplicationDrawOperation : public DrawOperation
{

    Operation operation() const override {return Mal;}

    mats::Vec3 calcResult(const mats::Vec3 &v1, const mats::Vec3 &v2) override
    {
        return v1 * v2.y();
    }

    void draw(QPainter &p, const mats::Vec3 &v1, const mats::Vec3 &v2, const mats::Vec3 &vResult, bool result) const override
    {
        p.scale(1.0, -1.0);

        p.drawLine(QPointF(), v2q(v1));
        if(result)
        {
            QPen pen2(Qt::blue, 1.0, Qt::SolidLine);
            pen2.setCosmetic(true);
            p.setPen(pen2);
            p.drawLine(QPointF(), v2q(vResult));
        }

        p.scale(1.0, 1.0);
    }

    bool op2IsScalar() const override {return true;}
};

struct DivisionDrawOperation : public DrawOperation
{

    Operation operation() const override {return Geteilt;}

    mats::Vec3 calcResult(const mats::Vec3 &v1, const mats::Vec3 &v2) override
    {
        return v1 / v2.y();
    }

    void draw(QPainter &p, const mats::Vec3 &v1, const mats::Vec3 &v2, const mats::Vec3 &vResult, bool result) const override
    {
        p.scale(1.0, -1.0);

        p.drawLine(QPointF(), v2q(v1));
        if(result)
        {
            QPen pen2(Qt::blue, 1.0, Qt::SolidLine);
            pen2.setCosmetic(true);
            p.setPen(pen2);
            p.drawLine(QPointF(), v2q(vResult));
        }

        p.scale(1.0, 1.0);
    }

    bool op2IsScalar() const override {return true;}
};

struct CrossProductDrawOperation : public DrawOperation
{

    Operation operation() const override {return Kreuzprodukt;}

    mats::Vec3 calcResult(const mats::Vec3 &v1, const mats::Vec3 &v2) override
    {
        return v1 ^ v2;
    }

    void draw(QPainter &p, const mats::Vec3 &v1, const mats::Vec3 &v2, const mats::Vec3 &vResult, bool result) const override
    {
        p.scale(1.0, -1.0);

        p.drawLine(QPointF(), v2q(v1));
        p.drawLine(QPointF(), v2q(v2));
        if(result)
        {
            QPen pen2(Qt::blue, 1.0, Qt::SolidLine);
            pen2.setCosmetic(true);
            p.setPen(pen2);
            p.drawLine(QPointF(), v2q(vResult));
            p.drawLine(QPointF(vResult.x() - 5, vResult.y() - 5), QPointF(vResult.x() + 5, vResult.y() + 5));
            p.drawLine(QPointF(vResult.x() - 5, vResult.y() + 5), QPointF(vResult.x() + 5, vResult.y() - 5));
        }

        p.scale(1.0, 1.0);
    }
};

struct DotProductDrawOperation : public DrawOperation{

    Operation operation() const override {return Skalarprodukt;}

    mats::Vec3 calcResult(const mats::Vec3 &v1, const mats::Vec3 &v2) override
    {
        mats::Vec3 v3 = v2;
        mats::Vec3 v4 = v1;
        double scalar = v4 * v3;
        return mats::Vec3(0, scalar, 0);
    }

    void draw(QPainter &p, const mats::Vec3 &v1, const mats::Vec3 &v2, const mats::Vec3 &vResult, bool result) const override
    {
        p.scale(1.0, -1.0);

        p.drawLine(QPointF(), v2q(v1));
        p.drawLine(QPointF(), v2q(v2));
        if(result)
        {
            QPen pen2(Qt::blue, 1.0, Qt::SolidLine);
            pen2.setCosmetic(true);
            p.setPen(pen2);
            int sqrt = int(std::sqrt(vResult.y()));
            p.drawRect(0, 0, sqrt, sqrt);
        }

        p.scale(1.0, 1.0);
    }
};

using DrawOperationMap = std::map<Operation, std::unique_ptr<DrawOperation>>;

#endif // DRAW_H
