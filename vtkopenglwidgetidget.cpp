#include "vtkopenglwidgetidget.h"
#include <qfiledialog.h>
#include <vtkTriangleFilter.h>
#include <vtkProperty.h>
#include <vtkLinearSubdivisionFilter.h>
#include <vtkOBJWriter.h>


VTKopenGlWidget::VTKopenGlWidget(QWidget* parent)
	: QVTKOpenGLStereoWidget(parent)
{
	maper = vtkSmartPointer<vtkPolyDataMapper>::New();
	actor = vtkSmartPointer<vtkActor>::New();
	renderer = vtkSmartPointer<vtkRenderer>::New();
	win = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
	interactor = vtkSmartPointer<QVTKInteractor>::New();
	interactorStyle = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();

	win->AddRenderer(renderer);
	SetRenderWindow(win);
	interactor->SetInteractorStyle(interactorStyle);
	interactor->Initialize();
	interactor->SetRenderWindow(win);
	
}

void VTKopenGlWidget::loadFile()
{
	openFileName = QFileDialog::getOpenFileName(this, tr("Chose File"), QDir::currentPath(),
		tr("OBJ File (*.obj)"));

	if (openFileName.isEmpty())
		return;
	objFile = vtkSmartPointer<vtkOBJReader>::New();
	objFile->SetFileName(openFileName.toUtf8().constData());
	objFile->Update();

	vtkSmartPointer<vtkTriangleFilter> tringels =
		vtkSmartPointer<vtkTriangleFilter>::New();
	tringels->SetInputConnection(objFile->GetOutputPort());
	tringels->Update();


	rawData = tringels->GetOutput();

	loadModel();

	emit loaded();
}

void VTKopenGlWidget::loadModel()
{
	
	maper->SetInputData(rawData);
	actor->SetMapper(maper);
	renderer->AddActor(actor);
	renderer->ResetCamera();
	win->Render();
}

void VTKopenGlWidget::saveFile()
{
	savedFileName = QFileDialog::getSaveFileName(this, tr("SaveFile As"),
		QDir::currentPath(), tr("OBJ Fle (*.obj)"));
	vtkSmartPointer<vtkOBJWriter> exporter = vtkSmartPointer<vtkOBJWriter>::New();
	exporter->SetInputData(rawData);
	exporter->SetFileName(savedFileName.toUtf8().constData());
	exporter->Write();

}

void VTKopenGlWidget::decimate()
{

	vtkSmartPointer<vtkQuadricDecimation> decimate =
		vtkSmartPointer<vtkQuadricDecimation>::New();
	decimate->SetInputData(rawData);
	decimate->AttributeErrorMetricOn();
	decimate->SetTargetReduction(0.1);
	decimate->VolumePreservationOn();

	decimate->Update();

	rawData->DeepCopy(decimate->GetOutput());
	win->Render();
}

void VTKopenGlWidget::subDivision()
{
	int fixPointNumbers = 1000000;
	if (rawData->GetNumberOfPoints() >= fixPointNumbers)
		return;
	vtkSmartPointer<vtkLinearSubdivisionFilter> subDivFilter =
		vtkSmartPointer<vtkLinearSubdivisionFilter>::New();
	subDivFilter->SetInputData(rawData);
	subDivFilter->Update();
	rawData->DeepCopy(subDivFilter->GetOutput());
	win->Render();
}
