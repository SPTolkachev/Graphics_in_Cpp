//#include "coordplane.h"
#include "graphics.h"
#include "../../libs/parsemathex/parsemathex.h"
#include <iostream>
#include <math.h>

Graphics::Graphics(Ui::MainWindow *ui, CoordPlane *cp, QGraphicsScene *scene) {
    this->ui = ui;
    this->cp = cp;
    this->scene  = scene;//this->cp->GetScene();//new QGraphicsScene(ui->graphicsView);
    this->canvas = this->ui->graphicsView->viewport();
    this->debug  = this->ui->DebugFlag->isChecked();
    //std::cout << "this->debug = " << (this->debug ? "true" : "false") << " " << (this->ui->DebugFlag->isChecked() ? "true" : "false") << "\n";
    this->toDefaultCoordArrays();
    //this->Show();
}

bool Graphics::GetDebug() {
    return this->debug;
}

void Graphics::SetDebug(bool debug) {
    this->debug = debug;
}


double Graphics::calculateYValue(std::string exp, double X) {
    double result = 0;
    //exp = "sin($x * $x)";

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

    if(openParenthesis == closeParenthesis) {
        std::string expression = "$x = " + std::to_string(X) + "; " + exp;

        char * charexpression = new char [expression.length()+1];
        strcpy (charexpression, expression.c_str());

        std::cout << expression << " = " << result << "\n";
        result = ParserMathExpression(charexpression);
    }

    return result;//X * X;
}





