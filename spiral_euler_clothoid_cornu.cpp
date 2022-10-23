
//// g++ fresnel.cpp -o t -I/usr/include/python3.8 -lpython3.8
#include <iostream>
#include <vector>
#include <math.h>
#include <tuple>

#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

//---------------------------------------------------------------

double L = 60; // length of curve
double R = 4.999706667;
int lambda = 1;
float A = std::sqrt(R * L);


//---------------------------------------------------------------

double funCos(double tt)
{

    return std::cos(lambda * tt * tt / (2 * A * A));
}

//---------------------------------------------------------------

double funSin(double tt)
{

    return std::sin(lambda * tt * tt / (2 * A * A));
}
//---------------------------------------------------------------

std::tuple<std::vector<double>, std::vector<double>> trapezoidRuleClothoid()

{
    int N = 1 << 15; // number of iterations
    float aa{0};
    float bb{100};
    float h = (bb - aa) / N;

    std::vector<double> outCos;
    double aAc = funCos(aa) * 0.5;
    double bBc = funCos(bb) * 0.5;

    std::vector<double> outSin;
    double aAs = funSin(aa) * 0.5;
    double bBs = funSin(bb) * 0.5;

    double sumC{0};
    double sumS{0};

    for (int ii = -N; ii < N; ii++)
    {

        sumC += funCos(aa + ii * h);
        sumS += funSin(aa + ii * h);

        outCos.push_back(1.5 * h * (aAc + bBc + sumC)); //scale 1.5
        outSin.push_back(1.5 * h * (aAs + bBs + sumS)); //scale 1.5
    }
    return std::make_tuple(outCos, outSin);
}

//---------------------------------------------------------------

std::tuple<std::vector<double>, std::vector<double>> simpsonRuleClothoid()

{
    int N = 1 << 15; // number of iterations
    float aa{0};
    float bb{100};
    float h = (bb - aa) / N;

    std::vector<double> outCos;
    double aAc = funCos(aa) * 0.5;
    double bBc = funCos(bb) * 0.5;

    std::vector<double> outSin;
    double aAs = funSin(aa) * 0.5;
    double bBs = funSin(bb) * 0.5;

    double sumC2{0};
    double sumS2{0};
    double sumC4{0};
    double sumS4{0};

    for (int ii = 1; ii < N; ii++)
    {

        sumC4 += funCos(aa + ii * h + 0.5 * h);
        sumS4 += funSin(aa + ii * h + 0.5 * h);

        sumC2 += funCos(aa + ii * h);
        sumS2 += funSin(aa + ii * h);

        outCos.push_back(h/6 * (aAc + bBc + 2 * sumC2 + 4 * sumC4 ));
        outSin.push_back(h/6 * (aAs + bBs + 2 * sumS2 + 4 * sumS4 ));


    }
    return std::make_tuple(outCos, outSin);
}

//---------------------------------------------------------------

void plot2D(std::tuple<std::vector<double>, std::vector<double>> data1)
{

    std::vector<double> xX1 = std::get<0>(data1);
    std::vector<double> yY1 = std::get<1>(data1);
   
    plt::plot(xX1, yY1);
    plt::xlabel("x");
    plt::ylabel("y");
    plt::show();
}

//---------------------------------------------------------------

int main()
{

    std::tuple<std::vector<double>, std::vector<double>> clothoid1;
    std::tuple<std::vector<double>, std::vector<double>> clothoid2;
    clothoid1 = trapezoidRuleClothoid();
    clothoid2 = simpsonRuleClothoid();
    plot2D(clothoid1);


}