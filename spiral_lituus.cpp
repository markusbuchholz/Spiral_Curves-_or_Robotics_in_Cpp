
//// g++ fresnel.cpp -o t -I/usr/include/python3.8 -lpython3.8
#include <iostream>
#include <vector>
#include <math.h>
#include <tuple>

#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

std::tuple<std::vector<float>, std::vector<float>> lituusSpiral()
{

    float a = 1.5;
    float fi = M_PI_4/3;
    float dt = 0.0001;
    int size = 1000; // number of iterations - length of spiral

    std::vector<float> xX;
    std::vector<float> yY;


    for (int ii = 0; ii < size; ii++)
    {

        float xXi = (a * std::sqrt(a/(fi * ii))) * std::cos(fi * ii);
        float yYi = (a * std::sqrt(a/(fi * ii))) * std::sin(fi * ii);

        xX.push_back(xXi);
        yY.push_back(yYi);
    }
    return std::make_tuple(xX, yY);
}

//---------------------------------------------------------------

void plot2D(std::tuple<std::vector<float>, std::vector<float>> data1)
{

    std::vector<float> xX1 = std::get<0>(data1);
    std::vector<float> yY1 = std::get<1>(data1);

    plt::plot(xX1, yY1);
    plt::xlabel("x");
    plt::ylabel("y");
    plt::show();
}

//---------------------------------------------------------------

int main()
{

    std::tuple<std::vector<float>, std::vector<float>> spiralXY;
    spiralXY = lituusSpiral();

    plot2D(spiralXY);
}