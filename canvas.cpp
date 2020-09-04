#include <QDebug>
#include <QPainter>
#include <QWheelEvent>
#include <QResizeEvent>
#include <cmath>

#include "canvas.h"
#include "constants.h"

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(1000, 800);
    m_position.setX(this->width()/2);
    m_position.setY(this->height()/2);
}

void Canvas::reset()
{
    m_position.setX(this->width()/2);
    m_position.setY(this->height()/2);
    m_scale = 1.0;
    m_zoom = 100;
    update();
    emit deleteAllEntries();
}

void Canvas::setVector(const mats::Vec3 &v, Operand op)
{
    m_operands[op] = v;
}

void Canvas::setOperator(const QString& op){
    m_operator = op;
}

void Canvas::calcResult(){
    if(m_operator == "+"){
        m_operands[Result] = m_operands[Op1] + m_operands[Op2];
    } else if(m_operator == "-"){
        m_operands[Result] = m_operands[Op1] - m_operands[Op2];
    } else if(m_operator == "x"){
        m_operands[Result] = m_operands[Op1] ^ m_operands[Op2];
    } else if(m_operator == "*"){

    }
    emit finished(m_operands[Result], 3);
    qDebug() << m_operands[Result];
}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter    p(this);

    QRectF  miniRect(rect().topLeft() + QPointF(100, 100),
                     rect().bottomRight() - QPointF(200, 200));
    mats::Vec3 vec(20.0, 40.0, 0.0);

    QFont font;
    font.setBold(true);
    font.setPixelSize(int(16));
    p.setFont(font);

    p.drawText(QPointF(10, m_position.y() + 20), "x");
    p.drawText(QPointF(m_position.x() + 10, 20), "y");

//    p.setClipRect(miniRect);

    p.translate(m_position.x(), m_position.y());
    p.scale(m_scale, m_scale);

    drawVector(p, QPointF(0, 0), m_operands[Op1]);
    drawVector(p, QPointF(0, 0), m_operands[Op2]);
    drawVector(p, QPointF(0, 0), m_operands[Result]);
//    p.fillRect(QRect(50, 50, 100, 170), Qt::green);

    drawGrid(p);

    update();
}

void Canvas::resizeEvent(QResizeEvent *e){
    m_size = e->size();
    update();
}

void Canvas::wheelEvent(QWheelEvent *e)
{

  if((m_zoom + e->delta()/120) < 92 or (m_zoom + e->delta()/120) > 115){
      return;
  }

  m_zoom += e->delta()/120;

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

    QRectF  miniRect(rect().topLeft() + QPointF(100, 100),
                     rect().bottomRight() - QPointF(200, 200));

    m_grid.draw(p, m_position, m_scale, rect());
}

void Canvas::drawVector(QPainter &p, QPointF from, mats::Vec3 &vec){
    QPointF to = mats::v2q(vec);
    QColor color(COLOR[m_colorIndex]);
    QPen pen(Qt::red, 1.0, Qt::SolidLine);
    pen.setCosmetic(true);
    p.setPen(pen);
    p.drawLine(int(from.x()), int(from.y()), int(to.x() * 10), int(- to.y() * 10));
    m_colorIndex++;
    if(m_colorIndex == 6){
        m_colorIndex = 5;
    }
}
