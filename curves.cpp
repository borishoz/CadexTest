#include <cmath>

#include "curves.h"

char Curve::_printBuffer [_bufferSize];
const double Curve::_dt=1e-10;

char* Curve::StrCurve3dPoint( double t) {
    Point3D point3D;
    Get3dPoint( t, &point3D);
    sprintf(_printBuffer, "3D point x: %f, y: %f, z: %f", point3D.x, point3D.y, point3D.z );
    return _printBuffer;
}

char* Curve::StrCurve3dDerivative( double t) {
    Point3D point3D;
    Get3dDerivative( t, &point3D);
    sprintf(_printBuffer, "3D derivative x: %f, y: %f, z: %f", point3D.x, point3D.y, point3D.z );
    return _printBuffer;
}

void Curve::_Get3dPoint( double t, Point3D* point3D, double a, double b, double step) {
    point3D->z = step * t / (2*std::numbers::pi);
    if(a==b) { //circle
        point3D->x = a*cos( t);
        point3D->y = b*sin( t);
        return;
    }
    point3D->x = _XbyT(t, a, b);
    point3D->y = _YbyT(t, a, b);
}

void Curve::_Get3dDerivative( double t, Point3D* point3D, double a, double b, double step) {
    point3D->z = step / (2*std::numbers::pi);;
    if(a==b) { //circle
        point3D->x = -a*sin( t);
        point3D->y = b*cos( t);
        return;
    }
    point3D->x = _Derivative([this](double t, double a, double b){ return _XbyT(t, a, b);}, t, a, b);
    point3D->y = _Derivative([this](double t, double a, double b){ return _YbyT(t, a, b);}, t, a, b);
//    point3D->x = (_XbyT(t+_dt, a, b)-_XbyT(t-_dt, a, b))/(2*_dt);
//    point3D->y = (_YbyT(t+_dt, a, b)-_YbyT(t-_dt, a, b))/(2*_dt);
 }


