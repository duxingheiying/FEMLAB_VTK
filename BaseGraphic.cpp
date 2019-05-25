#include "BaseGraphic.h"

BaseGraphic::BaseGraphic()
{
}

// 显示图形
void BaseGraphic::Show()
{
    m_bIsVisable = true;
}

// 隐藏对应的图像
void BaseGraphic::Hide()
{
    m_bIsVisable = false;
}

BaseGraphic::~BaseGraphic()
{
}

Point::Point()
{
    X = 0;
    Y = 0;
    Z = 0;
}

Point::Point(Vector3D)
{
//    X = point_.x();
//    Y = point_.y();
//    Z = point_.z();

    m_fPointType = 0;
}

Point::Point(double x, double y, double z):
    X (x), Y(y), Z(z)
{
    m_fPointType = 0.0;
}

double Point::x()
{
    return X;
}

double Point::y()
{
    return Y;
}

double Point::z()
{
    return Z;
}

void Point::Show()
{
}

void Point::Hide()
{

}

Point::~Point()
{
}

Line::Line(uint FirstPointID_, uint SecondPointID_):
    m_nFirstPointID(FirstPointID_), m_nSecondPointID(SecondPointID_)
{
}

Line::Line(Vector3D FirstPoint, Vector3D SecondPoint)
{
}

Line::Line()
{
}

void Line::Show()
{

}

void Line::Hide()
{

}

Line::~Line()
{

}

Triangle::Triangle()
{

}

Triangle::Triangle(int nFirstPointID_,
                   int nSecondPointID_,
                   int nthirdPointID_) :
    m_nFirstPointID(nFirstPointID_),
    m_nSecondPointID(nSecondPointID_),
    m_nThirdPointID(nthirdPointID_)
{

}

void Triangle::Show()
{

}

void Triangle::Hide()
{

}

Triangle::~Triangle()
{

}

Quadrangle::Quadrangle()
{

}

Quadrangle::Quadrangle(Point, Point, Point, Point)
{

}

Quadrangle::Quadrangle(int nFirstPointID_,
                       int nSecondPointID_,
                       int nThirdPointID_,
                       int nFourthPointID_):
    m_nFirstPointID(nFirstPointID_),
    m_nSecondPointID(nSecondPointID_),
    m_nThirdPointID(nThirdPointID_),
    m_nFourthPointID(nFourthPointID_)
{

}

void Quadrangle::Show()
{

}

void Quadrangle::Hide()
{

}

Quadrangle::~Quadrangle()
{

}
