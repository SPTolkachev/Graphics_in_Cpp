#include "coordplane.h"
#include <iostream>
#include <math.h>

CoordPlane::CoordPlane(Ui::MainWindow *ui, /* QGraphicsView scene, */double x, double y, double scale/*, int steps*/) {
    this->SetX(x);
    this->SetY(y);
    this->SetScale(scale);
    this->ui = ui;
    this->scene = new QGraphicsScene(ui->graphicsView);
    //this->SetSteps(steps);


    this->canvas  = this->ui->graphicsView->viewport();
}

double CoordPlane::GetX() {
    return this->X;
}

void CoordPlane::SetX(double x) {
    this->X = x;
}

double CoordPlane::GetXe() {
    double Xe = this->Xe;
    //std::cout << "Xe* = " << Xe << ";\n";
    if(Xe == 0) {
        Xe = this->GetX() + this->GetScale();
        std::cout << "Xe = " << Xe << ";\n";
        this->SetXe(Xe);
    }
    return Xe;
}

void CoordPlane::SetXe(double Xe) {
    this->Xe = Xe;
}


double CoordPlane::GetY() {
    return this->Y;
}

void CoordPlane::SetY(double y) {
    this->Y = y;
}

double CoordPlane::GetYe() {
    double Ye = this->Ye;
    //std::cout << "Ye* = " << Ye << ";\n";
    if(Ye == 0) {
        Ye = this->GetY() - this->GetScale();
        std::cout << "Ye = " << Ye << ";\n";
        this->SetYe(Ye);
    }
    return Ye;
}

void CoordPlane::SetYe(double Ye) {
    this->Ye = Ye;
}



double CoordPlane::GetScale() {
    return this->scale;
}


void CoordPlane::SetScale(double scale) {
    this->scale = scale;
}


int  CoordPlane::GetSteps() {
    // Кол-во шагов определяем динамически
    int steps = this->steps;

    if(steps == 0) {
        int stepSize;
        stepSize = ceil(this->GetScale() / 10);
        steps = this->GetScale() / stepSize;
        this->maxLines = steps + 1;
        std::cout << "steps = " << steps << ";\n";
        this->SetSteps(steps);
    }

    return steps;
}


void CoordPlane::SetSteps(int steps) {
    this->steps = steps;
}


int CoordPlane::GetXLines() {
    int lines = this->X_lines;

    if(lines == 0) {
        //std::cout << "\n\nGetLines\n";
        int stepLength = this->GetStep();
        double fromX = this->GetFromX();
        double toX = this->GetXe();
        //std::cout << "fromX = " << fromX << " ++ " << stepLength << "; (" << this->GetX() << " -> " << toX << ")\n";
        //int allYSteps = ((this->GetX() == fromX) ? (this->GetSteps()+1) : (this->GetSteps() - 1));

        //std::cout << "allYSteps (" << this->GetY() << " == " << fromX << ") = " << allYSteps << ";\n";
        //std::cout << "Y: ";
        double currentStep = fromX;
        //lines = 1;
        std::cout  << "XLines: " << currentStep << ", ";
        while(currentStep + stepLength <= toX) {
            lines++;
            currentStep += stepLength;
            std::cout << currentStep << ", ";
        }
        SetXLines(++lines);
       std::cout << "; steps = " << lines << ";\n";
    }
    return lines;
}

void CoordPlane::SetXLines(int lines) {
    this->X_lines = lines;
}

int CoordPlane::GetYLines() {
    int lines = this->Y_lines;

    if(lines == 0) {
        //std::cout << "\n\nGetLines\n";
        int stepLength = this->GetStep();
        double toY = this->GetYe();
        double fromY = this->GetFromY();
        //std::cout << "fromX = " << fromX << " ++ " << stepLength << "; (" << this->GetX() << " -> " << toX << ")\n";
        //int allYSteps = ((this->GetX() == fromX) ? (this->GetSteps()+1) : (this->GetSteps() - 1));

        //std::cout << "allYSteps (" << this->GetY() << " == " << fromX << ") = " << allYSteps << ";\n";
        //std::cout << "Y: ";
        double currentStep = fromY;
        //lines = 1;
        //std::cout << "***" << currentStep + stepLength << " <= " << toY << "\n";
        std::cout << fromY << " -> " << toY << "\n";
        std::cout  << "YLines: " << currentStep << ", ";
        while(currentStep - stepLength >= toY) {
            lines++;
            currentStep -= stepLength;
            std::cout << currentStep << ", ";
        }
        this->SetYLines(++lines);
        std::cout << "; steps = " << lines << ";\n";

    }
    return lines;
}

