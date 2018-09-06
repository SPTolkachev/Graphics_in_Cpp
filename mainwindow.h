#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "classes/coordPlane/coordplane.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void ShowGraph();

private slots:
    void on_renderButton_clicked();

    void on_scalePlane_valueChanged(double arg1);

    void on_to_upButton_clicked();

    void on_to_rightButton_clicked();

    void on_to_downButton_clicked();

    void on_to_leftButton_clicked();

    void on_to_leftUpButton_clicked();

    void on_to_rightUpButton_clicked();

    void on_to_rightBottomButton_clicked();

    void on_to_leftDownButton_clicked();

private:
    Ui::MainWindow *ui;
    CoordPlane *cplane;
};

#endif // MAINWINDOW_H
