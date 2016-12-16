#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "colormap.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

private:
    Ui::MainWindow *ui;
    ColorMap *m_pColorMap;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void changeHue(int nValue);
};

#endif // MAINWINDOW_H
