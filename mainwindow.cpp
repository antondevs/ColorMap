#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);    
    m_pColorMap = new ColorMap();

    MapView *pMapView = findChild<MapView *>("mapview");

    if (pMapView)
        pMapView->SetColorMap(m_pColorMap);
}

MainWindow::~MainWindow()
{
    delete ui;

    if (m_pColorMap)
        delete m_pColorMap;
}

void MainWindow::changeHue(int nValue)
{
    MapView *pMapView = findChild<MapView *>("mapview");

    if (pMapView)
    {
        int nSelected = pMapView->GetSelected();

        if (nSelected >= 0)
        {
            m_pColorMap->UpdateSlot(nSelected, nValue);
        }

        pMapView->repaint();
    }
}
