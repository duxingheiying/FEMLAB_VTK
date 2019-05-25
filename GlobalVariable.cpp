#include "GlobalVariable.h"

VTKWidget*                                    g_VTKWidget;              // 渲染窗口

map<int, int>                                 g_VTKPointID_to_PointID;
map<int, int>                                 g_PointID_to_VTKPointID;
map<int, Point*>                              g_Point_Map;             // 所有点的组合
map<int, Line*>                               g_Line_Map;              // 所有线的组合
map<int, Triangle*>                           g_Triangle_Map;          // 所有三角形的组合
map<int, Quadrangle*>                         g_Quadrangle_Map;        // 所有四边形的组合
vector<vtkSmartPointer<vtkUnstructuredGrid>>  g_GridVector;
vtkSmartPointer<vtkUnstructuredGrid>          g_pPointGrid;
vtkSmartPointer<vtkUnstructuredGrid>          g_pCellGrid;             // 单元图形数据
vtkSmartPointer<vtkPoints>                    g_pAllvtkPoints;
vtkSmartPointer<vtkPolyVertex>                g_pAllPolyVertex;
vtkSmartPointer<vtkPolyData>                  g_pAllPolyData;          // 用于存储点的数据
vtkSmartPointer<vtkLine>                      g_pLine;
vtkSmartPointer<vtkPolyLine>                  g_pPolyLine;
vector< vtkSmartPointer<vtkLine> >            g_AllLine;
vector<vtkSmartPointer<vtkTriangle> >         g_AllTriangle;           // 所有的三角形
vtkSmartPointer<vtkFloatArray>                g_pAllFloatArray;
vector<vtkSmartPointer<vtkQuad> >             g_AllQuad;               // 所有的四边形

GlobalVariable::GlobalVariable()
{
}

GlobalVariable::~GlobalVariable()
{
    g_pPointGrid->Delete();
}