void CoordPlane::SetYLines(int lines) {
    this->Y_lines = lines;
}


double CoordPlane::GetFromX() {
    double fromX = this->fromX;

    if(fromX == 0) {
        int correctX = this->GetX()*100;
        int stepLength = this->GetStep();
        int remainder = correctX % (stepLength * 100);
        remainder = correctX >= 0 ? -remainder : remainder;
        fromX = (correctX - remainder ) / 100;
        std::cout << "fromX = (" << correctX << " - (" << correctX << " % (" << stepLength << " * " << 100 << ") ) ) / " << 100 << "    =    ";
        std::cout <<  "(" << correctX << " - (" << correctX << " % (" << stepLength * 100 << ") ) ) / " << 100 << "    =    ";
        std::cout <<  "(" << correctX << " - (" << (correctX % (stepLength * 100)) << ") ) / " << 100 << "    =    ";
        std::cout <<  "(" << (correctX + (correctX % (stepLength * 100))) << ") / " << 100 << "     =     ";
        std::cout <<  (correctX + (correctX % (stepLength * 100) ) ) / 100 << "\n";
        this->SetFromX(fromX);
    }
    return fromX;
}

void   CoordPlane::SetFromX(double fromX) {
    this->fromX = fromX;
}


double CoordPlane::GetToX() {
    double toX = this->toX;

    if(toX == 0) {
        double fromX = this->GetFromX();
        double step  = this->GetStep();
        int    lines = this->GetXLines() - 1;
        toX = fromX + (step * lines);
        std::cout << "toX = " << fromX << " + (" << step << " * " << lines << ") = " << toX << ";\n";
        this->SetToX(toX);
    }
    return toX;
}

void   CoordPlane::SetToX(double toX) {
    this->toX = toX;
}



double CoordPlane::GetFromY() {
    double fromY = this->fromY;

    if(fromY == 0) {
        int correctY = this->GetY()*100;
        //std::cout << "\n\ncorrectY = " << correctY << "\n\n";
        int stepLength = this->GetStep();
        fromY = (correctY - abs(correctY % (stepLength * 100) ) ) / 100;
        std::cout << "fromY = (" << correctY << " - (" << correctY << " % (" << stepLength << " * " << 100 << ") ) ) / " << 100 << " = " << fromY << ";\n";
        this->SetFromY(fromY);
    }
    return fromY;
}

void   CoordPlane::SetFromY(double fromY) {
    this->fromY = fromY;
}


double CoordPlane::GetToY() {
    double toY = this->toY;

    if(toY == 0) {
        //double startY = this->GetY();
        double fromY = this->GetFromY();
        double step  = this->GetStep();
        int    lines = this->GetYLines() - 1 ;//(startY == fromY ? 1);
        toY = fromY - (step * lines);
        std::cout << "toY = " << fromY << " - (" << step << " * " << lines << ") = " << toY << ";\n";
        this->SetToY(toY);
    }
    return toY;
}

void   CoordPlane::SetToY(double toY) {
    this->toY = toY;
}



/**
 * @brief CoordPlane::GetStep
 * @return -- Возвращает величину шага на графике
 */
double CoordPlane::GetStep() {
    double step = this->step;

    if(step == 0) {
        step = ceil( this->GetScale() / this->GetSteps() );
        this->SetStep(step);
        std::cout << "step = " << step << ";\n";
    }
    // std::cout << this->GetScale() << " / " << this->GetSteps() << " = " << this->GetScale() / this->GetSteps() << "\n\n";
    //std::cout << "Get: " << this->GetScale() / this->GetSteps() << "\n";
    return step;
}

/**
 * @brief CoordPlane::SetStep
 * Устанавливает размер одного шага (между значениями соседних линий координатной прямой)
 * @param step -- назначаемое значение шага
 */
void CoordPlane::SetStep(double step) {
    this->step = step;
}





/**
 * @brief CoordPlane::GetStepCanvasWidth
 * @return -- Возвращает величину шага в canvas при построении горизонтальных линий
 */
