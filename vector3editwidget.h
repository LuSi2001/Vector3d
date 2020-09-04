#ifndef VECTOR3EDITWIDGET_H
#define VECTOR3EDITWIDGET_H

#include <QGroupBox>
#include "utils.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GroupBox; }
QT_END_NAMESPACE

class Vector3EditWidget : public QGroupBox
{
    Q_OBJECT
public:
    explicit Vector3EditWidget(QWidget *parent = nullptr);
    ~Vector3EditWidget();
    void setReadOnly(bool r);
    void toScalar();
    void toVector();
    void setResult(const mats::Vec3 &v, const int mode);
    bool scalarMode() const;

signals:

    void    valueChanged(const mats::Vec3 &);

public slots:

    void deleteEntries();

private slots:

    void    coordinateChanged();

private:
    Ui::GroupBox *ui;

    bool m_scalarMode = false;
};

#endif // VECTOR3EDITWIDGET_H
