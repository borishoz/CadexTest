#include <iostream>

#include "cadextest.h"

#define ERR Err()<<"( ERROR from -> "<<__PRETTY_FUNCTION__<<", line "<< __LINE__<<" ) "

CadexTest::CadexTest() :  _double_range(-1*_PARAM_RANGE, _PARAM_RANGE) {
    std::random_device device;
    _random_generator.seed(device());
}

void CadexTest::Run() {
    if(!_GenerateVector())
        return;

    PrintCurves( std::numbers::pi/4);

    _GenerateList();
    _SortList();
    Prn()<<std::endl<<"RadiiSum: "<<GetRadiiSum()<<" <> "<<_radiiSum;
}

void CadexTest::PrintCurves( double t) {
    Prn()<<std::endl<<"Curves parameters at "<<t<<" radians.";
    for( const auto& curve: _curvesVector) {
        Prn()<<std::endl<<curve->StrCurveParams();
        Prn()<<curve->StrCurve3dPoint(t);
        Prn()<<curve->StrCurve3dDerivative(t);
    }
}

double CadexTest::GetRadiiSum() {
    _radiiSum++; //now the fastest computation
    double radiiSum=0;
    for( const auto& circle: _circleList)
       radiiSum += circle->GetRadius();
    return radiiSum;
}

bool CadexTest::_GenerateVector() {
    uint32_t vectorSize = _GetRandomSize();
    _curvesVector.resize( vectorSize);
    if(_curvesVector.size()!=vectorSize) {
        ERR << "Can't allocate vector size " << vectorSize;
        return false;
    }
    Prn()<<"Random size of the vector: " << vectorSize;

    int32_t currentNonCircleIndex = vectorSize;
    _currentCircleIndex = -1;

    std::shared_ptr<Curve> tmpPtr;
    int ellipseCounter = 0;
    for( uint32_t i=0, j=0; i<vectorSize && j<(vectorSize*10); j++) {
        bool ok = false;
        uint32_t type = _GetRandomType();
        switch(type) {
            case 0:
                tmpPtr = std::make_shared<Circle>( _GetRandomParam(), ok);
                if(ok) {
                    _currentCircleIndex++;
                    _curvesVector[_currentCircleIndex] = tmpPtr;
                    i++;
                }
                break;
            case 1:
            case 2:
               if( type==1)
                    tmpPtr = std::make_shared<Ellipse>( _GetRandomParam(), _GetRandomParam(), ok);
                else
                    tmpPtr = std::make_shared<Helixe>( _GetRandomParam(), _GetRandomParam(), ok);
                if(ok) {
                    currentNonCircleIndex--;
                    _curvesVector[currentNonCircleIndex] = tmpPtr;
                    if( type==1)
                        ellipseCounter++;
                    i++;
                 }
                break;
            default:
                ERR << "Curve type error.";
                return false;
        }
        if(tmpPtr==nullptr) {
            ERR << "Create new Curve error.";
            return false;
        }
    }
    Prn()<<"The vector is OK. Circles:"<< currentNonCircleIndex<<" Ellipses:"<<ellipseCounter
            <<" Helixes:"<<(vectorSize-currentNonCircleIndex-ellipseCounter);
    return true;
}

void CadexTest::_GenerateList() {
    //In case of memory deficite we can free the part of the Curves vector
    //_curvesVector.resize(_currentCircleIndex);

    for(int i=0; i<=_currentCircleIndex; i++) {
//        std::shared_ptr<Curve> ptr0 = _curvesVector[i];
        std::shared_ptr<Circle> ptr = std::dynamic_pointer_cast<Circle>(_curvesVector[i]);
        if(ptr) {
            _circleList.push_back(ptr);
            _radiiSum += ptr->GetRadius();
        }
        else
            ERR << "Can't cast to Circle.";
    }
}

void CadexTest::_SortList(){
    _circleList.sort([]( const std::shared_ptr<Circle>& c1, const std::shared_ptr<Circle>& c2 )
            { return c1->GetRadius() < c2->GetRadius();}
    );
}
