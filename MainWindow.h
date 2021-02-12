#include <QtWidgets/QMainWindow>

#include "vtkopenglwidgetidget.h"
#include <qmenu.h>
#include <qaction.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);
    void createActions();
    void createMenus();

public slots:
    void updateActions();

private:
    QMenu* mainMenu;
    QMenu* editMenu;
    QAction* openAction;
    QAction* saveACtion;
    QAction* decimateAction;
    QAction* subDivAction;
    VTKopenGlWidget* window;
};
