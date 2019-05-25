#include "FEMMainWindow.h"
#include "ui_FEMMainWindow.h"

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QStringList>
#include <QRegExp>

#include "BaseGraphic.h"
#include "GlobalVariable.h"

class QTextStream;

FEMMainWindow::FEMMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FEMMainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("FEMLAB"));
    g_VTKWidget = new VTKWidget(this);

    setCentralWidget(g_VTKWidget);

    CreateMenue();                                                 // 创建MenuBar中的Menu菜单
    CreateActions();                                               // 创建Actions
    AddActionToMenu();                                             // 添加Actions到Menu中
    AddActionToTBar();                                             // 添加Actions到ToolBar中
}

void FEMMainWindow::CreateMenue(void)
{
    m_pFileMenue = new QMenu(this);
    m_pFileMenue->setTitle(QString::fromLocal8Bit("文件"));

    m_pContralMenu = new QMenu(this);
    m_pContralMenu->setTitle(QString::fromLocal8Bit("控制"));

    ui->m_pMenubar->addMenu(m_pFileMenue);
    ui->m_pMenubar->addMenu(m_pContralMenu);
}

void FEMMainWindow::CreateActions(void )
{
    // 打开文件
    m_pOpenFileAction = new QAction(this);
    m_pOpenFileAction->setText(QString::fromLocal8Bit("打开"));
    m_pOpenFileAction->setShortcut(QKeySequence(tr("Ctrl+O")));
    m_pOpenFileAction->setIcon(QIcon(":/Actions/document-open.png"));
    connect(m_pOpenFileAction, SIGNAL(triggered(bool)), this, SLOT(OpenSelectFileDialog(bool)));

    // 保存文件
    m_pSaveFileAction = new QAction(this);
    m_pSaveFileAction->setText(QString::fromLocal8Bit("保存"));
    m_pSaveFileAction->setShortcut(QKeySequence(tr("Ctrl+S")));
    m_pSaveFileAction->setIcon(QIcon("://Actions/document-save.png"));

    // 另存文件
    m_pSaveAsAction = new QAction(this);
    m_pSaveAsAction->setText(QString::fromLocal8Bit("另存为..."));
    m_pSaveAsAction->setShortcut(QKeySequence(tr("Ctrl+Shift+S")));
    m_pSaveAsAction->setIcon(QIcon("://Actions/document-save-as.png"));

    // 新建文件
    m_pNewFileAction = new QAction(this);
    m_pNewFileAction->setText(QString::fromLocal8Bit("新建"));
    m_pNewFileAction->setShortcut(QKeySequence(tr("Ctrl+N")));
    m_pNewFileAction->setIcon(QIcon("://Actions/document-new.png"));

    // 新建文件
    m_pContralEdgeShowAction = new QAction(this);
    m_pContralEdgeShowAction->setText(QString::fromLocal8Bit("网格"));
    m_pContralEdgeShowAction->setShortcut(QKeySequence(tr("")));
    m_pContralEdgeShowAction->setIcon(QIcon("://Actions/stock_mail-send.png"));
    connect(m_pContralEdgeShowAction, SIGNAL(triggered(bool)), this, SLOT(ShowOrHideEdge(bool)));
}

void FEMMainWindow::AddActionToMenu() const
{
    m_pFileMenue->addAction(m_pOpenFileAction);
    m_pFileMenue->addAction(m_pSaveFileAction);
    m_pFileMenue->addAction(m_pSaveAsAction);
    m_pFileMenue->addSeparator();
    m_pFileMenue->addAction(m_pNewFileAction);

    m_pContralMenu->addAction(m_pContralEdgeShowAction);
}

void FEMMainWindow::AddActionToTBar() const
{
    ui->m_pToolBar->addAction(m_pOpenFileAction);
    ui->m_pToolBar->addAction(m_pSaveFileAction);
    ui->m_pToolBar->addAction(m_pSaveAsAction);
    ui->m_pToolBar->addSeparator();
    ui->m_pToolBar->addAction(m_pNewFileAction);

    ui->m_pToolBar->addAction(m_pContralEdgeShowAction);
}

void FEMMainWindow::ShowOrHideEdge(bool bShow_)
{
    g_VTKWidget->m_bShowEdge = !g_VTKWidget->m_bShowEdge;

    g_VTKWidget->PaintVTK();
    g_VTKWidget->repaint();
}

void FEMMainWindow::OpenSelectFileDialog(bool)
{
    QString _sSelectFileName;
    _sSelectFileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"),
                                                    tr(""),
                                                    tr("testFile(*.txt);;RealData File(*.bdf *.inp *.cdb);;Test File(*.unv)"));
    QFile _file;
    _file.setFileName(_sSelectFileName);

    // 如果读取文件失败，就跳出该函数
    if(!_file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this,
                             QString::fromLocal8Bit("警告"),
                             QString::fromLocal8Bit("打开文件失败！！"),
                             QMessageBox::Ok);
        return;  // 跳出函数体
    }

    // 清理掉所有存储的内存
    ClearUpStore();

    QString _strCurrentString;

    QTextStream _streamInputString;
    _streamInputString.setDevice(&_file);

    uint _unitType = 0;

    while(!_streamInputString.atEnd())
    {
        _strCurrentString = _streamInputString.readLine();

        _strCurrentString = _strCurrentString.trimmed();  // 去掉前后的标识符

        if(_strCurrentString.contains("Nodes"))
        {
            _unitType = 1;  // 表示是节点
        }
        else if(_strCurrentString.contains("Element"))
        {
            _unitType = 2;
        }

        if(_unitType == 1)
        {
            ReadPoint(_strCurrentString);                  // 读取节点结构
        }
        else if(_unitType == 2)
        {
            ReadUnit(_strCurrentString);                   // 读取单元结构
        }
    }

    g_VTKWidget->BuildGrid();
}

