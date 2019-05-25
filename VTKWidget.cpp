#include "VTKWidget.h"

#include "GlobalVariable.h"

#include "vtkCellData.h"
#include "vtkUnsignedCharArray.h"
#include "vtkRendererCollection.h"
#include "vtkAbstractPicker.h"
#include "vtkSphereSource.h"

#include <QDebug>

// 鼠标事件使用宏定义
vtkStandardNewMacro(MouseInteractorStyle);

VTKWidget::VTKWidget(QWidget *parent, Qt::WindowFlags f):
    QVTKWidget(parent, f)
{
    // 默认情况下显示网格
    m_bShowEdge = true;

    // 初始化对应点的VTK窗口
    m_pvtkRenderWindow     = GetRenderWindow();
    m_pvtkCellArray        = vtkSmartPointer<vtkCellArray>::New();
    m_pvtkPolyData         = vtkSmartPointer<vtkPolyData>::New();
    m_pvtkPolyDataMapper   = vtkSmartPointer<vtkPolyDataMapper>::New();
    m_pvtkActor            = vtkSmartPointer<vtkActor>::New();
    m_pvtkRenderere        = vtkSmartPointer<vtkRenderer>::New();
    m_pvtkDataSetMapper    = vtkSmartPointer<vtkDataSetMapper>::New();
    m_pvtkRWInteractor     = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    m_pvtkIStyleCamera     = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    m_pvtkPropPicker       = vtkSmartPointer<vtkPropPicker>::New();

    // 拾取使用变量
    m_pvtkCellPicker       = vtkSmartPointer<vtkCellPicker>::New();
    m_pvtkIdTypeArray      = vtkSmartPointer<vtkIdTypeArray>::New();
    m_pvtkSelectionNode    = vtkSmartPointer<vtkSelectionNode>::New();
    m_pvtkSelection        = vtkSmartPointer<vtkSelection>::New();
    m_pvtkExtractSelection = vtkSmartPointer<vtkExtractSelection>::New();
    m_pvtkSelectPolyData   = vtkSmartPointer<vtkPolyData>::New();
    m_pvtkSelectGrid       = vtkSmartPointer<vtkUnstructuredGrid>::New();
    m_pvtkSelectedMapper   = vtkSmartPointer<vtkDataSetMapper>::New();
    m_pvtkSelectedActor    = vtkSmartPointer<vtkActor>::New();

    g_pPointGrid            = vtkSmartPointer<vtkUnstructuredGrid>::New();
    g_pCellGrid            = vtkSmartPointer<vtkUnstructuredGrid>::New();
    g_pAllvtkPoints        = vtkSmartPointer<vtkPoints>::New();
    g_pAllPolyVertex       = vtkSmartPointer<vtkPolyVertex>::New();
    g_pLine                = vtkSmartPointer<vtkLine>::New();
    g_pPolyLine            = vtkSmartPointer<vtkPolyLine>::New();
    g_pAllFloatArray       = vtkSmartPointer<vtkFloatArray>::New();

    BuildGrid();
}

