#include "graphics.h"
#include "../../libs/parsemathex/parsemathex.h"
#include <iostream>
#include <math.h>

Graphics::Graphics(Ui::MainWindow *ui, CoordPlane *cp, QGraphicsScene *scene) {
    this->ui = ui;
    this->cp = cp;
    this->scene  = scene;
    this->canvas = this->ui->graphicsView->viewport();
    this->debug  = this->ui->DebugFlag->isChecked();
    this->toDefaultCoordArrays();


    this->SetGraphicString( 0, ui->gFunc0->text() );
    //this->SetGraphicString( 1, ui->gFunc1->text() );
    //this->SetGraphicString( 2, ui->gFunc2->text() );

    //this->arrayGraphics[0] = (ui->gFunc0->text()).toUtf8().constData();
    //this->arrayGraphics[1] = (ui->gFunc1->text()).toUtf8().constData();
    //this->arrayGraphics[2] = (ui->gFunc2->text()).toUtf8().constData();

    this->SetGraphicColor( 0, ui->color_graph0->currentIndex() );
    //this->SetGraphicColor( 1, ui->color_graph1->currentIndex() );
    //this->SetGraphicColor( 2, ui->color_graph2->currentIndex() );

    //this->arrayGraphicsColors[0] = ui->color_graph0->currentIndex();
    //this->arrayGraphicsColors[1] = ui->color_graph1->currentIndex();
    //this->arrayGraphicsColors[2] = ui->color_graph2->currentIndex();
}

bool Graphics::GetDebug() {
    return this->debug;
}

void Graphics::SetDebug(bool debug) {
    this->debug = debug;
}




std::string Graphics::GetGraphicString(int num) {
    std::string result = "";
    if( num >= 0 && num <= this->graphics_numbers )
        result = this->arrayGraphics[num];

    return result;
}

void Graphics::SetGraphicString(int num, QString exp) {
    if( num >= 0 && num <= this->graphics_numbers )
        this->arrayGraphics[num] = exp.toUtf8().constData();
}


QColor *Graphics::GetGraphicColor(int num) {
    QColor * color;// = new QColor(0,0,0);
    if( num >= 0 && num <= this->graphics_numbers )
        color = this->usedColors[ this->arrayGraphicsColors[num] ];
    else
        color = this->usedColors[0];
    return color;
}

void Graphics::SetGraphicColor(int num, int color) {
    if( num >= 0 && num <= this->graphics_numbers )
        this->arrayGraphicsColors[num] = color;
}






double Graphics::calculateYValue(std::string exp, double X) {
    double result = 0;

    if( this->CheckExpression(exp) ) {
        std::string expression = "$x = " + std::to_string(X) + "; " + exp;

        char * charexpression = new char [expression.length()+1];
        strcpy (charexpression, expression.c_str());

        std::cout << expression << " = " << result << "\n";
        result = ParserMathExpression(charexpression);
    }

    return result;
}





void Graphics::toDefaultCoordArrays() {
    int dots = this->GetDots();
    //for(int i=0; i < this->graphics_numbers; i++) {
        for(int j=0; j < dots; j++) {
            this->arrayXCoords/*[i]*/[j] = 0;
            this->arrayYCoords/*[i]*/[j] = 0;
            this->arrayCanvasXCoords/*[i]*/[j] = 0;
            this->arrayCanvasYCoords/*[i]*/[j] = 0;
        }
    //}
}


int Graphics::GetDots() {
    return this->dots;
}


bool Graphics::CheckExpression(std::string exp) {
    if( exp.length() == 0 )
        return false;

    int openParenthesis  = 0;
    int closeParenthesis = 0;
    int exp_length = exp.length();
    for(int i=0; i < exp_length; i++) { // Проверяем скобки
        switch (exp[i]) {
            case '(':
                openParenthesis++;
                break;
            case ')':
                closeParenthesis++;
                break;
        }
    }

    if(openParenthesis != 0 && openParenthesis == closeParenthesis)
        return false;

    if(closeParenthesis != 0 && openParenthesis == closeParenthesis)
        return false;

    return true;
}