void Graphics::toDefaultCoordArrays() {
    int dots = this->GetDots();
    for(int i=0; i < dots; i++) {
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
    return this->dots;
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
    if(this->debug) std::cout << "X:\n";
    std::string exp = "sin($x)";
    for(int i=0; i < dots; i++) {
        double x1 = X + i * step;
        double y1 = this->calculateYValue(exp, x1);

        double cnv_x1 = (x1 - X)  / X_PsiP;
        double cnv_y1 = (-y1 + Y) / Y_PsiP;

        if(i) { // Проверка
            double x0 = this->arrayXCoords[i-1];
            double y0 = this->arrayYCoords[i-1];
            std::cout << "x0["<<i-1<<"] = " << x0 << "; y0["<<i-1<<"] = "<<y0<<"\n";

            //double cnv_x0 = this->arrayCanvasXCoords[i-1];
            //double cnv_y0 = this->arrayCanvasYCoords[i-1];

            if(this->debug) std::cout << "\n";
            bool condition_x0 = (x0 >= X && x0 <= Xe) ? true : false;
            if(this->debug) std::cout << "condition_x0 = ("<<x0<<" >= "<<X<<" && "<<x0<<" <= "<<Xe<<") = "<< (condition_x0 ? "true" : "false") <<";   ";
            bool condition_x1 = (x1 >= X && x1 <= Xe) ? true : false;
            if(this->debug) std::cout << "condition_x1 = ("<<x1<<" >= "<<X<<" && "<<x1<<" <= "<<Xe<<") = "<< (condition_x1 ? "true" : "false") <<";\n";
            bool condition_y0 = (y0 <= Y && y0 >= Ye);
            if(this->debug) std::cout << "condition_y0 = ("<<y0<<" <= "<<Y<<" && "<<y0<<" >= "<<Ye<<") = "<< (condition_y0 ? "true" : "false") <<";   ";
            bool condition_y1 = (y1 <= Y && y1 >= Ye);
            if(this->debug) std::cout << "condition_y1 = ("<<y1<<" <= "<<Y<<" && "<<y1<<" >= "<<Ye<<") = "<< (condition_y1 ? "true" : "false") <<";\n";

            /*
            if(this->debug) std::cout << (condition_x0 ? "true" : "false") << " ";
            if(this->debug) std::cout << (condition_y0 ? "true" : "false") << " ";
            if(this->debug) std::cout << (condition_x1 ? "true" : "false") << " ";
            if(this->debug) std::cout << (condition_y1 ? "true" : "false") << "\n\n";
            */

            int action = 0;
            action += condition_x0 ? 1000 : 0;
            action += condition_y0 ?  100 : 0;
            action += condition_x1 ?   10 : 0;
            action += condition_y1 ?    1 : 0;
            double *correctDot;

            switch (action) { // Корректировка
                case 1011: // Y0 не попал в диапазон
                    std::cout << "Пограничная ситуация (Y0) this->scene->addLine("<<x0<<", "<<y0<<",  "<<x1<<", "<<y1<<",  pen);\n";
                    correctDot = this->CorrectY0(exp, x0, y0, x1, y1);
                    this->arrayXCoords[i-1] = correctDot[0];
                    this->arrayYCoords[i-1] = correctDot[1];
                    this->arrayCanvasXCoords[i-1] = ( correctDot[0] - X)  / X_PsiP;
                    this->arrayCanvasYCoords[i-1] = (-correctDot[1] + Y)  / Y_PsiP;
                    break;
                case 1110: // Y1 не попал в диапазон
                    std::cout << "Пограничная ситуация (Y1) this->scene->addLine("<<x0<<", "<<y0<<",  "<<x1<<", "<<y1<<",  pen);\n";
                    correctDot = this->CorrectY1(exp, x0, y0, x1, y1);
                    if(correctDot[0] != correctDot[2] && correctDot[1] != correctDot[3]) {
                        x1     = correctDot[2];
                        y1     = correctDot[3];
                        cnv_x1 = ( correctDot[2] - X) / X_PsiP;
                        cnv_y1 = (-correctDot[3] + Y) / Y_PsiP;
                    }
                    break;
                default:
                std::cout << "Добавляем this->scene->addLine("<<x0<<", "<<y0<<", "<<x1<<", "<<y1<<", pen);\n";
            }
        }

        this->arrayXCoords[i] = x1;
        this->arrayYCoords[i] = y1;
        // if(this->debug) std::cout <<"    this->arrayXCoords["<< i <<"] = " << this->arrayXCoords[i] << ";    this->arrayYCoords["<< i <<"] = " << this->arrayYCoords[i] << ";\n";

        this->arrayCanvasXCoords[i] = cnv_x1;
        this->arrayCanvasYCoords[i] = cnv_y1;
    }
    if(this->debug) std::cout << "\n";

    /*
    for(int i=0; i < dots; i++) {
        std::cout << "this->arrayXCoords["<<i<<"] = "<<this->arrayXCoords[i]<<";   this->arrayYCoords["<<i<<"] = "<<this->arrayYCoords[i]<<";\n";
    }
    */
}



void Graphics::ShowLines() {
    int dots  = this->GetDots();
    double X  = this->cp->GetX();
    double Y  = this->cp->GetY();
    double Xe = this->cp->GetXe();
    double Ye = this->cp->GetYe();
    QPen pen(QColor(0, 225, 0));

    //double X_PsiP = this->cp->GetX_PsiP();
    //double Y_PsiP = this->cp->GetY_PsiP();
    std::cout <<"*****\n";
    for(int i=0; i < dots; i++) {
        if(i) {
            double x0 = this->arrayXCoords[i-1];
            double y0 = this->arrayYCoords[i-1];
            double x1 = this->arrayXCoords[i];
            double y1 = this->arrayYCoords[i];

            double cnv_x0 = this->arrayCanvasXCoords[i-1];
            double cnv_y0 = this->arrayCanvasYCoords[i-1];
            double cnv_x1 = this->arrayCanvasXCoords[i];
            double cnv_y1 = this->arrayCanvasYCoords[i];

            //if(this->debug) std::cout << "\n";
            bool condition_x0 = (x0 >= X && x0 <= Xe) ? true : false;
            //if(this->debug) std::cout << "condition_x0 = ("<<x0<<" >= "<<X<<" && "<<x0<<" <= "<<Xe<<") = "<< (condition_x0 ? "true" : "false") <<";   ";
            bool condition_x1 = (x1 >= X && x1 <= Xe) ? true : false;
            //if(this->debug) std::cout << "condition_x1 = ("<<x1<<" >= "<<X<<" && "<<x1<<" <= "<<Xe<<") = "<< (condition_x1 ? "true" : "false") <<";\n";
            bool condition_y0 = (y0 <= Y && y0 >= Ye);
            //if(this->debug) std::cout << "condition_y0 = ("<<y0<<" <= "<<Y<<" && "<<y0<<" >= "<<Ye<<") = "<< (condition_y0 ? "true" : "false") <<";   ";
            bool condition_y1 = (y1 <= Y && y1 >= Ye);
            //if(this->debug) std::cout << "condition_y1 = ("<<y1<<" <= "<<Y<<" && "<<y1<<" >= "<<Ye<<") = "<< (condition_y1 ? "true" : "false") <<";\n";

            /*
            if(this->debug) std::cout << (condition_x0 ? "true" : "false") << " ";
            if(this->debug) std::cout << (condition_y0 ? "true" : "false") << " ";
            if(this->debug) std::cout << (condition_x1 ? "true" : "false") << " ";
            if(this->debug) std::cout << (condition_y1 ? "true" : "false") << "\n\n";
            */
            int action = 0;
            action += condition_x0 ? 1000 : 0;
            action += condition_y0 ?  100 : 0;
            action += condition_x1 ?   10 : 0;
            action += condition_y1 ?    1 : 0;

            if(condition_x0 && condition_y0 && condition_x1 && condition_y1) {
                this->scene->addLine(cnv_x0, cnv_y0,  cnv_x1, cnv_y1,  pen);
                std::cout << "Добавляем this->scene->addLine("<<x0<<", "<<y0<<", "<<x1<<", "<<y1<<", pen);\n";
            }
            else {
                std::cout << "Пропускаем this->scene->addLine("<<x0<<", "<<y0<<", "<<x1<<", "<<y1<<", pen);\n";
            }

            /*
            double *correctDot;
            switch (action) {
            case 1111:
                this->scene->addLine(cnv_x0, cnv_y0,  cnv_x1, cnv_y1,  pen);
                //* if(this->debug) * / std::cout << "this->scene->addLine("<<cnv_x0<<", "<<cnv_y0<<", "<<cnv_x1<<", "<<cnv_y1<<", pen);\n";
                std::cout << "this->scene->addLine("<<x0<<", "<<y0<<", "<<x1<<", "<<y1<<", pen);\n";
                break;
            // *
            case 1110: // Y1 не попал в диапазон
                // * if(this->debug) * / std::cout << "Пограничная ситуация this->scene->addLine("<<cnv_x0<<", "<<cnv_y0<<",  "<<cnv_x1<<", "<<cnv_y1<<",  pen);\n";
                std::cout << "Пограничная ситуация (Y1) this->scene->addLine("<<x0<<", "<<y0<<",  "<<x1<<", "<<y1<<",  pen);\n";
                correctDot = this->CorrectY1(x0, y0, x1, y1);
                cnv_x1 = (correctDot[2] - X) / X_PsiP;
                cnv_y1 = (-correctDot[3] + Y) / Y_PsiP;
                this->scene->addLine(cnv_x0, cnv_y0,  cnv_x1, cnv_y1,  pen);
                break;
            case 1101: // X1 не попал в диапазон
                // * if(this->debug) * / std::cout << "Пограничная ситуация this->scene->addLine("<<cnv_x0<<", "<<cnv_y0<<",  "<<cnv_x1<<", "<<cnv_y1<<",  pen);\n";
                std::cout << "Пограничная ситуация this->scene->addLine("<<x0<<", "<<y0<<",  "<<x1<<", "<<y1<<",  pen);\n";
                break;
            case 1011: // Y0 не попал в диапазон
                // * if(this->debug) * / std::cout << "Пограничная ситуация this->scene->addLine("<<cnv_x0<<", "<<cnv_y0<<",  "<<cnv_x1<<", "<<cnv_y1<<",  pen);\n";
                std::cout << "Пограничная ситуация (Y0) this->scene->addLine("<<x0<<", "<<y0<<",  "<<x1<<", "<<y1<<",  pen);\n";
                correctDot = this->CorrectY0(x0, y0, x1, y1);
                cnv_x0 = (correctDot[0] - X)  / X_PsiP;
                cnv_y0 = (-correctDot[1] + Y)  / Y_PsiP;
                this->scene->addLine(cnv_x0, cnv_y0,  cnv_x1, cnv_y1,  pen);
                //std::cout << ;
                break;
            case 111: // X0 не попал в диапазон
                // * if(this->debug) * / std::cout << "Пограничная ситуация this->scene->addLine("<<cnv_x0<<", "<<cnv_y0<<",  "<<cnv_x1<<", "<<cnv_y1<<",  pen);\n";
                std::cout << "Пограничная ситуация this->scene->addLine("<<x0<<", "<<y0<<",  "<<x1<<", "<<y1<<",  pen);\n";
                break;
            // * /
            default:
                // * if(this->debug) * / std::cout << "Пропускаем this->scene->addLine("<<cnv_x0<<", "<<cnv_y0<<",  "<<cnv_x1<<", "<<cnv_y1<<",  pen);\n";
                std::cout << "Пропускаем this->scene->addLine("<<x0<<", "<<y0<<",  "<<x1<<", "<<y1<<",  pen);\n";
                break;
            }
            */

            /*
            if(condition_x0 && condition_y0 && condition_x1 && condition_y1) {
                this->scene->addLine(cnv_x0, cnv_y0,  cnv_x1, cnv_y1,  pen);
                if(this->debug) std::cout << "this->scene->addLine("<<cnv_x0<<", "<<cnv_y0<<", "<<cnv_x1<<", "<<cnv_y1<<", pen);\n";
            }
            */
        }
    }
}




double *Graphics::CorrectY0(std::string exp, double X0, double Y0, double X1, double Y1) {
    double  cpY  = this->cp->GetY();
    double  cpYe = this->cp->GetYe();
    double *newCoord = new double[4];

    double differenceY = Y0 - Y1;
    double differenceX = X1 - X0;
    int    differenceXDots  = 20;

    double deviation  = differenceY / differenceXDots; // рассчитываем допустимое отклонение от края координатной плоскости
    deviation = deviation * (deviation > 0 ? 1 : -1);
    double cpY_dev  = cpY  - (deviation * 1.2); // Допустимая точка отклонения по верхнему краю
    double cpYe_dev = cpYe + (deviation * 1.2); // Допустимая точка отклонения по нижнему  краю

    //int    differenceXSteps = differenceXDots - 1;
    double differenceXStep  = differenceX / differenceXDots;

    double currX0 = 0;
    double currY0 = 0;
    bool successfullyCorrect = false;

    for(int i=0; i <= differenceXDots; i++) {
        currX0 = X0 + i * differenceXStep;
        // currX1 = X1 - i * differenceXStep;
        currY0 = calculateYValue(exp, currX0);

        std::cout << cpYe<<" <= "<<currY0<<" && "<<currY0<<" <= "<<cpYe_dev<<" || ";
        std::cout << cpY<<" >= "<<currY0<<" && "<<currY0<<" >= "<<cpY_dev<<"\n";

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

    std::cout << "на { "<<X0<<", "<<Y0<<", "<<X1<<",  "<<Y1<<"};\n";
    newCoord[0] = X0;
    newCoord[1] = Y0;
    newCoord[2] = X1;
    newCoord[3] = Y1;

    //{ X0, Y0, X1, Y1 };

    return newCoord;
}

double *Graphics::CorrectY1(std::string exp, double X0, double Y0, double X1, double Y1) {
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

    //int    differenceXSteps = differenceXDots - 1;
    double differenceXStep  = differenceX / differenceXDots;

    double currX1 = 0;
    double currY1 = 0;
    //double delta  = 0;
    //double d_X    = X1;
    //double d_Y    = calculateYValue(currX1);
    bool successfullyCorrect = false;
    for(int i=0; i <= differenceXDots; i++) {
        currX1 = X1 - i * differenceXStep;
        currY1 = calculateYValue(exp, currX1);
        std::cout << cpYe<<" <= "<<currY1<<" && "<<currY1<<" <= "<<cpYe_dev<<" || ";
        std::cout << cpY<<" >= "<<currY1<<" && "<<currY1<<" >= "<<cpY_dev<<"\n";
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

    std::cout << "на { "<<X0<<", "<<Y0<<", "<<X1<<",  "<<Y1<<"};\n";
    newCoord[0] = X0;
    newCoord[1] = Y0;
    newCoord[2] = X1;
    newCoord[3] = Y1;

    //{ X0, Y0, X1, Y1 };

    return newCoord;
}



double *Graphics::CorrectDot(double X0, double Y0, double X1, double Y1) {
    double cpX  = this->cp->GetX();
    double cpY  = this->cp->GetY();
    double cpXe = this->cp->GetXe();
    double cpYe = this->cp->GetYe();
    double* newCoord = new double[4];

    std::cout << "Переопределение координат с { "<<X0<<", "<<Y0<<", "<<X1<<",  "<<Y1<<"} ";

    /*
    int action = 0;
    action += condition_x0 ? 1000 : 0;
    action += condition_y0 ?  100 : 0;
    action += condition_x1 ?   10 : 0;
    action += condition_y1 ?    1 : 0;
    */
    bool condition_x0 = (X0 >= cpX && X0 <= cpXe);
    bool condition_x1 = (X1 >= cpX && X1 <= cpXe);
    bool condition_y0 = (Y0 <= cpY && Y0 >= cpYe);
    bool condition_y1 = (Y1 <= cpY && Y1 >= cpYe);
    int limit = 10;

    int  correctDot  = condition_x1 && condition_y1 ? 0 : 1; // 0 -- first,  1 -- second
    bool by_x  = !(condition_x0 && condition_x1);
    bool by_y  = !(condition_y0 && condition_y1);

    double deviation  = 0;
    double differenceX = 0;
    double differenceY = 0;
    if( !correctDot ) {
        std::cout << "!correctDot ";
        if(by_x && by_y) { // by both dots

        }
        else { // only one dot
            std::cout << " :: only one dot :: ";
            /*
            if(by_x) {
                std::cout << "by_x ****\n";
                difference = X1 - X0;
                deviation  = difference / 10;
                double cpX_dev = cpX + deviation;
                difference /= 2;
                double new_X0 = cpX + difference;
                int limit = 10;
                do {
                    if( new_X0 < cpX ) {
                        difference *= 1.5;
                    }
                    else {
                        difference *= 0.5;
                    }
                    limit--;
                } while( !(cpX <= new_X0 && new_X0 >= cpX_dev) && (limit > 0) );
                X0 = new_X0;
                Y0 = calculateYValue(X0);
            }
            */
            if(by_y) {
                std::cout << "by_y ****\n";

                // Надо заходить через X!!!!!!!!!!!!
                /*
                differenceX = X1 - X0; // длина проблемного участка
                differenceY = Y0 - Y1;
                //std::cout << "difference = "<<Y0<<" - "<<Y1<<";\n";
                deviation  = differenceY / 10; // рассчитываем допустимое отклонение от края координатной плоскости
                double cpY_dev = cpY - deviation; // Допустимая точка отклонения
                std::cout << "cpY_dev = "<<cpY<<" - "<<deviation<<";\n";
                differenceX /= 2;
                double new_Y0;
                int limit = 10;
                do {
                    new_Y0 = calculateYValue(cpX + differenceX);
                    if( new_Y0 < cpY ) {
                        differenceX *= 1.5;
                    }
                    else {
                        differenceX *= 0.5;
                    }
                    limit--;
                    std::cout << cpY<<" <= "<<new_Y0<<" && "<<new_Y0<<" >= "<<cpY_dev<<" \n";
                } while( !(cpY >= new_Y0 && new_Y0 <= cpY_dev) && (limit > 0) );
                X0 = new_Y0;
                Y0 = calculateYValue(X0);
                */
                differenceY = Y0 - Y1;
                differenceX = X1 - X0;
                int    differenceXDots  = 10;
                deviation  = differenceY / differenceXDots; // рассчитываем допустимое отклонение от края координатной плоскости
                double cpY_dev = cpY - deviation; // Допустимая точка отклонения

                int    differenceXSteps = differenceXDots - 1;
                double differenceXStep  = differenceX / differenceXSteps;

                double currX0 = 0;
                double currY0 = 0;
                bool succssesfullDot = false;
                for(int i=0; i < differenceXSteps; i++) {
                    currX0 = X0 + i * differenceXStep;
                    currY0 = calculateYValue("$x", currX0);
                    if(cpY >= currY0 && currY0 <= cpY_dev) {
                        succssesfullDot = true;
                        break;
                    }
                }

                if(succssesfullDot) {
                    X0 = currX0;
                    Y0 = currY0;
                }
            }
        }
    }
    else {

    }

    /*
    do {
        if( !condition_x0 ) {
            X0 = cpX;
            Y0 = calculateYValue(X0);
        }
        if( !condition_y0 ) {
            X0 = (X0 + X1) / 2;
            Y0 = calculateYValue(X0);
        }

        if( !condition_x1 ) {
            X1 = cpXe;
            Y1 = calculateYValue(X1);
        }
        if( !condition_y1 ) {
            X1 = (X0 + X1) / 2;
            Y1 = calculateYValue(X1);
        }

        condition_x0 = (X0 >= cpX && X0 <= cpXe);
        condition_x1 = (X1 >= cpX && X1 <= cpXe);
        condition_y0 = (Y0 <= cpY && Y0 >= cpYe);
        condition_y1 = (Y1 <= cpY && Y1 >= cpYe);
        limit--;
    } while( (!condition_x0 || !condition_y0 || !condition_x1 || !condition_y1)  && limit > 0);
    */

    std::cout << "на { "<<X0<<", "<<Y0<<", "<<X1<<",  "<<Y1<<"};\n";
    newCoord[0] = X0;
    newCoord[1] = Y0;
    newCoord[2] = X1;
    newCoord[3] = Y1;

    //{ X0, Y0, X1, Y1 };

    return newCoord;
}

/*
void Graphics::clearScene() {
    this->scene = new QGraphicsScene(ui->graphicsView);
}
*/

void Graphics::Show() {
    //this->clearScene();

    this->refillCoordArrays();
    this->ShowLines();
    //ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    ui->graphicsView->setScene( this->scene );
    //this->scene = new QGraphicsScene(ui->graphicsView);
    //this->cp->SetScene();
}
