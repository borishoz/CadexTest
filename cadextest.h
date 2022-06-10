#ifndef CADEXTEST_H
#define CADEXTEST_H

#include <random>
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <list>

#include "curves.h"

class CadexTest
{
public:
    CadexTest();
    virtual ~CadexTest() { Prn(); Err();}

    void Run();
    void PrintCurves( double t);
    double GetRadiiSum();

    std::ostream& Prn() {return std::cout << std::endl;}
    std::ostream& Err() {return std::cerr << std::endl;}

private:
    std::mt19937 _random_generator;

    std::vector<std::shared_ptr<Curve>> _curvesVector;
    bool _GenerateVector();

    std::list<std::shared_ptr<Circle>> _circleList;
    void _GenerateList();
    void _SortList();

    int32_t _currentCircleIndex = 0;

    double _radiiSum = -1.0;

    const uint32_t _MAX_CURVE_TYPE = 3;

    const uint32_t _MAX_VECTOR_SIZE = 100;

    const double _PARAM_RANGE = 100;
    std::uniform_real_distribution<> _double_range;

    uint32_t _GetRandomSize() {
      std::uniform_int_distribution<uint32_t> range(1, _MAX_VECTOR_SIZE);
      return range(_random_generator);
    }

    uint32_t _GetRandomType() {
      std::uniform_int_distribution<uint32_t> range(0, _MAX_CURVE_TYPE-1);
      return range(_random_generator);
    }

    double _GetRandomParam() { return _double_range(_random_generator);}

};

#endif // CADEXTEST_H
