#ifndef FEMMAINWINDOW_H
#define FEMMAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QMouseEvent>
#include <QKeyEvent>

#include "VTKWidget.h"

//# pragma warning (disable:4819)
//# pragma warning (disable:936)

namespace Ui {
class FEMMainWindow;
}

class FEMMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FEMMainWindow(QWidget *parent = 0);
    ~FEMMainWindow();

private:
    void CreateMenue(void);
    void CreateActions(void );
    void AddActionToMenu(void) const;
    void AddMenueToMBar(void)  const;
    void AddActionToTBar(void) const;

    void ReadPoint(const QString PointLine_) const;                      // 读取节点
    void ReadUnit(const QString) const;                                  // 读取单元
    void ClearUpStore();                                                 // 清理所使用的内存

private:
    // 文件管理菜单
    QMenu*   m_pFileMenue;                                               // 文件控制菜单
    QAction* m_pNewFileAction;                                           // 新建文件
    QAction* m_pOpenFileAction;                                          // 打开文件
    QAction* m_pSaveFileAction;                                          // 保存文件
    QAction* m_pSaveAsAction;                                            // 另存文件

    QMenu*   m_pContralMenu;                                             // 控制菜单
    QAction* m_pContralEdgeShowAction;                                   // 控制网格的显示


private:
    virtual void mouseMoveEvent(QMouseEvent*);                           // 鼠标移动事件
    virtual void mousePressEvent(QMouseEvent*);                          // 鼠标按键按下事件
    virtual void mouseReleaseEvent(QMouseEvent*);                        // 鼠标按键释放按键
    virtual void keyPressEvent(QKeyEvent*);                              // 键盘按键按下事件
    virtual void keyReleaseEvent(QKeyEvent*);                            // 键盘按键释放事件

private slots:
    void OpenSelectFileDialog(bool);
    void ShowOrHideEdge(bool);

private:
    Ui::FEMMainWindow *ui;
};

#endif // FEMMAINWINDOW_H
