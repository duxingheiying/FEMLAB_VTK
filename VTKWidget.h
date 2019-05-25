#ifndef VTKWIDGET_H
#define VTKWIDGET_H

#include <QVTKWidget.h>

// 通用头文件
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkDataSetMapper.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkUniformGrid.h>
#include <vtkPropPicker.h>
#include <vtkCellPicker.h>
#include <vtkSelectionNode.h>
#include <vtkSelection.h>
#include <vtkExtractSelection.h>
#include <vtkUnstructuredGrid.h>

// 特定头文件
#include <vtkPoints.h>
#include <vtkPointSource.h>
#include <vtkLine.h>
#include <vtkTriangle.h>
#include <vtkQuad.h>
#include <vtkLineSource.h>
#include <vtkNamedColors.h>
#include <vtkPolyVertex.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>
#include <vtkPolygon.h>

#include <vtkCylinderSource.h>

#include <vtkRendererCollection.h>
#include <vtkIdTypeArray.h>
#include <vtkTriangleFilter.h>
#include <vtkCommand.h>
#include <vtkPlaneSource.h>
#include <vtkObjectFactory.h>


#include <QMouseEvent>
#include <QKeyEvent>

class MouseInteractorStyle;

class VTKWidget : public QVTKWidget
{
public:
    explicit VTKWidget(QWidget* parent = NULL, Qt::WindowFlags f = 0);
    virtual ~VTKWidget();

public:
    void BuildGrid(void);
    void PaintVTK(void);

private:
    virtual void mouseMoveEvent(QMouseEvent*);                                // 鼠标移动事件
    virtual void mousePressEvent(QMouseEvent*);                               // 鼠标按键按下事件
    virtual void mouseReleaseEvent(QMouseEvent*);                             // 鼠标按键释放按键
    virtual void keyPressEvent(QKeyEvent*);                                   // 键盘按键按下事件
    virtual void keyReleaseEvent(QKeyEvent*);                                 // 键盘按键释放事件
    void ClearUpData();                                                       // 清理掉所形成图形数据

public:
    bool m_bShowEdge;                                                         // 判定是否显示网格


private:
    // VTK渲染使用，所使用的基本结构
    vtkRenderWindow*                                   m_pvtkRenderWindow;    // 渲染窗口
    vtkSmartPointer<vtkCellArray>                      m_pvtkCellArray;       // 单元组
    vtkSmartPointer<vtkPolyData>                       m_pvtkPolyData;        // 多义线
    vtkSmartPointer<vtkPolyDataMapper>                 m_pvtkPolyDataMapper;  // 资源数据，添加
    vtkSmartPointer<vtkActor>                          m_pvtkActor;           // 渲染属性
    vtkSmartPointer<vtkRenderer>                       m_pvtkRenderere;       // 渲染
    vtkSmartPointer<vtkDataSetMapper>                  m_pvtkDataSetMapper;   // 渲染使用数据
    vtkSmartPointer<vtkRenderWindowInteractor>         m_pvtkRWInteractor;    // 渲染指针
    vtkSmartPointer<vtkInteractorStyleTrackballCamera> m_pvtkIStyleCamera;    // 相机设置

    // vtk拾取使用的变量
    vtkSmartPointer<vtkPropPicker>                     m_pvtkPropPicker;      // 拾取
    vtkSmartPointer<vtkCellPicker>                     m_pvtkCellPicker;      // 单元拾取
    vtkSmartPointer<vtkIdTypeArray>                    m_pvtkIdTypeArray;     // 拾取的ID数组
    vtkSmartPointer<vtkSelectionNode>                  m_pvtkSelectionNode;   // 选择的节点
    vtkSmartPointer<vtkSelection>                      m_pvtkSelection;       // 选择
    vtkSmartPointer<vtkExtractSelection>               m_pvtkExtractSelection;//
    vtkSmartPointer<vtkPolyData>                       m_pvtkSelectPolyData;  // 选择使用数据
    vtkSmartPointer<vtkUnstructuredGrid>               m_pvtkSelectGrid;      //
    vtkSmartPointer<vtkDataSetMapper>                  m_pvtkSelectedMapper;
    vtkSmartPointer<vtkActor>                          m_pvtkSelectedActor;

    vtkSmartPointer<vtkNamedColors>                    m_pvtkNameColors;      // 颜色
    vtkSmartPointer<vtkCylinderSource>                 m_pvtkCyLinderSource;  // 绘制多面柱体
    vtkSmartPointer<vtkPoints>                         m_pvtkPoints;          // 基本点
    vtkSmartPointer<vtkTriangle>                       m_pvtkTriangle;        // 三角形
    vtkSmartPointer<vtkQuad>                           m_pvtkQuad;            // 四边形
};

// Catch mouse events
class MouseInteractorStyle : public vtkInteractorStyleTrackballCamera
{
public:
    static MouseInteractorStyle* New();
    MouseInteractorStyle();
    virtual void OnLeftButtonDown();

public:
    vtkSmartPointer<vtkPolyData> Data;
    vtkSmartPointer<vtkUnstructuredGrid> Grild;
    vtkSmartPointer<vtkDataSetMapper> selectedMapper;
    vtkSmartPointer<vtkActor> selectedActor;
};

#endif // VTKWIDGET_H