void VTKWidget::BuildGrid(void)
{
    // 计算点的个数
    size_t _nPointNumber = g_Point_Map.size();

    g_pAllvtkPoints->Initialize();
    g_pAllvtkPoints->SetNumberOfPoints(_nPointNumber);//此行可有可无
    int _PointID = 0;
    for (auto _iter = g_Point_Map.begin(); _iter != g_Point_Map.end(); _iter++)
    {
        Point* _Point = _iter->second;
        g_pAllvtkPoints->InsertPoint(_PointID, _Point->x(), _Point->y(), _Point->z());
        g_PointID_to_VTKPointID[_Point->ID] = _PointID;  // 设置对应的ID值

        _PointID++;
    }

    g_pAllPolyVertex->Initialize();
    g_pAllPolyVertex->GetPointIds()->SetNumberOfIds(_nPointNumber);//必须设置Id个数，否则可以编译，不能运行
    for (auto _iter = g_Point_Map.begin(); _iter != g_Point_Map.end(); _iter++)
    {
        Point* _Point = _iter->second;
        g_pAllPolyVertex->GetPointIds()->SetId(g_PointID_to_VTKPointID[_Point->ID], _Point->ID);
    }

    g_pAllFloatArray->Initialize();
    g_pAllFloatArray->SetNumberOfTuples(_nPointNumber);//必须设置Id个数，否则可以编译，不能运行
    for (auto _iter = g_Point_Map.begin(); _iter != g_Point_Map.end(); _iter++)
    {
        Point* _Point = _iter->second;
        g_pAllFloatArray->InsertValue(g_PointID_to_VTKPointID[_Point->ID], _Point->m_fPointType);
    }

    // 清理掉所有的数据信息，形成新的数据类型
    ClearUpData();
    // 生成测试直线
    for(auto _itor = g_Line_Map.begin(); _itor != g_Line_Map.end(); _itor++)
    {
        Line* _line = _itor->second;
        vtkSmartPointer<vtkLine> _vtkLine = vtkSmartPointer<vtkLine>::New();
        _vtkLine->GetPointIds()->SetNumberOfIds(2);
        _vtkLine->GetPointIds()->SetId(0, g_PointID_to_VTKPointID[_line->m_nFirstPointID]);
        _vtkLine->GetPointIds()->SetId(1, g_PointID_to_VTKPointID[_line->m_nSecondPointID]);
        g_AllLine.push_back(_vtkLine);
    }

    // 生成三角形
    for(auto _itor = g_Triangle_Map.begin(); _itor != g_Triangle_Map.end(); _itor++)
    {
        Triangle* _Triangle = _itor->second;
        vtkSmartPointer<vtkTriangle> _vtkTriangle = vtkSmartPointer<vtkTriangle>::New();

        _vtkTriangle->GetPointIds()->SetNumberOfIds(3);

        _vtkTriangle->GetPointIds()->SetId(0, g_PointID_to_VTKPointID[_Triangle->m_nFirstPointID]);
        _vtkTriangle->GetPointIds()->SetId(1, g_PointID_to_VTKPointID[_Triangle->m_nSecondPointID]);
        _vtkTriangle->GetPointIds()->SetId(2, g_PointID_to_VTKPointID[_Triangle->m_nThirdPointID]);

        g_AllTriangle.push_back(_vtkTriangle);
    }

    // 生成四边形
    for(auto _itor = g_Quadrangle_Map.begin(); _itor != g_Quadrangle_Map.end(); _itor++)
    {
        Quadrangle* _Quadrangle = _itor->second;
        vtkSmartPointer<vtkQuad> _vtkQuad = vtkSmartPointer<vtkQuad>::New();

        _vtkQuad->GetPointIds()->SetNumberOfIds(4);

        _vtkQuad->GetPointIds()->SetId(0, g_PointID_to_VTKPointID[_Quadrangle->m_nFirstPointID]);
        _vtkQuad->GetPointIds()->SetId(1, g_PointID_to_VTKPointID[_Quadrangle->m_nSecondPointID]);
        _vtkQuad->GetPointIds()->SetId(2, g_PointID_to_VTKPointID[_Quadrangle->m_nThirdPointID]);
        _vtkQuad->GetPointIds()->SetId(3, g_PointID_to_VTKPointID[_Quadrangle->m_nFourthPointID]);

        g_AllQuad.push_back(_vtkQuad);
    }

    //将以上三部分数据组合成一个结构vtkUnstructureGrid
    g_pCellGrid->Initialize();  // 初始化数据
    g_pCellGrid->Allocate(1, 1);
    g_pCellGrid->SetPoints(g_pAllvtkPoints);                      // 所有的点设置进去
    g_pCellGrid->GetPointData()->SetScalars(g_pAllFloatArray);

    // 添加点的图元到Grid里面
    // 这个会影响到拾取功能，等待进一步的理解
//    g_pCellGrid->InsertNextCell(g_pAllPolyVertex->GetCellType(), g_pAllPolyVertex->GetPointIds());

        // 添加线性结构
        for(size_t _i = 0; _i < g_AllLine.size(); _i++)
        {
            g_pCellGrid->InsertNextCell(g_AllLine[_i]->GetCellType(), g_AllLine[_i]->GetPointIds());
        }

        // 添加三角面
        for(size_t _i = 0; _i < g_AllTriangle.size(); _i++)
        {
            g_pCellGrid->InsertNextCell(g_AllTriangle[_i]->GetCellType(), g_AllTriangle[_i]->GetPointIds());
        }

        //  添加四角面片
        for(size_t _i = 0; _i < g_AllQuad.size(); _i++)
        {
            g_pCellGrid->InsertNextCell(g_AllQuad[_i]->GetCellType(), g_AllQuad[_i]->GetPointIds());
        }

    PaintVTK();
}

