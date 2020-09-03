#ifndef CANVAS_H
#define CANVAS_H

#include "grid.h"

#include <QPointF>
#include <QWidget>
#include "utils.h"

class Canvas : public QWidget
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = nullptr);

private:

    Grid m_grid;

    QPointF m_position = QPointF(0, 0);
    QPointF m_offset = QPointF(0, 0);
    QPointF m_dragStart;

    QSizeF m_size;

    qreal m_scale = 1.0;
    qreal m_angle = 0.0;

    bool dragged = false;

    void drawGrid(QPainter& p);
    void drawVector(QPainter& p, mats::Vec3 &vec);

protected:

    void    paintEvent(QPaintEvent *) override;
    void    wheelEvent(QWheelEvent *e) override;
    void    resizeEvent(QResizeEvent *e) override;
    void    mousePressEvent(QMouseEvent *e) override;
    void    mouseMoveEvent(QMouseEvent *e) override;
    void    mouseReleaseEvent(QMouseEvent *) override;

signals:

};

#endif // CANVAS_H
