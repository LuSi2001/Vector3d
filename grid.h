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

#include <QPointF>
#include <QSizeF>

class QPainter;
class QSize;

class Grid
{
public:
    Grid() = default;
    void draw(QPainter &p);
    void setSize(const QSize &s);
    const QSizeF& size() const;
    void setScale(const int v);
    void setOffset(const QPointF &off);
    const QPointF &position() const;
    const QPointF &offset() const;
    const qreal& scale() const;

private:
    QPointF m_offset;
    QSizeF m_size;
    qreal m_scale = 100;
    QPointF m_position;
    bool m_sizeSet = false;
};

#endif // GRID_H
