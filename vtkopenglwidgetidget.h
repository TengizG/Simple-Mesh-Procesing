#ifndef VTKOPENGLWIDGET_H
#define VTKOPENGLWIDGET_H

#include <QVTKOpenGLStereoWidget.h>
#include <vtkSmartPointer.h>
#include <vtkOBJReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <QVTKInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkPolyData.h>
#include <vtkQuadricDecimation.h>


class VTKopenGlWidget : public QVTKOpenGLStereoWidget
{
	Q_OBJECT
public:
	VTKopenGlWidget(QWidget* parent = nullptr);

	QString getFileName() const { return openFileName; }
	void setFileName(QString fileName) { this->openFileName = fileName; }
	void loadModel();

public slots:
	void loadFile();
	void saveFile();
	void decimate();
	void subDivision();

signals:
	void loaded();

private:
	vtkSmartPointer<vtkOBJReader> objFile;
	vtkSmartPointer<vtkPolyDataMapper> maper;
	vtkSmartPointer<vtkActor> actor;
	vtkSmartPointer<vtkRenderer> renderer;
	vtkSmartPointer<vtkGenericOpenGLRenderWindow> win;
	vtkSmartPointer<QVTKInteractor> interactor;
	vtkSmartPointer<vtkInteractorStyleTrackballCamera> interactorStyle;
	vtkSmartPointer<vtkPolyData> rawData;
	vtkSmartPointer<vtkQuadricDecimation> decimation;
	
	QString openFileName;
	QString savedFileName;
};

#endif // !VTKOPENGLWIDGET_H