double CoordPlane::GetStepCanvasWidth() {
    double stepCanvasWidth = this->stepCanvasWidth;
    if(stepCanvasWidth == 0) {
        // -1 т.к. первая в нулевой точке.
        int lines = this->GetXLines() - 1;

        double margin = this->GetProcentMarginLeft() + this->GetProcentMarginRight();
        stepCanvasWidth = (this->GetUsedCanvasWidth() * (1 - margin)) / lines; // / this->GetSteps()
        std::cout << "stepCanvasHeight = " << (this->GetUsedCanvasWidth() * (1 - margin)) << " / " << lines << " = " << stepCanvasWidth << ";\n";
        //stepCanvasWidth = this->GetUsedCanvasWidth() / this->GetSteps();
        //std::cout << "stepCanvasWidth = " << stepCanvasWidth << ";\n";
        this->SetStepCanvasWidth( stepCanvasWidth );
    }
    //std::cout << this->GetUsedCanvasWidth() << " / " << this->GetSteps() << " = " << this->GetUsedCanvasWidth() / this->GetSteps() << "\n\n";
    return stepCanvasWidth;
}

/**
 * @brief CoordPlane::SetStepCanvasWidth
 * @param width -- ширина холста
 */
void CoordPlane::SetStepCanvasWidth(double width) {
    this->stepCanvasWidth = width;
}


/**
 * @brief CoordPlane::GetStepCanvasHeight
 * @return -- Возвращает величину шага в canvas при построении вертикальных линий
 */
double CoordPlane::GetStepCanvasHeight() {
    double stepCanvasHeight = this->stepCanvasHeight;
    // std::cout << this->GetUsedCanvasHeight() << " / " << this->GetSteps() << " = " << this->GetUsedCanvasHeight() / this->GetSteps() << "\n\n";
    if( stepCanvasHeight == 0 ) {
        // -1 т.к. первая в нулевой точке.
        int lines = this->GetYLines() - 1; //- ((this->GetFromY() == this->GetY()) ? 1 : 0);
        /*
        double marginTop = (this->GetY() - this->GetFromY()) / this->GetScale();
        std::cout << "marginTop = " <<  "(" << this->GetY() <<" - " << this->GetFromY() << ") / " << this->GetScale() << " = " << marginTop << "\n";
        double marginBottom = abs(this->GetYe() - this->GetToY()) / this->GetScale();
        std::cout << "marginBottom = " <<  "(" << this->GetYe() <<" - " << this->GetToY() << ") / " << this->GetScale() << " = " << marginBottom << "\n";
        */
        double margin = this->GetProcentMarginTop() + this->GetProcentMarginBottom();
        stepCanvasHeight = (this->GetUsedCanvasHeight() * (1 - margin)) / lines; // / this->GetSteps()
        std::cout << "stepCanvasHeight = " << (this->GetUsedCanvasHeight() * (1 - margin)) << " / " << lines << " = " << stepCanvasHeight << ";\n";
        this->SetStepCanvasHeight( stepCanvasHeight );
    }
    return stepCanvasHeight;
}

/**
 * @brief CoordPlane::SetStepCanvasHeight
 * @param height -- высота шага между горизонтальными линиями координатной прямой
 */
void CoordPlane::SetStepCanvasHeight(double height) {
    this->stepCanvasHeight = height;
}


double CoordPlane::GetUsedCanvasWidth() {
    double realWidthCanvas = this->realWidthCanvas;
    if(realWidthCanvas == 0) {
        realWidthCanvas = this->canvas->width() - 50; // 60
        this->realWidthCanvas = realWidthCanvas;
        std::cout << "realWidthCanvas = " << realWidthCanvas << "\n";
    }
    return realWidthCanvas;
}

void CoordPlane::SetUsedCanvasWidth(double width) {
    this->realWidthCanvas = width;
}



double CoordPlane::GetUsedCanvasHeight() {
    double realHeightCanvas = this->realHeightCanvas;
    if(realHeightCanvas == 0) {
        realHeightCanvas = this->canvas->height() - 50;
        this->realHeightCanvas = realHeightCanvas;
        std::cout << "realHeightCanvas = " << realHeightCanvas << "\n";
    }
    return realHeightCanvas;
}

void CoordPlane::SetUsedCanvasHeight(double height) {
    this->realHeightCanvas = height;
}




double CoordPlane::GetCanvasLeftMargin() {
    double canvasLeftMargin = this->canvasLeftMargin;

    if(canvasLeftMargin == this->default_canvasLeftMargin) {
        canvasLeftMargin = this->GetProcentMarginLeft() * this->GetUsedCanvasWidth();
        std::cout << "canvasLeftMargin = " << this->GetProcentMarginLeft() << " * " << this->GetUsedCanvasWidth() << " = " << canvasLeftMargin << "\n";
        this->SetCanvasLeftMargin(canvasLeftMargin);
    }
    return canvasLeftMargin;
}

