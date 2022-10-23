//// g++ fresnel.cpp -o t -I/usr/include/python3.8 -lpython3.8
#include <iostream>
#include <vector>
#include <math.h>
#include <tuple>

#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

std::tuple<std::vector<float>, std::vector<float>, std::vector<float>, std::vector<float>> fermatSpiral()
{

    float a = 1;
    float fi = M_PI_4/3;
    float dt = 0.001;
    int size = 100; // number of iterations - length of spiral

    std::vector<float> xX;
    std::vector<float> yY;
    std::vector<float> _xX;
    std::vector<float> _yY;

    for (int ii = 0; ii < size; ii++)
    {

        float xXi = (a * std::sqrt(fi * ii)) * std::cos(fi * ii);
        float yYi = (a * std::sqrt(fi * ii)) * std::sin(fi * ii);

        float _xXi = -(a * std::sqrt(fi * ii)) * std::cos(fi * ii);
        float _yYi = -(a * std::sqrt(fi * ii)) * std::sin(fi * ii);


        xX.push_back(xXi);
        yY.push_back(yYi);
        _xX.push_back(_xXi);
        _yY.push_back(_yYi);
    
    
    }
    return std::make_tuple(xX, yY, _xX, _yY);
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



void plot2x2D(std::tuple<std::vector<float>, std::vector<float>> data1, std::tuple<std::vector<float>, std::vector<float>> data2)
{

    std::vector<float> xX1 = std::get<0>(data1);
    std::vector<float> yY1 = std::get<1>(data1);
   
    std::vector<float> xX2 = std::get<0>(data2);
    std::vector<float> yY2 = std::get<1>(data2);

    plt::plot(xX1, yY1);
    plt::plot(xX2, yY2);
    plt::xlabel("x");
    plt::ylabel("y");
    plt::show();
}

int main()
{

    std::tuple<std::vector<float>, std::vector<float>, std::vector<float>, std::vector<float>> spiralXY;
    
    spiralXY = fermatSpiral();
    
    std::tuple<std::vector<float>, std::vector<float>> spiral1 = {std::get<0>(spiralXY), std::get<1>(spiralXY)};
    std::tuple<std::vector<float>, std::vector<float>> spiral2 = {std::get<2>(spiralXY), std::get<3>(spiralXY)};

    plot2x2D(spiral1, spiral2);
}