void Graphics::refillCoordArrays() {
    double X  = this->cp->GetX();
    double Y  = this->cp->GetY();
    double Xe = this->cp->GetXe();
    double Ye = this->cp->GetYe();

    if(this->debug) std::cout << "X: " << X << " -> " << Xe << "\n";
    int    dots = this->GetDots();
    double step = (Xe - X) / (dots - 1);

    double X_PsiP = this->cp->GetX_PsiP();
    double Y_PsiP = this->cp->GetY_PsiP();
    //for(int i=0; i < this->graphics_numbers; i++) {
        if(this->debug) std::cout << "X:\n";

        std::string exp = GetGraphicString(0/*i*/);
        /*if( this->CheckExpression(exp) )
            continue;*/
        if( this->CheckExpression(exp) ) {
        for(int j=0; j < dots; j++) {
            double x1 = X + j * step;
            double y1 = this->calculateYValue(exp, x1);

            double cnv_x1 = (x1  - X) / X_PsiP;
            double cnv_y1 = (-y1 + Y) / Y_PsiP;

            if(j) { // Проверка
                double x0 = this->arrayXCoords/*[i]*/[j-1];
                double y0 = this->arrayYCoords/*[i]*/[j-1];

                bool condition_x0 = (x0 >= X && x0 <= Xe);
                bool condition_x1 = (x1 >= X && x1 <= Xe);
                bool condition_y0 = (y0 <= Y && y0 >= Ye);
                bool condition_y1 = (y1 <= Y && y1 >= Ye);

                if(this->debug) {
                    std::cout << "\n";
                    std::cout << "condition_x0 = ("<<x0<<" >= "<<X<<" && "<<x0<<" <= "<<Xe<<") = "<< (condition_x0 ? "true" : "false") <<";   ";
                    std::cout << "condition_x1 = ("<<x1<<" >= "<<X<<" && "<<x1<<" <= "<<Xe<<") = "<< (condition_x1 ? "true" : "false") <<";\n";
                    std::cout << "condition_y0 = ("<<y0<<" <= "<<Y<<" && "<<y0<<" >= "<<Ye<<") = "<< (condition_y0 ? "true" : "false") <<";   ";
                    std::cout << "condition_y1 = ("<<y1<<" <= "<<Y<<" && "<<y1<<" >= "<<Ye<<") = "<< (condition_y1 ? "true" : "false") <<";\n";
                }

                int action = 0;
                action += condition_x0 ? 1000 : 0;
                action += condition_y0 ?  100 : 0;
                action += condition_x1 ?   10 : 0;
                action += condition_y1 ?    1 : 0;
                double *correctDot;

                switch (action) { // Корректировка
                    case 1011: // Y0 не попал в диапазон
                        if(this->debug) std::cout << "Пограничная ситуация (Y0) this->scene->addLine("<<x0<<", "<<y0<<",  "<<x1<<", "<<y1<<",  pen);\n";
                        correctDot = this->CorrectY0(exp, x0, y0, x1, y1);
                        this->arrayXCoords/*[i]*/[j-1] = correctDot[0];
                        this->arrayYCoords/*[i]*/[j-1] = correctDot[1];
                        this->arrayCanvasXCoords/*[i]*/[j-1] = ( correctDot[0] - X)  / X_PsiP;
                        this->arrayCanvasYCoords/*[i]*/[j-1] = (-correctDot[1] + Y)  / Y_PsiP;
                        break;
                    case 1110: // Y1 не попал в диапазон
                        if(this->debug) std::cout << "Пограничная ситуация (Y1) this->scene->addLine("<<x0<<", "<<y0<<",  "<<x1<<", "<<y1<<",  pen);\n";
                        correctDot = this->CorrectY1(exp, x0, y0, x1, y1);
                        if(correctDot[0] != correctDot[2] && correctDot[1] != correctDot[3]) {
                            x1     = correctDot[2];
                            y1     = correctDot[3];
                            cnv_x1 = ( correctDot[2] - X) / X_PsiP;
                            cnv_y1 = (-correctDot[3] + Y) / Y_PsiP;
                        }
                        break;
                }
            }

            this->arrayXCoords/*[i]*/[j] = x1;
            this->arrayYCoords/*[i]*/[j] = y1;

            this->arrayCanvasXCoords/*[i]*/[j] = cnv_x1;
            this->arrayCanvasYCoords/*[i]*/[j] = cnv_y1;
        }
        if(this->debug) std::cout << "\n";
        }
    //}
}



void Graphics::ShowLines() {
    int dots  = this->GetDots();
    double X  = this->cp->GetX();
    double Y  = this->cp->GetY();
    double Xe = this->cp->GetXe();
    double Ye = this->cp->GetYe();

    //for(int i=0; i < this->graphics_numbers; i++) {
        QPen pen(*this->GetGraphicColor(0/*i*/)/*QColor(0, 225, 0)*/);
        std::string exp = GetGraphicString(0/*i*/);
        /*if( this->CheckExpression(exp) )
            continue; */
        std::cout << exp << " " << (this->CheckExpression(exp) ? "true" : "false") << "\n";
    if( this->CheckExpression(exp) ) {
        for(int j=0; j < dots; j++) {
            if(j) {
                double x0 = this->arrayXCoords/*[i]*/[j-1];
                double y0 = this->arrayYCoords/*[i]*/[j-1];
                double x1 = this->arrayXCoords/*[i]*/[j];
                double y1 = this->arrayYCoords/*[i]*/[j];

                double cnv_x0 = this->arrayCanvasXCoords/*[i]*/[j-1];
                double cnv_y0 = this->arrayCanvasYCoords/*[i]*/[j-1];
                double cnv_x1 = this->arrayCanvasXCoords/*[i]*/[j];
                double cnv_y1 = this->arrayCanvasYCoords/*[i]*/[j];

                bool condition_x0 = (x0 >= X && x0 <= Xe) ? true : false;
                bool condition_x1 = (x1 >= X && x1 <= Xe) ? true : false;
                bool condition_y0 = (y0 <= Y && y0 >= Ye);
                bool condition_y1 = (y1 <= Y && y1 >= Ye);

                if(condition_x0 && condition_y0 && condition_x1 && condition_y1) {
                    this->scene->addLine(cnv_x0, cnv_y0,  cnv_x1, cnv_y1,  pen);
                    if(this->debug) std::cout << "Добавляем this->scene->addLine("<<x0<<", "<<y0<<", "<<x1<<", "<<y1<<", pen);\n";
                }
                else {
                    if(this->debug) std::cout << "Пропускаем this->scene->addLine("<<x0<<", "<<y0<<", "<<x1<<", "<<y1<<", pen);\n";
                }
            }
        }
    }
    //}
}