void CoordPlane::SetCanvasLeftMargin(double canvasLeftMargin) {
    this->canvasLeftMargin = canvasLeftMargin;
}




double CoordPlane::GetCanvasTopMargin() { //GetCanvasHMargin
    double canvasTopMargin = this->canvasTopMargin;

    if(canvasTopMargin == this->default_canvasTopMargin) {
        //double scale = this->GetScale();
        //double margin = this->GetY() - this->GetFromY();
        /*canvasTopMargin = (margin / scale) * this->GetUsedCanvasHeight();


        std::cout << "canvasTopMargin = (" << margin << " / " << scale << ") * " << this->GetUsedCanvasHeight() << " = ";
        std::cout << "(" << margin / scale << ") * " << this->GetUsedCanvasHeight() << " = " << canvasTopMargin << "\n";
        */
        canvasTopMargin = this->GetProcentMarginTop() * this->GetUsedCanvasHeight();
        std::cout << "canvasTopMargin = " << this->GetProcentMarginTop() << " * " << this->GetUsedCanvasHeight() << " = " << canvasTopMargin << "\n";
        /*
        double Y = this->GetY();
        double fromY = this->GetFromY();
        canvasTopMargin = (Y == fromY ? 0 : (this->GetUsedCanvasHeight() / (this->GetY() - this->GetFromY()) ) );
        std::cout << "canvasTopMargin = " << canvasTopMargin << "\n";
        */
        this->SetCanvasTopMargin(canvasTopMargin);
    }

    return canvasTopMargin;
}

void CoordPlane::SetCanvasTopMargin(double canvasTopMargin) {
    this->canvasTopMargin = canvasTopMargin;
}


/**
 * @brief refillCoordLinesArray
 * Обновление значений линий координатной плоскости
 */
void CoordPlane::refillCoordLinesArray() {
    // Переопределяем массив типов линий
    double step = this->GetStep();
    double startRange = 10.0;
    double endRange   =  1.0;
    while( !(startRange > step && step >= endRange) ) {
         //std::cout << startRange << " > " << step << " && " << step << " >= " << endRange << "\n";
        if( step < 10 ) {
            startRange /= 10;
            endRange   /= 10;
        }
        else {
            startRange *= 10;
            endRange   *= 10;
        }
    };
    //this->canvasLinesTypes[0] = startRange;
    //this->canvasLinesTypes[1] = endRange;
    // std::cout << "Полученные значения: startRange = " << startRange << ";\tendRange = " << endRange << ";\n";

    //int displayedLines = 11;


    // Определяем отступы от краев координатной прямой
    int correctX = abs(this->GetX()*100);
    //int correctY = abs(this->GetY()*100);

    int correctRange = endRange*100;

    //std::cout << "first line: " << (this->GetX() - (correctX % (this->GetStep()*100) ))/100 << "\n";
    //std::cout << "Полученные значения: correctX = " << correctX << ";\tcorrectY = " << correctY << "\tcorrectRange = " << correctRange << ";\n";
    int correctCLM = 0; // коррестировка canvas lines margins
    this->canvasVMargin = (correctX % correctRange) / 100.0;
    if(this->canvasVMargin >= 1.0) { // Находим дробную часть числа
        correctCLM = this->canvasVMargin;
        this->canvasVMargin = this->canvasVMargin - correctCLM;
    }
    //std::cout << "this->canvasLinesMargins[0] = " << this->canvasLinesMargins[0] << "\n";
    /*this->canvasHMargin = (correctY % correctRange) / 100.0;
    if(this->canvasHMargin >= 1.0) { // Находим дробную часть числа
        correctCLM = this->canvasHMargin;
        this->canvasHMargin = this->canvasHMargin - correctCLM;
    }
    std::cout << "this->canvasHMargin = " << this->canvasHMargin << ";\n";*/
    //std::cout << "Полученные значения: (" << correctY << " % " << correctRange << ") / " << 100.0 << " = " << abs(correctY % correctRange) / 100.0 << ";\n";
    //std::cout << "Полученные значения: (" << (correctY % correctRange) << ") / " << 100.0 << " = " << (correctY % correctRange) / 100.0 << ";\n";
    //std::cout << "Полученные значения: " << (50) / 100.0 << " = " << (correctY % correctRange) / 100.0 << ";\n";
    //std::cout << "Полученные значения: canvasLinesMargins[0] = " << canvasLinesMargins[0] << ";\tcanvasLinesMargins[1] = " << canvasLinesMargins[1] << ";\n";
    //canvasLinesMargins


    //canvasLinesTypes
    int stepLength = this->GetStep();

    // Вертикальные линии
    int x_lines = this->GetXLines();
    double fromX = this->GetFromX();
    std::cout << "fromX = " << fromX << "; (" << this->GetX() << " -> " << this->GetXe() << ")\n";
    std::cout << "X: ";
    for(int i=0; i < this->maxLines; i++) {
        if(i < x_lines) {
            //this->coordLinesX[i] = this->GetX() + (stepLength * i) + this->canvasVMargin;
            this->coordLinesX[i] = fromX + (i * stepLength);
            std::cout << this->coordLinesX[i] << ", ";
        }
        else {
            this->coordLinesX[i] = 0;
        }
        //std::cout << this->coordLinesX[i] << ", "; // -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5,
    }
    std::cout << "\n";
    //std::cout << "\n" << this->GetXe() << "\n\n\n";

    // Горизонтальные линии

    int y_lines = this->GetYLines();
    // Определяем начальную току шага
    double fromY = this->GetFromY();
    std::cout << "fromY = " << fromY << "; (" << this->GetY() << " -> " << this->GetYe() << ")\n";
    //int allYSteps = ((this->GetY() == fromY) ? (this->GetSteps()+1) : (this->GetSteps() - 1));
    // std::cout << "numsLines (" << this->GetY() << " == " << fromY << ") = " << numsLines << ";\n";
    // std::cout << "Y: ";
    for(int i=0; i < this->maxLines; i++) {
        if(i < y_lines) {
            this->coordLinesY[i] = fromY - (i * stepLength);
            //std::cout << fromY - (i * stepLength) << ", ";
        }
        else {
            this->coordLinesY[i] = 0;
        }
    }
    //std::cout << " (new)\n";

    /*
    std::cout << "Y: ";
    for(int i=0; i < this->maxLines; i++) {
        this->coordLinesY[i] = this->GetY() - (stepLength * i) - this->canvasHMargin;
        std::cout << this->coordLinesY[i] << ", ";
        //std::cout << this->GetY() << " - " << "(" << stepLength << " * " << i <<") - " << canvasLinesMargins[1] << " = " << this->coordLinesY[i] << "\n"; // 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5,
    }
    std::cout << "\n";
    */
    //std::cout << "\n" << this->GetY() << " " << this->GetYe() << "\n\n\n";
}


