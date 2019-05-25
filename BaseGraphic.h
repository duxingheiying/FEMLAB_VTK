#ifndef BASEGRAPHIC_H
#define BASEGRAPHIC_H

/************************************************************************
 * 此类主要是用来绘制一些基本的图形比如：点/线/三角形/四边形
 * VTK库的引入
 * **********************************************************************/

#include "vtkPoints.h"
#include "vtkLine.h"
#include "vtkPolyLine.h"
#include "vtkGenericDataArray.h"

#include "Vector3D.h"

class BaseGraphic
{
public:
    explicit BaseGraphic();
    virtual ~BaseGraphic();

public:
    virtual void Show();
    virtual void Hide();

public:
    uint ID;                               // 单元ID号
    bool m_bIsVisable;                   // 表示显示与否的属性

};

// 三角形绘制
class Point : public BaseGraphic
{
public:
    explicit Point();
    explicit Point(Vector3D);
    explicit Point(double x = 0,
                   double y = 0,
                   double z = 0);

    virtual ~Point();
    virtual void Show();
    virtual void Hide();

    double x();
    double y();
    double z();

public:
    float m_fPointType;

private:
    double X;
    double Y;
    double Z;

    double* m_pdPointList;       // 节点列表
    bool b_isShow;
};

// 直线绘制
class Line : public BaseGraphic
{
public:
    explicit Line();

    explicit Line(Vector3D FirstPoint,           // 直线第一个点
                  Vector3D SecondPoint);         // 直线第二个点

    explicit Line(uint FirstPointID_,            // 第一个节点的ID
                  uint SecondPointID_);          // 第二个节点的ID

    virtual ~Line();

    virtual void Show();
    virtual void Hide();

public:
    uint m_nFirstPointID;
    uint m_nSecondPointID;
};

// 三角形绘制
class Triangle : public BaseGraphic
{
public:
    explicit Triangle();
    explicit Triangle(int, int, int);
    virtual ~Triangle();

    virtual void Show();
    virtual void Hide();

public:
    int m_nFirstPointID;
    int m_nSecondPointID;
    int m_nThirdPointID;
};

// 四边形绘制
class Quadrangle : public BaseGraphic
{
public:
    explicit Quadrangle();
    explicit Quadrangle(Point, Point, Point, Point);
    explicit Quadrangle(int nFirstPointID_,
                        int nSecondPointID_,
                        int nThirdPointID_,
                        int nFourthPointID_);

    virtual ~Quadrangle();

    virtual void Show();
    virtual void Hide();

public:
    int m_nFirstPointID;
    int m_nSecondPointID;
    int m_nThirdPointID;
    int m_nFourthPointID;
};

#endif // BASEGRAPHIC_H