void FEMMainWindow::ReadPoint(const QString PointLine_) const
{
    QStringList _CombineList = PointLine_.split(QRegExp("\\s+"));
    if (_CombineList.size() == 4)
    {
        Point* pt = new Point(_CombineList[1].toDouble(),
                              _CombineList[2].toDouble(),
                              _CombineList[3].toDouble());

        int _PointID = _CombineList[0].toInt();
        pt->ID = _PointID;
        g_Point_Map[_PointID] = pt;
    }
    else
    {
        return;
    }
}

void FEMMainWindow::ReadUnit(const QString UnitLine_) const
{
    QStringList _CombineList = UnitLine_.split(QRegExp("\\s+"));

    /*******************************************************************
     * 所有单元图形
     * 现在设计单元的类型为第一个表示单元的类型，
     * 第二个数据表示ID值
     * 第三以后表示所使用点的ID值
    ********************************************************************/
    // 直线有4个数据信息
    if(UnitLine_.startsWith("Line"))
    {
        if (_CombineList.size() == 4)
        {
            Line* _line = new Line(_CombineList[2].toInt(),  // 表示实际存储的第一个点
                                   _CombineList[3].toInt()); // 表示实际存储的第二个点
            int _PointID = _CombineList[1].toInt();
            _line->ID = _PointID;

            g_Line_Map[_PointID] = _line;
        }
        else
        {
            return;
        }
    }
    // 三角形有5个数据
    else if(UnitLine_.startsWith("Triangle"))
    {
        if(_CombineList.size() == 5)
        {
            Triangle* triangle = new Triangle(_CombineList[2].toInt(),
                                              _CombineList[3].toInt(),
                                              _CombineList[4].toInt());

            int _TriangleID = _CombineList[1].toInt();
            triangle->ID = _TriangleID;
            g_Triangle_Map[_TriangleID] = triangle;
        }
    }
    // 四边形形有6个数据
    else if(UnitLine_.startsWith("Quadrilateral"))
    {
        if(_CombineList.size() == 6)
        {
            Quadrangle * quadrangle = new Quadrangle(_CombineList[2].toInt(),
                                                     _CombineList[3].toInt(),
                                                     _CombineList[4].toInt(),
                                                     _CombineList[5].toInt());

            int _QuadrangleID = _CombineList[1].toInt();
            quadrangle->ID = _QuadrangleID;
            g_Quadrangle_Map[_QuadrangleID] = quadrangle;
        }
        else
        {
            return;
        }
    }
    else
    {
        return;
    }
}

void FEMMainWindow::mouseMoveEvent(QMouseEvent*)
{
}

void FEMMainWindow::mousePressEvent(QMouseEvent*)
{
}

void FEMMainWindow::mouseReleaseEvent(QMouseEvent*)
{
}

void FEMMainWindow::keyPressEvent(QKeyEvent*)
{
}

void FEMMainWindow::keyReleaseEvent(QKeyEvent*)
{
}

void FEMMainWindow::ClearUpStore()
{
    // 清理掉所有点的对应关系
    g_PointID_to_VTKPointID.clear();

    // 清理掉节点的存储
    for (auto _itor = g_Point_Map.begin();
         _itor != g_Point_Map.end();
         _itor++)
    {
        delete _itor->second;
        _itor->second = NULL;
    }
    g_Point_Map.clear();              //清除掉点所用ID

    // 清理直线的存储方式
    for(auto _itor = g_Line_Map.begin();
        _itor != g_Line_Map.end();
        _itor++)
    {
        delete _itor->second;
        _itor->second = NULL;
    }
    g_Line_Map.clear();

    // 清理三角形的存储
    for(auto _itor = g_Triangle_Map.begin();
        _itor != g_Triangle_Map.end();
        _itor++)
    {
        delete _itor->second;
        _itor->second = NULL;
    }
    g_Triangle_Map.clear();

    // 清理四边形
    for(auto _itor = g_Quadrangle_Map.begin();
        _itor != g_Quadrangle_Map.end();
        _itor++)
    {
        delete _itor->second;
        _itor->second = NULL;
    }
    g_Quadrangle_Map.clear();
}

FEMMainWindow::~FEMMainWindow()
{
    ClearUpStore();
    delete g_VTKWidget;
    delete m_pFileMenue;
    delete m_pOpenFileAction;
    delete m_pSaveAsAction;
    delete m_pSaveFileAction;
    delete m_pNewFileAction;
    delete ui;
}