/**
 * @brief CoordPlane::ShowCoordLines
 * Функция отвечающая за вывод вертикальных и
 * горизонтальных линий
 */
void CoordPlane::ShowCoordLines() {
    QPen pen(QColor(225, 225, 225));
    int x_lines = this->GetXLines();
    double currX;
    double canvasLeftMargin = this->GetCanvasLeftMargin();
    // std::cout << "for до: " << this->maxLines-(this->canvasVMargin==0 ? 0 : 1) << "\n";
    for(int i=0/*(canvasLinesMargins[0]==0 ? 1 : 0)*/; i < x_lines /* this->maxLines-(this->GetCanvasLeftMargin()==0 ? 0 : 1)*/; i++) {
        //currX = (i + this->canvasVMargin) * this->GetStepCanvasWidth();
        currX = (i * this->GetStepCanvasWidth()) + canvasLeftMargin;
        //std::cout << "currX = (" << i << " * " << this->GetStepCanvasWidth() << ") + " << canvasLeftMargin << " = ";
        //std::cout << "currX = (" << i * this->GetStepCanvasWidth() << ") + " << canvasLeftMargin << " = ";
        //std::cout << (i * this->GetStepCanvasWidth()) + canvasLeftMargin << " = " << currX << "\n";
        scene->addLine(currX, 0,  currX, this->GetUsedCanvasHeight(), pen);
        //std::cout << "scene->addLine(" << currX << ", 0,  " << currX << ", " << this->GetUsedCanvasHeight() << ", pen);\n";
    }
    //std::cout << "\n\n" << this->realHeightCanvas << " " << this->realWidthCanvas << "\n";

    /*
    double currY;
    for(int i=0; i < (this->maxLines-(this->canvasHMargin==0 ? 0 : 1)); i++) {
        currY = (i + this->canvasHMargin) * this->GetStepCanvasHeight();
        //std::cout << "currX: " << currY << "\n";
        scene->addLine(0, currY, this->GetUsedCanvasWidth(), currY, pen);
    }
    */
    int y_lines = this->GetYLines();
    double currY;
    double canvasTopMargin = this->GetCanvasTopMargin();
    //double usedCanvasHeight = ;
    //double canvasHMargin = ( (this->GetY() - this->GetFromY()) / this->GetStep() ) * this->GetStepCanvasHeight();
    for(int i=0; i < y_lines; i++) {
        currY = (i * this->GetStepCanvasHeight()) + canvasTopMargin;
        //std::cout << "currY: " << "(" << i << " * " << this->GetStepCanvasHeight() << ") + " << canvasHMargin << " = " << currY << "\n";
        scene->addLine(0, currY, this->GetUsedCanvasWidth(), currY, pen);
    }
    //scene->addLine(0, 128, realWidth,  128, pen);//x
    //scene->addLine(128, 0,  128, realHeight, pen);//y


    /*
    QPen penRed(QColor(225, 0, 0));

    int startLine = 0;
    int correctX = this->GetX() * 100;
    */
}


