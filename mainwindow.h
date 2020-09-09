#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "constants.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

signals:
    void resultCall();
    void specialChar(QString op);

private slots:
    void checkOp(Operation op) const;
    void newCursor(const QCursor &cursor);
    void on_equals_clicked() const;

};
#endif // MAINWINDOW_H
