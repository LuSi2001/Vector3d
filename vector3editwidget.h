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
    bool scalarMode() const;
    void setReadOnly(bool r);
    void setValidator();

signals:

    void valueChanged(const mats::Vec3 &);

public slots:

    void deleteEntries();
    void fillEdits(const mats::Vec3 &v);
    void setResult(const mats::Vec3 &v);
    void toScalar();
    void toVector();

private slots:

    void coordinateChanged();

private:
    Ui::GroupBox *ui;

    bool m_scalarMode = false;
    bool m_valueSetExternally = false;
};

#endif // VECTOR3EDITWIDGET_H