/**
 * @brief CoordPlane::ShowCoordNums
 * Функция отвечающая за вывод числовых обозначений
 * вертикальных и горизонтальных линий
 */
void CoordPlane::ShowCoordLineNums() {
    QPen pen(QColor(175, 175, 175));

    int numsXLines = this->GetXLines();
    double canvasLeftMargin = this->GetCanvasLeftMargin();
    double currX, canvasX;
    //std::cout << "\n\nGetSteps: " << this->GetSteps() << "\n\n\n";
    double realHeightCanvas = this->GetUsedCanvasHeight() - 5;
    for(int i=0/*(canvasLinesMargins[0]==0 ? 0 : 1)*/; i < numsXLines /*this->maxLines-(this->canvasVMargin==0 ? 0 : 1)*/; i++) {
        //canvasX = (i + this->canvasVMargin) * this->GetStepCanvasWidth(); // Вывод координат canvas
        canvasX = (i /*+ this->canvasHMargin*/) * this->GetStepCanvasWidth() + canvasLeftMargin; // Вывод координат canvas
        currX = coordLinesX[i]; // Вывод реальных координат
        std::string currXString = toHandleNumber( std::to_string(currX) );
        QGraphicsTextItem *textItem = new QGraphicsTextItem(QString::fromUtf8(currXString.c_str()));
        textItem->setPos(canvasX-10, realHeightCanvas+35);
        textItem->setRotation(-90);
        //std::cout << "currX: " << currX << "\n";
        scene->addItem(textItem);
    }


    //scene->addLine(-10, this->realHeightCanvas-5, -11, this->realHeightCanvas-6, pen1);


    int numsYLines = this->GetYLines();
    double canvasTopMargin = this->GetCanvasTopMargin();
    double currY, canvasY;

    QPen penDebug(QColor(225, 0, 0));
    std::string currYString0 = toHandleNumber( std::to_string(this->GetY()) );
    QGraphicsTextItem *textItem0 = new QGraphicsTextItem( QString::fromUtf8(currYString0.c_str()) );
    textItem0->setDefaultTextColor( QColor(255, 0, 0) );
    textItem0->setPos(0, 0);
    scene->addItem(textItem0);

    for(int i=0; i < numsYLines; i++) {
        canvasY = (i /*+ this->canvasHMargin*/) * this->GetStepCanvasHeight() + canvasTopMargin; // Вывод координат canvas
        currY = coordLinesY[i]; // Вывод реальных координат
        std::string currYString = toHandleNumber( std::to_string(currY) );
        QGraphicsTextItem *textItem = new QGraphicsTextItem(QString::fromUtf8(currYString.c_str()));
        textItem->setPos(-35, canvasY-10);
        //textItem->setRotation(-90);
        //std::cout << "currX: " << currX << "\n";
        scene->addItem(textItem);
    }


    std::string currYString = toHandleNumber( std::to_string(this->GetYe()) );
    QGraphicsTextItem *textItem = new QGraphicsTextItem( QString::fromUtf8(currYString.c_str()) );
    textItem->setDefaultTextColor( QColor(255, 0, 0) );
    textItem->setPos(0, this->GetUsedCanvasHeight()-40);
    scene->addItem(textItem);
    /*double currY, canvasY;
    for(int i=0; i < (this->maxLines-(this->canvasHMargin==0 ? 0 : 1)); i++) {
        canvasY = (i + this->canvasHMargin) * this->GetStepCanvasHeight(); // Вывод координат canvas
        currY = coordLinesY[i]; // Вывод реальных координат
        std::string currYString = toHandleNumber( std::to_string(currY) );
        QGraphicsTextItem *textItem = new QGraphicsTextItem(QString::fromUtf8(currYString.c_str()));
        textItem->setPos(-35, canvasY-10);
        //textItem->setRotation(-90);
        //std::cout << "currX: " << currX << "\n";
        scene->addItem(textItem);
    }
    */


    /*
    QGraphicsTextItem *textItem = new QGraphicsTextItem(QString::fromUtf8(currXString.c_str()));
    textItem->setPos(currX-10, 90);
    textItem->setRotation(-90);
    scene->addItem(textItem);
    */
}


