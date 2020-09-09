#ifndef GRID_H
#define GRID_H

#include <QRectF>

class QPainter;

class Grid
{
public:
    Grid() = default;
    void draw(QPainter &p, const QPointF &pos, qreal scale, const QRectF &r) const;

private:
    void drawLines(QPainter &p, const QRectF &sRect,
                   const QPointF &sPos, const qreal d) const;
};

#endif // GRID_H
