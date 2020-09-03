#include "grid.h"
#include "canvas.h"

#include <QPen>
#include <QPainter>

void Grid::draw(QPainter &p, const QPointF &pos, qreal scale, const QSizeF &size) const{

    QPen pen(Qt::GlobalColor::lightGray, 0.5, Qt::PenStyle::DotLine);
    QPen pen2(Qt::GlobalColor::gray, 1.0, Qt::PenStyle::SolidLine);
    QPen pen3(Qt::GlobalColor::black, 1.0, Qt::PenStyle::SolidLine);

    pen.setCosmetic(true);
    pen2.setCosmetic(true);
    pen3.setCosmetic(true);

    p.setPen(pen);

    QSizeF  sSize(size / scale);
    QPointF sPos(-pos / scale);

    QLineF  hLine;
    QLineF  vLine;

    constexpr qreal step = 10.0;

    drawLines(p, sSize, sPos, step);

    p.setPen(pen2);

    constexpr qreal step10 = step * 10.0;

    drawLines(p, sSize, sPos, step10);

    p.setPen(pen3);

    hLine.setLine(sPos.x(), 0.0, sSize.width() + sPos.x(), 0.0);
    vLine.setLine(0.0, sPos.y(), 0.0, sSize.height() + sPos.y());

    p.drawLine(hLine);
    p.drawLine(vLine);
}

void Grid::drawLines(QPainter &p, const QSizeF &sSize,
                     const QPointF &sPos, const qreal d) const
{

    QLineF  hLine;
    QLineF  vLine;

    qreal           iy = qreal(int(sPos.y() / d) * int(d));

    for (qreal y = iy; y < iy + sSize.height() + d; y += d)
    {
        hLine.setLine(sPos.x(), y, sSize.width() + sPos.x(), y);
        p.drawLine(hLine);
    }

    qreal   ix = qreal(int(sPos.x() / d) * int(d));

    for (qreal x = ix; x < ix + sSize.width() + d; x += d)
    {
        vLine.setLine(x, sPos.y(), x, sSize.height() + sPos.y());
        p.drawLine(vLine);
    }
}
