/***************
 *
 * Wenn zu weit rausgezommt, Linien mit größerem Abstand zueinander;
 *
 * Wenn resized, dann wird die Position angepasst;
 *
 * Kann über den Rand verschoben werden (Oben und Links);
 *
 * Scale und Offset sollten nicht im Grid liegen;
 *
 * ************/


#ifndef GRID_H
#define GRID_H

#include <QRectF>

class QPainter;
class QSize;
class QPointF;
class QPen;

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
