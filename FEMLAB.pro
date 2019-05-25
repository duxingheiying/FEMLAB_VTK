#-------------------------------------------------
#
# Project created by QtCreator 2017-08-09T14:56:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   = FEMLAB
TEMPLATE = app
RC_FILE  = myapp.rc

#QMAKE_CXXFLAGS += -std=c++14

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# 引用的VTK头文件所在位置
INCLUDEPATH += "D:\Program Files\VTK\include\vtk-8.0"

# 引用的VTK的静态链接库所在位置
LIBS += -l"D:/Program Files/VTK/lib/vtkCommonCore-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkalglib-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkChartsCore-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkCommonColor-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkCommonComputationalGeometry-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkCommonDataModel-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkCommonExecutionModel-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkCommonMath-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkCommonMisc-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkCommonSystem-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkCommonTransforms-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkDICOMParser-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkDomainsChemistry-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkDomainsChemistryOpenGL2-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkexoIIc-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkexpat-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkFiltersAMR-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkFiltersCore-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkFiltersExtraction-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkFiltersFlowPaths-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkFiltersGeneral-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkFiltersGeneric-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkFiltersGeometry-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkFiltersHybrid-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkFiltersHyperTree-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkFiltersImaging-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkFiltersModeling-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkFiltersParallel-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkFiltersParallelImaging-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkFiltersPoints-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkFiltersProgrammable-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkFiltersSelection-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkFiltersSMP-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkFiltersSources-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkFiltersStatistics-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkFiltersTexture-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkFiltersTopology-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkFiltersVerdict-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkfreetype-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkGeovisCore-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkgl2ps-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkglew-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkGUISupportQt-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkGUISupportQtSQL-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkhdf5-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkhdf5_hl-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkImagingColor-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkImagingCore-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkImagingFourier-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkImagingGeneral-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkImagingHybrid-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkImagingMath-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkImagingMorphological-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkImagingSources-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkImagingStatistics-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkImagingStencil-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkInfovisCore-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkInfovisLayout-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkInteractionImage-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkInteractionStyle-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkInteractionWidgets-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkIOAMR-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkIOCore-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkIOEnSight-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkIOExodus-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkIOExport-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkIOExportOpenGL2-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkIOGeometry-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkIOImage-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkIOImport-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkIOInfovis-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkIOLegacy-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkIOLSDyna-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkIOMINC-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkIOMovie-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkIONetCDF-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkIOParallel-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkIOParallelXML-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkIOPLY-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkIOSQL-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkIOTecplotTable-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkIOVideo-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkIOXML-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkIOXMLParser-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkjpeg-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkjsoncpp-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtklibharu-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtklibxml2-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtklz4-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkmetaio-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkNetCDF-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtknetcdf_c++"
LIBS += -l"D:/Program Files/VTK/lib/vtkoggtheora-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkParallelCore-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkpng-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkproj4-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkRenderingAnnotation-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkRenderingContext2D-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkRenderingContextOpenGL2-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkRenderingCore-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkRenderingFreeType-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkRenderingGL2PSOpenGL2-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkRenderingImage-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkRenderingLabel-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkRenderingLOD-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkRenderingOpenGL2-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkRenderingQt-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkRenderingVolume-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkRenderingVolumeOpenGL2-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtksqlite-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtksys-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkTestingGenericBridge-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkTestingIOSQL-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkTestingRendering-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtktiff-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkverdict-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkViewsContext2D-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkViewsCore-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkViewsInfovis-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkViewsQt-8.0"
LIBS += -l"D:/Program Files/VTK/lib/vtkzlib-8.0"

SOURCES += main.cpp \
    FEMMainWindow.cpp \
    VTKWidget.cpp \
    BaseGraphic.cpp \
    GlobalVariable.cpp

HEADERS  += \
    FEMMainWindow.h \
    VTKWidget.h \
    BaseGraphic.h \
    Vector3D.h \
    GlobalVariable.h

FORMS    += \
    FEMMainWindow.ui

DISTFILES += \
    myapp.rc

RESOURCES += \
    actions.qrc
