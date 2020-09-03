#include <QDebug>
#include <QPainter>
#include <QWheelEvent>
#include <QResizeEvent>
#include <cmath>

#include "canvas.h"

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(1000, 800);
    m_position.setX(this->width()/2);
    m_position.setY(this->height()/2);
}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter    p(this);

    p.translate(m_position.x(), m_position.y());
    p.scale(m_scale, m_scale);

    p.fillRect(QRect(50, 50, 100, 170), Qt::green);

    drawGrid(p);
}

void Canvas::resizeEvent(QResizeEvent *e){
    m_size = e->size();
    update();
}

void Canvas::wheelEvent(QWheelEvent *e)
{
  qreal fac;

  if (e->delta() > 0)
  {
    fac = 1.25;
  }
  else
  {
    fac = 0.8;
  }

  m_scale *= fac;
  m_position = ((m_position - e->posF()) * fac) + e->posF();

  update();
}


void Canvas::mousePressEvent(QMouseEvent *e){
    if(e->modifiers() == Qt::ShiftModifier){
        m_dragStart = e->pos();
        dragged = true;
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *e){
    if(dragged && e->modifiers() == Qt::ShiftModifier){
        m_position = {m_position.x() - (m_dragStart.x() - e->pos().x()), m_position.y() - (m_dragStart.y() - e->pos().y())};
        m_dragStart = e->pos();
        update();
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *){
    dragged = false;
}

void Canvas::drawGrid(QPainter &p){
    m_grid.draw(p, m_position, m_scale, m_size);
}

void Canvas::drawVector(QPainter &p, mats::Vec3 &vec){

}
