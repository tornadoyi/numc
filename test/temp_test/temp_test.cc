#include <stdio.h>
#include <iostream>
#include "numc.h"
#include "../../eigen-git-mirror/Eigen/Eigen"

using namespace std;

using namespace numc;


int main()
{
    Shape s0(3, 4, 5);

    cout << s0 << endl;

    cout << s0.size() << endl;


    return 0;
}