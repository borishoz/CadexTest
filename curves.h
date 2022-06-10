#ifndef CURVES_H
#define CURVES_H

#include <numbers>
#include <cstdio>
#include <functional>

class Point3D {
public:
    double x, y, z;
};

enum class CurveType {
    Circle,
    Ellipse,
    Helixe
};

class Curve {
public:
    Curve( double a, bool& ok) : _a(a) { ok=true; if(a<0) ok = false;}

    virtual void Get3dPoint( double t, Point3D* point3D) = 0;
    virtual void Get3dDerivative( double t, Point3D* point3D) = 0;
    virtual CurveType GetCurveType() = 0;

    virtual char* StrCurveParams() = 0;
    char* StrCurve3dPoint( double t);
    char* StrCurve3dDerivative( double t);

    double Get_a() { return _a;}
protected:
    double _a;

    void _Get3dPoint( double t, Point3D* point3D, double a, double b, double step);

    void _Get3dDerivative( double t, Point3D* point3D, double a, double b, double step);
    double _XbyT(double t, double a, double b) {return a*cos( _FiByT(t, a, b));}
    double _YbyT(double t, double a, double b){return b*sin( _FiByT(t, a, b));}
    double _FiByT(double t, double a, double b) {return atan2( a*sin(t), b*cos(t));}
    double _Derivative( std::function<double(double t, double a, double b)> funcPtr, double t, double a, double b){
                                                            return (funcPtr(t+_dt, a, b)-funcPtr(t-_dt, a, b))/(2*_dt);}
    const static double _dt;

    const static int _bufferSize=100;
    static char _printBuffer [_bufferSize];
};

class Helixe : public Curve {
public:
    Helixe( double a, double step, bool& ok) : Curve( a, ok), _b(step) {}

    virtual void Get3dPoint( double t, Point3D* point3D) override { _Get3dPoint( t, point3D, _a, _a, _b);}
    virtual void Get3dDerivative( double t, Point3D* point3D) override { _Get3dDerivative( t, point3D, _a, _a, _b);}
    virtual CurveType GetCurveType() override { return CurveType::Helixe;}

    virtual char* StrCurveParams() { sprintf(_printBuffer, "Helixe R: %f, Step: %f", _a, _b ); return _printBuffer;}

protected:
    double _b;
};

class Ellipse : public Helixe {
public:
    Ellipse( double a, double b, bool& ok) : Helixe( a, b, ok) { if(b<0) ok = false;}

    virtual void Get3dPoint( double t, Point3D* point3D) override { _Get3dPoint( t, point3D,  _a, _b, 0);}
    virtual void Get3dDerivative( double t, Point3D* point3D) override { _Get3dDerivative( t, point3D, _a, _b, 0);}
    virtual CurveType GetCurveType() override { return CurveType::Ellipse;}

    virtual char* StrCurveParams() { sprintf(_printBuffer, "Ellipse a: %f, b: %f", _a, _b ); return _printBuffer;}
};

class Circle : public Curve {
public:
    Circle( double r, bool& ok) : Curve( r, ok) {}

    virtual void Get3dPoint( double t, Point3D* point3D) override { _Get3dPoint( t, point3D,  _a, _a, 0);}
    virtual void Get3dDerivative( double t, Point3D* point3D) override { _Get3dDerivative( t, point3D, _a, _a, 0);}
    virtual CurveType GetCurveType() override { return CurveType::Circle;}

    virtual char* StrCurveParams() { sprintf(_printBuffer, "Circle R: %f", _a ); return _printBuffer;}

    double GetRadius() { return Get_a();}
  };



#endif // CURVES_H
