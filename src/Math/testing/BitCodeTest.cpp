#include "testing-prototype.h"

#include "Math/Dense.h"
#include "Math/BitCode.h"

#include <iostream>
#include <math.h>

using namespace uLib;

int main() {
    BEGIN_TESTING(BitCode Test);

    BitCode<uint,1,2> bc;

    bc.PrintSelf();

    END_TESTING;
}