// 显示所要绘制的结构
void VTKWidget::PaintVTK(void)
{
    //设置映射器
#if VTK_MAJOR_VERSION <= 5
    m_pvtkDataSetMapper->SetInputConnection(g_GridPoint->GetProducerPort());
#else
    m_pvtkDataSetMapper->SetInputData(g_pCellGrid);
#endif

//    m_pvtkDataSetMapper->ScalarVisibilityOn();
    m_pvtkDataSetMapper->ScalarVisibilityOff();        // 关闭从Grid传递过来的属性
    m_pvtkActor->SetMapper(m_pvtkDataSetMapper);
//    m_pvtkActor->GetProperty()->SetRepresentationToPoints();
    m_pvtkActor->GetProperty()->SetDiffuseColor(0.5, 0.5, 0);

    // 显示边框
    if(m_bShowEdge)
    {
        m_pvtkActor->GetProperty()->EdgeVisibilityOn();
        m_pvtkActor->GetProperty()->SetEdgeColor(0, 0, 1);
    }
    else
    {
        m_pvtkActor->GetProperty()->EdgeVisibilityOff();
    }


    m_pvtkActor->GetProperty()->SetPointSize(5);
    m_pvtkActor->GetProperty()->SetLineWidth(1);
    m_pvtkActor->GetProperty()->SetColor(0.85, 0.0, 0.85);

    //创建显示窗口
//    m_pvtkRenderere->AddViewProp(m_pvtkActor);
    m_pvtkRenderere->SetBackground(0.25, 0.25, 0.25);
    m_pvtkRenderere->AddActor(m_pvtkActor);
    m_pvtkRenderWindow->AddRenderer(m_pvtkRenderere);
    m_pvtkRWInteractor->SetInteractorStyle(m_pvtkIStyleCamera);
    m_pvtkRWInteractor->SetRenderWindow(m_pvtkRenderWindow);
    m_pvtkRWInteractor->Initialize();
//    m_pvtkRenderWindow->SetSize(700, 700);

//    // 借助第三方工具类进行拾取功能
//    // Set the custom stype to use for interaction
//    vtkSmartPointer<MouseInteractorStyle> style =
//        vtkSmartPointer<MouseInteractorStyle>::New();
//    style->SetDefaultRenderer(m_pvtkRenderere);
//    style->Grild = g_pCellGrid;
//    m_pvtkRWInteractor->SetInteractorStyle(style);

    m_pvtkRenderere->ResetCamera();
    m_pvtkRenderere->GetActiveCamera()->ParallelProjectionOn();
    m_pvtkRenderWindow->Render();
}

void VTKWidget::mouseMoveEvent(QMouseEvent* event)
{
    QVTKWidget::mouseMoveEvent(event);
}

