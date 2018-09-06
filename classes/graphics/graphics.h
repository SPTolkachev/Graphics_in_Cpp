#ifndef GRAPHICS_H
#define GRAPHICS_H

//#include <QMainWindow>
#include "ui_mainwindow.h"
//#include <QGraphicsTextItem>
//#include "coordplane.h"
//#include "mainwindow.h"
#include "../coordPlane/coordplane.h"


class Graphics {
protected:
    Ui::MainWindow *ui;
    CoordPlane *cp;


public:
    Graphics(Ui::MainWindow *ui, CoordPlane *cp);
    void Show();




};
#endif // GRAPHICS_H
