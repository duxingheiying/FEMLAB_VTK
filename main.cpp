#include "FEMMainWindow.h"
#include <QApplication>
#include <QTextCodec>

#include "vtkAutoInit.h"

#ifndef INITIAL_OPENGL
#define INITIAL_OPENGL
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)
#endif


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 解决乱问题
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
    FEMMainWindow w;
    w.show();

    return a.exec();
}
