#pragma once
#include <random>
//#include <time.h>

namespace MyFunc {
 
float GetRandomNumber(std::default_random_engine &e,int i1, int i2);
#define INIT_RANDOM_ENGINE std::default_random_engine e(time(0))
#define rn(a,b) GetRandomNumber(e,a,b)
}

#define NS_MF namespace mf = MyFunc