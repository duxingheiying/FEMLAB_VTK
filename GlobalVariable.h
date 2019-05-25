#ifndef GLOBALVARIABLE_H
#define GLOBALVARIABLE_H

#include "vtkUnstructuredGrid.h"
#include "vtkSmartPointer.h"
#include "vtkPoints.h"
#include "vtkLine.h"
#include "vtkPolyLine.h"
#include "vtkFloatArray.h"

#include "BaseGraphic.h"
#include "VTKWidget.h"

#include <map>

using std::vector;
using std::map;

extern VTKWidget*                                    g_VTKWidget;          // 渲染窗口
extern map<int, int>                                 g_VTKPointID_to_PointID;
extern map<int, int>                                 g_PointID_to_VTKPointID;
extern map<int, Point*>                              g_Point_Map;          // 所有点的容器
extern map<int, Line*>                               g_Line_Map;           // 所有线的容器
extern map<int, Triangle*>                           g_Triangle_Map;       // 所有三角形的容器
extern map<int, Quadrangle*>                         g_Quadrangle_Map;     // 所有四边形的容器
extern vector<vtkSmartPointer<vtkUnstructuredGrid> > g_GridVector;         //
extern vtkSmartPointer<vtkUnstructuredGrid>          g_pPointGrid;          //
extern vtkSmartPointer<vtkUnstructuredGrid>          g_pCellGrid;          // 单元图形数据
extern vtkSmartPointer<vtkPoints>                    g_pAllvtkPoints;      //
extern vtkSmartPointer<vtkPolyVertex>                g_pAllPolyVertex;     //
extern vtkSmartPointer<vtkPolyData>                  g_pAllPolyData;       // 用于存储点的数据
extern vtkSmartPointer<vtkFloatArray>                g_pAllFloatArray;     //
extern vtkSmartPointer<vtkLine>                      g_pLine;              // 单条线段
extern vtkSmartPointer<vtkPolyLine>                  g_pPolyLine;          // 单条多义线
extern vector<vtkSmartPointer<vtkLine> >             g_AllLine;            // 所有的线段
extern vector<vtkSmartPointer<vtkTriangle> >         g_AllTriangle;        // 所有的三角形
extern vector<vtkSmartPointer<vtkQuad> >             g_AllQuad;            // 所有的四边形


class GlobalVariable
{
public:
    explicit GlobalVariable();
    virtual ~GlobalVariable();
};

#endif // GLOBALVARIABLE_H