void VTKWidget::mousePressEvent(QMouseEvent* event)
{
    // 左键事件
    if(event->button() == Qt::LeftButton)
    {
        int* pos = m_pvtkRenderWindow->GetInteractor()->GetEventPosition();
        m_pvtkCellPicker->SetTolerance(0.0005);

        // Pick from this location.
        m_pvtkCellPicker->Pick(pos[0],
                               pos[1],
                               pos[2],
                               m_pvtkRenderWindow->GetRenderers()->GetFirstRenderer());

        qDebug()<<"Select ObjectID:"<<m_pvtkCellPicker->GetCellId();

//        double* worldPosition = m_pvtkCellPicker->GetPickPosition();
        if (m_pvtkCellPicker->GetCellId() != -1)
        {
            m_pvtkIdTypeArray->RemoveAllObservers();
            m_pvtkIdTypeArray->Initialize();
            m_pvtkIdTypeArray->SetNumberOfComponents(1);
            m_pvtkIdTypeArray->InsertNextValue(m_pvtkCellPicker->GetCellId());

            m_pvtkSelectionNode->SetFieldType(vtkSelectionNode::CELL);
            m_pvtkSelectionNode->SetContentType(vtkSelectionNode::INDICES);
            m_pvtkSelectionNode->SetSelectionList(m_pvtkIdTypeArray);
            m_pvtkSelection->RemoveAllNodes();
            m_pvtkSelection->Initialize();
            m_pvtkSelection->AddNode(m_pvtkSelectionNode);

#if VTK_MAJOR_VERSION <= 5
            extractSelection->SetInput(0, g_pCellGrid);
            extractSelection->SetInput(1, m_pvtkSelection);
#else
            m_pvtkExtractSelection->SetInputData(0, g_pCellGrid);
            m_pvtkExtractSelection->SetInputData(1, m_pvtkSelection);
#endif
            m_pvtkExtractSelection->Update();

            m_pvtkSelectGrid->RemoveAllObservers();
            m_pvtkSelectGrid->RemoveGhostCells();
            m_pvtkSelectGrid->Initialize();
            // In selection
            m_pvtkSelectGrid->ShallowCopy(m_pvtkExtractSelection->GetOutput());

            m_pvtkSelectedMapper->RemoveAllInputs();
#if VTK_MAJOR_VERSION <= 5
            m_pvtkSelectedMapper->SetInputConnection(
                        selected->GetProducerPort());
#else
            m_pvtkSelectedMapper->SetInputData(m_pvtkSelectGrid);
#endif
            m_pvtkSelectedMapper->ScalarVisibilityOff();                  // 关闭从Grid继承过来的属性

            m_pvtkSelectedActor->RemoveAllObservers();
            m_pvtkSelectedActor->SetMapper(m_pvtkSelectedMapper);
            m_pvtkSelectedActor->GetProperty()->SetDiffuseColor(0, 0, 1); // 和上面的函数配合使用
            m_pvtkSelectedActor->GetProperty()->EdgeVisibilityOn();
            m_pvtkSelectedActor->GetProperty()->SetEdgeColor(0, 1, 0);
            m_pvtkSelectedActor->GetProperty()->SetLineWidth(3);

            m_pvtkRenderWindow->GetRenderers()->GetFirstRenderer()->AddActor(m_pvtkSelectedActor);
        }
        else
        {
            m_pvtkSelectGrid->RemoveAllObservers();
            m_pvtkSelectGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
            m_pvtkSelectGrid->Initialize();
            m_pvtkSelectedMapper->RemoveAllInputs();
            m_pvtkSelectedMapper->SetInputData(m_pvtkSelectGrid);
            m_pvtkSelectedActor->SetMapper(m_pvtkSelectedMapper);
            m_pvtkRenderWindow->GetRenderers()->GetFirstRenderer()->AddActor(m_pvtkSelectedActor);
        }
    }

    QVTKWidget::mousePressEvent(event);
}


void VTKWidget::mouseReleaseEvent(QMouseEvent* event)
{
    QVTKWidget::mouseReleaseEvent(event);
}

