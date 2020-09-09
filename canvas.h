#ifndef CANVAS_H
#define CANVAS_H

#include "grid.h"

#include <QPointF>
#include <QWidget>
#include "utils.h"
#include "constants.h"
#include "draw.h"

class Canvas : public QWidget
{
    Q_OBJECT

public:
    explicit Canvas(QWidget *parent = nullptr);
    void addDrawFunctor(DrawOperation *functor);

public slots:
    void calcResult();
    void noResults();
    void reset();
    void setVector(const mats::Vec3 &v, const Operand &op);
    void setOperator(const Operation &op);

signals:
    void cursorChange(const QCursor &cursor);
    void deleteAllEntries();
    void finished(const mats::Vec3 &v);
    void vChanged(const mats::Vec3 &v, const int mode);

private:
    Grid m_grid;

    QCursor m_cursor;

    QPointF m_position = QPointF(0, 0);
    QPointF m_offset = QPointF(0, 0);
    QPointF m_dragStart;

    QSizeF m_size;

    qreal m_scale = 1.0;
    qreal m_zoom = 100;

    int m_mode = 0;
    int m_picked = Noperand;

    bool m_result = false;

    mats::Vec3 m_operands[Noperand];

    Operation m_operator = Plus;
    DrawOperationMap m_operationDrawFunctors;

    void drawArrows(QPainter &p);
    void drawGrid(QPainter& p);

protected:
    void    mouseMoveEvent(QMouseEvent *e) override;
    void    mousePressEvent(QMouseEvent *e) override;
    void    mouseReleaseEvent(QMouseEvent *) override;
    void    paintEvent(QPaintEvent *) override;
    void    resizeEvent(QResizeEvent *e) override;
    void    wheelEvent(QWheelEvent *e) override;

signals:

};

#endif // CANVAS_H
