
//// g++ fresnel.cpp -o t -I/usr/include/python3.8 -lpython3.8
#include <iostream>
#include <vector>
#include <math.h>
#include <tuple>

#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

//---------------------------------------------------------------

float L = 60; // length of curve
float R = 4.999706667;
int lambda = 1;
float A = std::sqrt(R * L);

//---------------------------------------------------------------

float funCos(float tt)
{

    return std::cos(lambda * tt * tt / (2 * A * A));
}

//---------------------------------------------------------------

float funSin(float tt)
{

    return std::sin(lambda * tt * tt / (2 * A * A));
}
//---------------------------------------------------------------

std::tuple<std::vector<float>, std::vector<float>> trapezoidRuleClothoid()

{
    int N = 1 << 15; // number of iterations
    float aa{0};
    float bb{100};
    float h = (bb - aa) / N;

    std::vector<float> outCos;
    float aAc = funCos(aa) * 0.5;
    float bBc = funCos(bb) * 0.5;

    std::vector<float> outSin;
    float aAs = funSin(aa) * 0.5;
    float bBs = funSin(bb) * 0.5;

    float sumC{0};
    float sumS{0};

    for (int ii = -N; ii < N; ii++)
    {

        sumC += funCos(aa + ii * h);
        sumS += funSin(aa + ii * h);

        outCos.push_back(1.5 * h * (aAc + bBc + sumC)); // scale 1.5
        outSin.push_back(1.5 * h * (aAs + bBs + sumS)); // scale 1.5
    }
    return std::make_tuple(outCos, outSin);
}

//---------------------------------------------------------------

std::tuple<std::vector<float>, std::vector<float>> simpsonRuleClothoid()

{
    int N = 1 << 15; // number of iterations
    float aa{0};
    float bb{100};
    float h = (bb - aa) / N;

    std::vector<float> outCos;
    float aAc = funCos(aa) * 0.5;
    float bBc = funCos(bb) * 0.5;

    std::vector<float> outSin;
    float aAs = funSin(aa) * 0.5;
    float bBs = funSin(bb) * 0.5;

    float sumC2{0};
    float sumS2{0};
    float sumC4{0};
    float sumS4{0};

    for (int ii = 1; ii < N; ii++)
    {

        sumC4 += funCos(aa + ii * h + 0.5 * h);
        sumS4 += funSin(aa + ii * h + 0.5 * h);

        sumC2 += funCos(aa + ii * h);
        sumS2 += funSin(aa + ii * h);

        outCos.push_back(h / 6 * (aAc + bBc + 2 * sumC2 + 4 * sumC4));
        outSin.push_back(h / 6 * (aAs + bBs + 2 * sumS2 + 4 * sumS4));
    }
    return std::make_tuple(outCos, outSin);
}

//---------------------------------------------------------------

std::tuple<std::vector<float>, std::vector<float>> archimedanSpiral()
{

    float v = 0.5;
    float c = 1.0;
    float omega = M_PI_4;
    float dt = 0.001;
    int size = 1 << 15; // number of iterations - length of spiral

    std::vector<float> xX;
    std::vector<float> yY;

    for (int ii = 0; ii < size; ii++)
    {

        float xXi = (v * ii * dt + c) * std::cos(omega * (ii * dt));
        float yYi = (v * ii * dt + c) * std::sin(omega * (ii * dt));

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
    spiralXY = archimedanSpiral();

    plot2D(spiralXY);
}