#ifndef GRAPHICS_H
#define GRAPHICS_H

//#include <QMainWindow>
//#include "ui_mainwindow.h"
//#include <QGraphicsTextItem>
//#include "coordplane.h"
//#include "mainwindow.h"


class Graphics {
protected:
    CoordPlane *cp;


public:
    Graphics(CoordPlane *cp);
    Show();




};
#endif // GRAPHICS_H
