#include <stdio.h>
#include <iostream>
#include "numc.h"
#include "../../eigen-git-mirror/Eigen/Eigen"
//#include "test.h"

using namespace std;

using namespace numc;

//using namespace Eigen;



int main()
{
    Array<float> a(2, 2);
    Array<float> b(2, 2);
    Array<float> c(2, 2);
    auto op = a + b;

    auto op2 = op + c;



    return 0;
}