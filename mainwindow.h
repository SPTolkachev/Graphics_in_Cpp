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

private:
    Ui::MainWindow *ui;
    CoordPlane *cplane;
};

#endif // MAINWINDOW_H
