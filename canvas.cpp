#include <QDebug>
#include <QPainter>
#include <QWheelEvent>
#include <QResizeEvent>
#include <cmath>

#include "canvas.h"

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(600, 600);
}

void Canvas::resizeEvent(QResizeEvent *e)
{
    m_grid.setSize(e->size());

    update();
}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter    p(this);
    mats::Vec3 v;
    mats::Vec3 z(1.0, 2.0, 3.0);
    mats::Vec3 y(3.0, 2.8, 9.1);
    drawGrid(p);
    drawVector(p, z);
}

void Canvas::wheelEvent(QWheelEvent *e)
{
    if(m_grid.scale() < 300 && m_grid.scale() > 50){
        qreal xStep = (m_grid.position().x() - e->pos().x());
        qreal yStep = (m_grid.position().y() - e->pos().y());
        xStep = xStep/(m_grid.scale() / 4);
        yStep = yStep/(m_grid.scale() / 4);
        if(e->delta()/30 > 0){
            m_grid.setOffset(QPointF(-xStep, -yStep));
        } else {
            m_grid.setOffset(QPointF(xStep, yStep));
        }
    }
    qDebug() << m_grid.scale();
    m_grid.setScale(e->delta()/30);
    update();
}

void Canvas::mousePressEvent(QMouseEvent *e)
{
    if(e->modifiers() == Qt::ShiftModifier){
        m_startPos = e->pos();
        drag = true;
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *e){
    if(drag && e->modifiers() == Qt::ShiftModifier){
        QPointF endPos(m_startPos.x() - e->pos().x(), m_startPos.y() - e->pos().y());
        m_grid.setOffset(endPos);
        update();
    }
    m_startPos = e->pos();
}

void Canvas::mouseReleaseEvent(QMouseEvent *)
{
    drag = false;
}

void Canvas::drawGrid(QPainter& p)
{
    m_grid.draw(p);
}

void Canvas::drawVector(QPainter& p, mats::Vec3 &vec){
    QPointF to = mats::v2q(vec);
    p.setPen(QPen(Qt::GlobalColor::red, 1.0, Qt::PenStyle::SolidLine));
    p.drawLine(m_grid.position().x(), m_grid.position().y(), m_grid.position().x() + to.x() * 10 * (m_grid.scale()/100), m_grid.position().y() + to.y() * 10 * (m_grid.scale()/100));
}