double *Graphics::CorrectY0(std::string exp, double X0, double Y0, double X1, double Y1) {
    if(this->debug) std::cout << "Переопределение координат с { "<<X0<<", "<<Y0<<", "<<X1<<",  "<<Y1<<"} ";
    double  cpY  = this->cp->GetY();
    double  cpYe = this->cp->GetYe();
    double *newCoord = new double[4];

    double differenceY = Y0 - Y1;
    double differenceX = X1 - X0;
    int    differenceXDots  = 10;
    double deviation  = differenceY / differenceXDots; // рассчитываем допустимое отклонение от края координатной плоскости
    deviation = deviation * (deviation > 0 ? 1 : -1);
    double cpY_dev  = cpY  - (deviation * 1.2); // Допустимая точка отклонения по верхнему краю
    double cpYe_dev = cpYe + (deviation * 1.2); // Допустимая точка отклонения по нижнему  краю

    double differenceXStep  = differenceX / differenceXDots;

    double currX0 = 0;
    double currY0 = 0;
    bool successfullyCorrect = false;

    for(int i=0; i <= differenceXDots; i++) {
        currX0 = X0 + i * differenceXStep;
        currY0 = calculateYValue(exp, currX0);

        if(
            (cpYe <= currY0 && currY0 <= cpYe_dev) || // по нижнему пределу
            (cpY  >= currY0 && currY0 >= cpY_dev)     // по верхнему пределу
          ) {
            successfullyCorrect = true;
            break;
        }
    }

    if(successfullyCorrect) {
        X0 = currX0;
        Y0 = currY0;
    }

    newCoord[0] = X0;
    newCoord[1] = Y0;
    newCoord[2] = X1;
    newCoord[3] = Y1;

    if(this->debug)  std::cout << "на { "<<X0<<", "<<Y0<<", "<<X1<<",  "<<Y1<<"};\n";

    return newCoord;
}

double *Graphics::CorrectY1(std::string exp, double X0, double Y0, double X1, double Y1) {
    if(this->debug) std::cout << "Переопределение координат с { "<<X0<<", "<<Y0<<", "<<X1<<",  "<<Y1<<"} ";
    double cpY  = this->cp->GetY();
    double cpYe = this->cp->GetYe();
    double* newCoord = new double[4];

    double differenceY = Y0 - Y1;
    double differenceX = X1 - X0;
    int    differenceXDots  = 10;
    double deviation  = differenceY / differenceXDots; // рассчитываем допустимое отклонение от края координатной плоскости
    deviation = deviation * (deviation > 0 ? 1 : -1);
    double cpYe_dev = cpYe + (deviation * 1.2); // Допустимая точка отклонения по верхнему краю
    double cpY_dev  = cpY  - (deviation * 1.2); // Допустимая точка отклонения по нижнему  краю

    double differenceXStep  = differenceX / differenceXDots;

    double currX1 = 0;
    double currY1 = 0;
    bool successfullyCorrect = false;

    for(int i=0; i <= differenceXDots; i++) {
        currX1 = X1 - i * differenceXStep;
        currY1 = calculateYValue(exp, currX1);

        if(
            (cpYe <= currY1 && currY1 <= cpYe_dev) || // по нижнему пределу
            (cpY  >= currY1 && currY1 >= cpY_dev)     // по верхнему пределу
          ) {
            successfullyCorrect = true;
            break;
        }
    }

    if(successfullyCorrect) {
        X1 = currX1;
        Y1 = currY1;
    }

    newCoord[0] = X0;
    newCoord[1] = Y0;
    newCoord[2] = X1;
    newCoord[3] = Y1;

    if(this->debug)  std::cout << "на { "<<X0<<", "<<Y0<<", "<<X1<<",  "<<Y1<<"};\n";

    return newCoord;
}


void Graphics::Show() {
    this->refillCoordArrays();
    this->ShowLines();
    ui->graphicsView->setScene( this->scene );
}
