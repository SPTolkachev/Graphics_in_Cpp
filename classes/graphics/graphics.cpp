//#include "coordplane.h"
#include "graphics.h"
#include <iostream>
#include <math.h>

Graphics::Graphics(Ui::MainWindow *ui, CoordPlane *cp/*, QGraphicsView *scene*/) {
    this->ui = ui;
    this->cp = cp;
    this->scene = scene;//this->cp->GetScene();//new QGraphicsScene(ui->graphicsView);
    this->canvas  = this->ui->graphicsView->viewport();
    this->toDefaultCoordArrays();

    //this->Show();
}

void Graphics::toDefaultCoordArrays() {

    for(int i=0; i < this->steps; i++) {
        this->arrayXCoords[i] = 0;//this->initialDouble;
        this->arrayYCoords[i] = 0;//this->initialDouble;
        this->arrayCanvasXCoords[i] = 0;//this->initialDouble;
        this->arrayCanvasYCoords[i] = 0;//this->initialDouble;
        //std::cout << i << ", ";
    }

    //std::cout << "\n9: " << this->arrayXCoords[8] << "\n";

    //std::cout << "arrays[0][5] = " << arrays[0][5] << "\n";
    //std::cout << (std::numeric_limits<double>::is_iec559 == 1.1 ? "true" : "false")  << "\n";
}


int Graphics::GetDots() {
    return (this->steps + 1);
}


void Graphics::refillCoordArrays() {

    double X  = this->cp->GetX();
    //double Y  = this->cp->GetY();
    double Xe = this->cp->GetXe();
    //double Ye = this->cp->GetYe();

    std::cout << "X: " << X << " -> " << Xe << "\n";
    double step = (Xe - X) / this->steps;
    int    dots = this->GetDots();


    std::cout << "X:\n";
    for(int i=0; i < dots; i++) {
        this->arrayXCoords[i] = X + i * step;
        this->arrayYCoords[i] = this->calculateYValue( this->arrayXCoords[i] );
        std::cout <<"    this->arrayXCoords["<< i <<"] = " << this->arrayXCoords[i] << ";    this->arrayYCoords["<< i <<"] = " << this->arrayYCoords[i] << ";\n";
    }
    std::cout << "\n";

    QPen pen(QColor(225, 225, 225));
    double X_PsiP = this->cp->GetX_PsiP();
    double Y_PsiP = this->cp->GetY_PsiP();

    for(int i=0; i < this->steps; i++) {
        if(i) {
            double x0 = this->arrayXCoords[i-1] / X_PsiP;
            double y0 = this->arrayYCoords[i-1] / Y_PsiP;
            double x1 = this->arrayXCoords[i]   / X_PsiP;
            double y1 = this->arrayYCoords[i]   / Y_PsiP;

            this->scene->addLine(x0, y0,  x1, y1,  pen);
            std::cout << "this->scene->addLine("<<x0<<", "<<y0<<", "<<x1<<", "<<y1<<", pen);\n";
        }
    }

}


double Graphics::calculateYValue(double X) {
    return (X * X);
}

/*
void Graphics::clearScene() {
    this->scene = new QGraphicsScene(ui->graphicsView);
}
*/

void Graphics::Show() {
    //this->clearScene();
    this->refillCoordArrays();
    //ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    //ui->graphicsView->setScene(scene);
    this->cp->SetScene();
}