/**
 * @brief CoordPlane::toHandleNumber
 * Удаляет лишние нули в дробной части числа
 * @param  std::string str -- строка с лишними нулями
 * @return std::string     -- строка без лишних нулей
 */
std::string CoordPlane::toHandleNumber(std::string str) {
    //std::cout << "str.length(): " <<  str.length() << "\t";
    int comma = -1;
    int lastNotNull = -1;
    int strLength = str.length();
    for(int i=0; i < strLength; i++) {
        if( comma >= 0 ) {
            // Находим в дробной части последний не нуль
            if( str[i] != '0' ) {
                lastNotNull = i;
            }
        }
        else if( str[i] == ',' ) { // Находим запятую
            comma = i;
        }
        //std::cout << str[i];
    }
    //std::cout << "\n";

    if( lastNotNull == -1) {
        lastNotNull = comma - 1;
    }

    // Стираем ненужные символы
    for(int i=(lastNotNull + 1); i < strLength; i++) {
        str[i] = ' ';
    }

    //std::cout << "comma = " << comma << ";\tlastNotNull = " << lastNotNull << ";\n";
    //std::cout << "str: " << str << "\n";
    return str;
}


/**
 * @brief CoordPlane::clearScene
 * Очистка canvas
 */
void CoordPlane::clearScene() {
    this->scene = new QGraphicsScene(ui->graphicsView);
}


/**
 * @brief CoordPlane::Show
 * Функция отображения координатной плоскости
 */
void CoordPlane::Show() {
    // Назначем значения высоты и ширины холста


    this->clearScene();
    this->refillCoordLinesArray();
    this->ShowCoordLines();    // Выводим линии
    this->ShowCoordLineNums(); // Выводим значения линий

    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    ui->graphicsView->setScene(scene);

    std::cout << "-------------------------------------------\n\n\n";

    // Обнуляем ненужные свойства
    this->resetWorkProperties();

    //Это как раз создана сцена. Сцена - это класс для работы с 2D графикой.
    //Теперь, раз это график, то построим координатные оси X и Y.
    /*
    QSize sz1 = this->ui->graphicsView->baseSize();
    QSize sz2 = this->ui->graphicsView->frameSize();
    QSize sz4 = this->ui->graphicsView->size();
    QWidget *sz5 = this->ui->graphicsView->viewport(); // 319
    QRegion sz6 = this->ui->graphicsView->visibleRegion();


    int sz3 = this->ui->graphicsView->width();
    QMargins mrg = this->ui->graphicsView->contentsMargins();
    //std::cout << "Размеры: " << this->ui->graphicsView->baseSize();
    //std::cout << "Размеры: " << this->ui->graphicsView->frameSize();
    //std::cout << "Размеры: " << sz1.width() << " " << sz2.width() << " " << sz3 << "\n" << mrg.left() << " " << mrg.right() << "\n";
    //std::cout << "Размеры: " << sz1.height() << " " << sz2.height() << " " << sz3 << "\n" << mrg.top() << " " << mrg.bottom() << "\n";

    std::cout << "Размеры: " << sz2.width() << " " << sz6.end() << "\n";
    */
//this->x = -15;


    /*
    int coordLinesArray[2][11] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    }; // GetCanvasStepLength
*/
    QPen pen1(QColor(175, 175, 175)/*Qt::gray*/);//Просто выбираем цвет для карандашика
/*    double currX;
    for(int i=0; i < 10; i++) {
        currX = i * this->GetCanvasStepLength();
        std::cout << "currX: " << currX << "\n";
        scene->addLine(currX, 0,  currX, realHeight, pen1);

        std::string currXString = std::to_string(currX);
        std::cout << currXString << "\n";
        QGraphicsTextItem *textItem = new QGraphicsTextItem(QString::fromUtf8(currXString.c_str()));
        textItem->setPos(currX-10, 90);
        textItem->setRotation(-90);
        scene->addItem(textItem);
    }


    std::cout << realWidth << " " << this->GetSteps() << "\n";
    std::cout << "------------------------------\n\n\n\n\n";

    double lineStep = realWidth / 10;
    double startLTR = realWidth + fmod((this->x + realWidth), realWidth);

*/
    QPen pen(QColor(175, 175, 175)/*Qt::gray*/);//Просто выбираем цвет для карандашика
/*    pen.setWidth(2);
    //scene->addLine(0, 128, realWidth,  128, pen);//x
    //scene->addLine(128, 0,  128, realHeight, pen);//y

    ui->graphicsView->setScene(scene);
*/
}





