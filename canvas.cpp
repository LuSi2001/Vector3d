#include <QDebug>
#include <QPainter>
#include <QWheelEvent>
#include <QResizeEvent>
#include <cmath>

#include "canvas.h"
#include "constants.h"
#include "draw.h"

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(1000, 800);
    m_position.setX(this->width()/2);
    m_position.setY(this->height()/2);
}

void Canvas::addDrawFunctor(DrawOperation *functor)
{
    m_operationDrawFunctors[functor->operation()].reset(functor);
}

void Canvas::drawGrid(QPainter &p)
{
    m_grid.draw(p, m_position, m_scale, rect());
}

void Canvas::drawArrows(QPainter &p){
    QPen pen(Qt::red, 0.5, Qt::SolidLine);
    QBrush brush(Qt::red);
    QPainterPath path;

    pen.setCosmetic(true);
    p.setPen(pen);

    for(int i = Op1; i <= Result; i++)
    {
        if(i == Op2 and (m_operator == Mal or m_operator == Geteilt)) continue;
        if(m_operands[i].length() > 1)
        {
            const mats::Vec3    &dir = m_operands[i].normalized();

            QPointF first(mats::v2q(m_operands[i] - dir - dir.perp2D() * 0.25));
            QPointF second(first + mats::v2q(dir.perp2D() * 0.5));
            QPolygonF polygon;

            if(i == Result)
            {
                QPainterPath path2;
                QBrush brush2(Qt::blue);
                pen.setColor(Qt::blue);
                p.setPen(pen);
                polygon << first * 10 << second * 10 << mats::v2q(m_operands[i] * 10);
                path2.addPolygon(polygon);
                p.fillPath(path2, brush2);
                continue;
            }

            polygon << first * 10 << second * 10 << mats::v2q(m_operands[i] * 10);

            path.addPolygon(polygon);
            p.drawConvexPolygon(polygon);
            p.fillPath(path, brush);
        }
    }
}

/* ++++++++++++++++++++++++++++++++SLOTS+++++++++++++++++++++++++++++++ */
void Canvas::calcResult()
{
    m_result = true;

    auto it = m_operationDrawFunctors.find(m_operator);
    if (it != m_operationDrawFunctors.end())
    {
        m_operands[Result] = it->second->calcResult(m_operands[Op1], m_operands[Op2]);
    }

    emit finished(m_operands[Result]);
}

void Canvas::noResults()
{
    if(m_result){ m_result = false; }
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

void Canvas::setOperator(const Operation &op)
{
    m_operator = op;
}

void Canvas::setVector(const mats::Vec3 &v, const Operand &op)
{
    m_operands[op] = v;
}

/* ++++++++++++++++++++++++++++++++EVENTS+++++++++++++++++++++++++++++++ */
void Canvas::mousePressEvent(QMouseEvent *e)
{
    m_dragStart = e->localPos();
    m_picked = Noperand;
    for(int i = Op1; i <= Op2; i++)
    {
        mats::Vec3 vec(m_position.x() + m_operands[i].x() * 10 * m_scale,
                       m_position.y() - m_operands[i].y() * 10 * m_scale);
        mats::Vec3  step = vec - mats::q2v(e->localPos());
        qreal d = step.length();
        if(d < 5)
        {
            m_picked = i;
            m_cursor.setShape(Qt::PointingHandCursor);
            emit cursorChange(m_cursor);
            break;
        }
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *e)
{
    if(e->modifiers() == Qt::ShiftModifier)
    {
        m_position = m_position - (m_dragStart - e->localPos());
        m_dragStart = e->localPos();
        update();
        return;
    }
    if (m_picked == Noperand) return;
    if(m_picked == Op2 and (m_operator == Mal or m_operator == Geteilt))
    {
        return;
    };

    m_operands[m_picked].x() = m_operands[m_picked].x() - ((m_dragStart.x() - e->localPos().x()) / m_scale * 0.1);
    m_operands[m_picked].y() = m_operands[m_picked].y() + ((m_dragStart.y() - e->localPos().y()) / m_scale * 0.1);

    m_dragStart = e->localPos();

    emit vChanged(m_operands[m_picked], m_picked);
    update();
}

void Canvas::mouseReleaseEvent(QMouseEvent *)
{
    calcResult();
    m_cursor.setShape(Qt::ArrowCursor);

    emit cursorChange(m_cursor);
}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    QFont font;
    font.setBold(true);
    font.setPixelSize(int(16));
    p.setFont(font);

    auto it = m_operationDrawFunctors.find(m_operator);

    p.drawText(QPointF(10, m_position.y() + 20), "x");
    p.drawText(QPointF(m_position.x() + 10, 20), "y");
    p.drawText(QPointF(m_position.x() + m_operands[Op1].x() * 10 * m_scale + 10, m_position.y() - m_operands[Op1].y() * 10 * m_scale + 10), "v1");

    if (not it->second->op2IsScalar())
    {
        p.drawText(QPointF(m_position.x() + m_operands[Op2].x() * 10 * m_scale + 10, m_position.y() - m_operands[Op2].y() * 10 * m_scale + 10), "v2");
    }

    p.translate(m_position.x(), m_position.y());
    p.scale(m_scale, m_scale);

    drawGrid(p);
    QPen pen(Qt::yellow, 1.0, Qt::SolidLine);
    pen.setColor(Qt::red);
    pen.setCosmetic(true);
    p.setPen(pen);

    if (it != m_operationDrawFunctors.end())
    {
        it->second->draw(p,
                         m_operands[Op1] * 10,
                         m_operands[Op2] * 10,
                         m_operands[Result] * 10,
                         m_result);
    }

    drawArrows(p);

    update();
}

void Canvas::resizeEvent(QResizeEvent *e)
{
    m_size = e->size();
    update();
}

void Canvas::wheelEvent(QWheelEvent *e)
{

    if((m_zoom + e->delta()/120) < 92 or (m_zoom + e->delta()/120) > 115)
    {
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



