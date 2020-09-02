#include "grid.h"
#include "canvas.h"

#include <QDebug>
#include <QPainter>
#include <QPen>
#include <QSize>

void Grid::setSize(const QSize &s)
{
    m_size = s;
    if(not m_sizeSet){
        m_position.setX(m_size.width() / 2 - m_offset.x());
        m_position.setY(m_size.height() / 2 - m_offset.y());
        m_sizeSet = true;
        return;
    }
}

void Grid::setScale(const int v)
{
    m_scale = std::max(std::min(int(m_scale) + v, 300), 50);
}

void Grid::setOffset(const QPointF &off)
{
    m_offset = off;
    m_position.setX(m_position.x() - m_offset.x());
    m_position.setY(m_position.y() - m_offset.y());
}

const QPointF &Grid::position() const {
    return m_position;
}

const QSizeF& Grid::size() const{
    return m_size;
}

const QPointF& Grid::offset() const{
    return m_offset;
}

const qreal& Grid::scale() const{
    return m_scale;
}

void Grid::draw(QPainter &p)
{
    QPen pen(Qt::GlobalColor::black, 1.0, Qt::PenStyle::SolidLine);
    qreal m_dValue = 0.1;
    qreal m_d = m_dValue * m_scale;
    int counter = 0;

    p.setPen(pen);
    p.drawLine(int(m_position.x()), 0, int(m_position.x()), int(m_size.height()));
    p.drawLine(0, int(m_position.y()), int(m_size.width()), int(m_position.y()));

    //grid
    pen.setColor(Qt::GlobalColor::lightGray);
    pen.setStyle(Qt::PenStyle::DotLine);
    pen.setWidthF(0.5);
    p.setPen(pen);

    while(m_d + position().x() < m_size.width()){
        if(counter == 9){
            pen.setWidthF(1.0);
            pen.setColor(Qt::gray);
            pen.setStyle(Qt::PenStyle::SolidLine);
            p.setPen(pen);

            p.drawLine(m_position.x() + m_d, 0, m_position.x() + m_d, m_size.height());

            pen.setColor(Qt::GlobalColor::lightGray);
            pen.setStyle(Qt::PenStyle::DotLine);
            pen.setWidthF(0.5);
            p.setPen(pen);

            counter = -1;
        } else {
            p.drawLine(m_position.x() + m_d, 0, m_position.x() + m_d, m_size.height());
        }

        counter++;
        m_dValue += 0.1;
        m_d = m_dValue * m_scale;
    }

    counter = 0;
    m_dValue = 0.1;
    m_d = m_dValue * m_scale;

    while(position().x() - m_d > 0){
        if(counter == 9){
            pen.setWidthF(1.0);
            pen.setColor(Qt::gray);
            pen.setStyle(Qt::PenStyle::SolidLine);
            p.setPen(pen);

            p.drawLine(m_position.x() - m_d, 0, m_position.x() - m_d, m_size.height());

            pen.setColor(Qt::GlobalColor::lightGray);
            pen.setStyle(Qt::PenStyle::DotLine);
            pen.setWidthF(0.5);
            p.setPen(pen);

            counter = -1;
        } else {
            p.drawLine(m_position.x() - m_d, 0, m_position.x() - m_d, m_size.height());
        }

        counter++;
        m_dValue += 0.1;
        m_d = m_dValue * m_scale;
    }

    counter = 0;
    m_dValue = 0.1;
    m_d = m_dValue * m_scale;

    while(position().y() + m_d < m_size.height()){
        if(counter == 9){
            pen.setWidthF(1.0);
            pen.setColor(Qt::gray);
            pen.setStyle(Qt::PenStyle::SolidLine);
            p.setPen(pen);

            p.drawLine(0, m_position.y() + m_d, m_size.width(), m_position.y() + m_d);

            pen.setColor(Qt::GlobalColor::lightGray);
            pen.setStyle(Qt::PenStyle::DotLine);
            pen.setWidthF(0.5);
            p.setPen(pen);

            counter = -1;
        } else {
            p.drawLine(0, m_position.y() + m_d, m_size.width(), m_position.y() + m_d);
        }

        counter++;
        m_dValue += 0.1;
        m_d = m_dValue * m_scale;
    }

    counter = 0;
    m_dValue = 0.1;
    m_d = m_dValue * m_scale;

    while(position().y() - m_d > 0){
        if(counter == 9){
            pen.setWidthF(1.0);
            pen.setColor(Qt::gray);
            pen.setStyle(Qt::PenStyle::SolidLine);
            p.setPen(pen);

            p.drawLine(0, m_position.y() - m_d, m_size.width(), m_position.y() - m_d);

            pen.setColor(Qt::GlobalColor::lightGray);
            pen.setStyle(Qt::PenStyle::DotLine);
            pen.setWidthF(0.5);
            p.setPen(pen);

            counter = -1;
        } else {
            p.drawLine(0, m_position.y() - m_d, m_size.width(), m_position.y() - m_d);
        }

        counter++;
        m_dValue += 0.1;
        m_d = m_dValue * m_scale;
    }
}