double CoordPlane::GetProcentMarginLeft() {
    double marginLeft = this->procentMarginLeft;

    if(marginLeft == this->default_procentMarginLeft) {
        double correctX     = this->GetX() * 100;
        double correctFromX = this->GetFromX() * 100;
        double correctScale = this->GetScale() * 100;
        marginLeft = abs(correctX - correctFromX) / correctScale;
        std::cout << "marginLeft = " << "abs(" << correctX << " - " << correctFromX << ") / " << correctScale << " = ";
        std::cout << "abs(" << correctX - correctFromX << ") / " << correctScale << " = ";
        std::cout << abs(correctX - correctFromX) << " / " << correctScale << " = ";
        std::cout << marginLeft << "\n";
        this->SetProcentMarginLeft(marginLeft);
    }
    return marginLeft;
}

void CoordPlane::SetProcentMarginLeft(double pml) {
    this->procentMarginLeft = pml;
}



double CoordPlane::GetProcentMarginRight() {
    double marginRight = this->procentMarginRight;

    if(marginRight == this->default_procentMarginRight) {
        double correctXe = this->GetXe() * 100;
        double correctToX  = this->GetToX() * 100;
        double correctScale = this->GetScale() * 100;
        marginRight = abs(correctXe - correctToX) / correctScale;

        //marginRight = abs(this->GetXe() - this->GetToX()) / this->GetScale();
        std::cout << "marginRight = " <<  "(" << correctXe <<" - " << correctToX << ") / " << correctScale << " = " << marginRight << "\n";
        this->SetProcentMarginRight(marginRight);
    }
    return marginRight;
}

void CoordPlane::SetProcentMarginRight(double pmr) {
    this->procentMarginRight = pmr;
}




double CoordPlane::GetProcentMarginTop() {
    double marginTop = this->procentMarginTop;

    if(marginTop == this->default_procentMarginTop) {
        marginTop = (this->GetY() - this->GetFromY()) / this->GetScale();
        std::cout << "marginTop = " <<  "(" << this->GetY() <<" - " << this->GetFromY() << ") / " << this->GetScale() << " = " << marginTop << "\n";
    }
    return marginTop;
}

void CoordPlane::SetProcentMarginTop(double pmt) {
    this->procentMarginTop = pmt;
}


double CoordPlane::GetProcentMarginBottom() {
    double marginBottom = this->procentMarginBottom;

    if(marginBottom == this->default_procentMarginBottom) {
        double correctYe = this->GetYe() * 100;
        double correctToY  = this->GetToY() * 100;
        double correctScale = this->GetScale() * 100;
        marginBottom = abs(correctYe - correctToY) / correctScale;
        std::cout << "marginBottom = " <<  "(" << correctYe <<" - " << correctToY << ") / " << correctScale << " = ";
        std::cout << "(" << correctYe - correctToY << ") / " << correctScale << " = " << marginBottom << "\n";
    }
    return marginBottom;
}

void CoordPlane::SetProcentMarginBottom(double pmb) {
    this->procentMarginBottom = pmb;
}





void CoordPlane::resetWorkProperties() {
    this->SetXe(0.0);
    this->SetYe(0.0);
    this->SetSteps(0);
    this->SetStep(0);
    this->SetStepCanvasWidth(0);
    this->SetStepCanvasHeight(0);
    this->SetXLines(0);
    this->SetYLines(0);
    this->SetFromX(0);
    this->SetFromY(0);
    this->SetCanvasLeftMargin(this->default_canvasLeftMargin);
    this->SetCanvasTopMargin(this->default_canvasTopMargin);
    this->SetUsedCanvasWidth(0);
    this->SetUsedCanvasHeight(0);
    this->SetToX(0);
    this->SetToY(0);
    this->SetProcentMarginLeft(this->default_procentMarginLeft);
    this->SetProcentMarginRight(this->default_procentMarginRight);
    this->SetProcentMarginTop(this->default_procentMarginTop);
    this->SetProcentMarginBottom(this->default_procentMarginBottom);
}