void VTKWidget::keyPressEvent(QKeyEvent* event)
{
    QVTKWidget::keyPressEvent(event);
}

void VTKWidget::keyReleaseEvent(QKeyEvent* event)
{
    QVTKWidget::keyReleaseEvent(event);
}

void VTKWidget::ClearUpData()
{
    // 清理线性的数据
    g_AllLine.clear();
    // 清理所有三角形的数据
    g_AllTriangle.clear();
    // 清理所有三角形的数据
    g_AllQuad.clear();
}

VTKWidget::~VTKWidget()
{
    ClearUpData();
}

// 继承于第三方库使用重写鼠标事件
MouseInteractorStyle::MouseInteractorStyle()
{
    selectedMapper = vtkSmartPointer<vtkDataSetMapper>::New();
    selectedActor = vtkSmartPointer<vtkActor>::New();
}

void MouseInteractorStyle::OnLeftButtonDown()
{
    // Get the location of the click (in window coordinates)
    int* pos = this->GetInteractor()->GetEventPosition();

    vtkSmartPointer<vtkCellPicker> picker =
        vtkSmartPointer<vtkCellPicker>::New();
    picker->SetTolerance(0.0005);

    // Pick from this location.
    picker->Pick(pos[0], pos[1], pos[2], this->GetDefaultRenderer());

    double* worldPosition = picker->GetPickPosition();
    std::cout << "Cell id is: " << picker->GetCellId() << std::endl;

    if (picker->GetCellId() != -1)
    {

        std::cout << "Pick position is: " << worldPosition[0] << " " << worldPosition[1]
            << " " << worldPosition[2] << endl;

        vtkSmartPointer<vtkIdTypeArray> ids =
            vtkSmartPointer<vtkIdTypeArray>::New();
        ids->SetNumberOfComponents(1);
        ids->InsertNextValue(picker->GetCellId());

        vtkSmartPointer<vtkSelectionNode> selectionNode =
            vtkSmartPointer<vtkSelectionNode>::New();
        selectionNode->SetFieldType(vtkSelectionNode::CELL);
        selectionNode->SetContentType(vtkSelectionNode::INDICES);
        selectionNode->SetSelectionList(ids);

        vtkSmartPointer<vtkSelection> selection =
            vtkSmartPointer<vtkSelection>::New();
        selection->AddNode(selectionNode);

        vtkSmartPointer<vtkExtractSelection> extractSelection =
            vtkSmartPointer<vtkExtractSelection>::New();
#if VTK_MAJOR_VERSION <= 5
        extractSelection->SetInput(0, this->Data);
        extractSelection->SetInput(1, selection);
#else
        extractSelection->SetInputData(0, this->Grild);
        extractSelection->SetInputData(1, selection);
#endif
        extractSelection->Update();

        // In selection
        vtkSmartPointer<vtkUnstructuredGrid> selected =
            vtkSmartPointer<vtkUnstructuredGrid>::New();
        selected->ShallowCopy(extractSelection->GetOutput());

        std::cout << "There are " << selected->GetNumberOfPoints()
            << " points in the selection." << std::endl;
        std::cout << "There are " << selected->GetNumberOfCells()
            << " cells in the selection." << std::endl;

#if VTK_MAJOR_VERSION <= 5
        selectedMapper->SetInputConnection(
            selected->GetProducerPort());
#else
        selectedMapper->SetInputData(selected);
#endif
        selectedMapper->ScalarVisibilityOff();
        selectedActor->SetMapper(selectedMapper);
        selectedActor->GetProperty()->SetColor(0, 0, 1);
        selectedActor->GetProperty()->EdgeVisibilityOn();
        selectedActor->GetProperty()->SetEdgeColor(1, 1, 1);
        selectedActor->GetProperty()->SetLineWidth(3);

        this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(selectedActor);
    }

    // Forward events
    vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
}


