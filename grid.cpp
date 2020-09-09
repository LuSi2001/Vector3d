#include "grid.h"
#include "canvas.h"

#include <QPen>
#include <QPainter>

void Grid::draw(QPainter &p, const QPointF &pos, qreal scale, const QRectF &r) const
{
    QPen pen(Qt::GlobalColor::lightGray, 0.5, Qt::PenStyle::DotLine);
    QPen pen2(Qt::GlobalColor::gray, 1.0, Qt::PenStyle::SolidLine);
    QPen pen3(Qt::GlobalColor::black, 1.0, Qt::PenStyle::SolidLine);

    pen.setCosmetic(true);
    pen2.setCosmetic(true);
    pen3.setCosmetic(true);

    p.setPen(pen);

    QPointF sPos(-pos / scale);
    QRectF  sRect(r.topLeft() / scale, r.bottomRight() / scale);

    QLineF  hLine;
    QLineF  vLine;

    constexpr qreal step = 10.0;

    drawLines(p, sRect, sPos, step);

    p.setPen(pen2);

    constexpr qreal step10 = step * 10.0;

    drawLines(p, sRect, sPos, step10);

    p.setPen(pen3);

    hLine.setLine(sRect.left() + sPos.x(), 0.0, sRect.right() + sPos.x(), 0.0);
    vLine.setLine(0.0, sRect.bottom() + sPos.y(), 0.0, sRect.top() + sPos.y());

    p.drawLine(hLine);
    p.drawLine(vLine);
}

void Grid::drawLines(QPainter &p, const QRectF &sRect,
                     const QPointF &sPos, const qreal d) const
{
    QLineF  hLine;
    QLineF  vLine;

    // horizontal lines
    qreal iy = qreal(int((sPos.y() + sRect.top()) / d) * int(d));
    for (qreal y = iy; y < iy + sRect.bottom(); y += d)
    {
        hLine.setLine(sRect.left() + sPos.x(), y, sRect.right() + sPos.x(), y);
        p.drawLine(hLine);
    }

    // vertical lines
    qreal ix = qreal(int((sPos.x()  + sRect.left()) / d) * int(d));
    for (qreal x = ix; x < ix + sRect.right(); x += d)
    {
        vLine.setLine(x, sRect.bottom() + sPos.y(), x, sRect.top() + sPos.y());
        p.drawLine(vLine);
    }
}
