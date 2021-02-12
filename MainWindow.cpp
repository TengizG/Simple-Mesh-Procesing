#include "MainWindow.h"
#include <qmenubar.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    window = new VTKopenGlWidget(this);
    setCentralWidget(window);
    createActions();
    createMenus();

    resize(600, 400);

}

void MainWindow::createActions()
{
    openAction = new QAction(tr("Open"), this);
    connect(openAction, SIGNAL(triggered()), window, SLOT(loadFile()));

    saveACtion = new QAction(tr("Save"), this);
    connect(saveACtion, SIGNAL(triggered()), window, SLOT(saveFile()));

    decimateAction = new QAction(tr("Decimate"), this);
    connect(decimateAction, SIGNAL(triggered()), window, SLOT(decimate()));
    decimateAction->setEnabled(false);

    subDivAction = new QAction(tr("Sub-Division"), this);
    connect(subDivAction, &QAction::triggered, window, &VTKopenGlWidget::subDivision);
    subDivAction->setEnabled(false);

    connect(window, &VTKopenGlWidget::loaded, this, &MainWindow::updateActions);
}

void MainWindow::createMenus()
{
    mainMenu = menuBar()->addMenu(tr("File"));
    mainMenu->addAction(openAction);
    mainMenu->addAction(saveACtion);

    editMenu = menuBar()->addMenu(tr("Edit"));
    editMenu->addAction(decimateAction);
    editMenu->addAction(subDivAction);
}

void MainWindow::updateActions()
{
    decimateAction->setEnabled(true);
    subDivAction->setEnabled(true);
}
