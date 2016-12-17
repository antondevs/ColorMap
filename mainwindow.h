#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "colormap.h"
#include "mapview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

private:
    Ui::MainWindow *ui;
    ColorMap *m_pColorMap;
    MapView *m_pMapView;
    QString m_szFileName;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void changeHue(int nValue);

private slots:
    void on_actionNewMap_triggered();
    void on_actionOpenMap_triggered();
    void on_actionSaveMap_triggered();
    void on_actionExport_triggered();
};

#endif // MAINWINDOW_H
