#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QWidget>
#include <QMouseEvent>
#include "colormap.h"

class MapView : public QWidget
{
Q_OBJECT

public:
    explicit MapView(QWidget *parent = 0);
    ~MapView();

    void SetColorMap(ColorMap *pColorMap);
    void SetSelected(int nIndex);
    int GetSelected();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void selectedChanged(int nIndex);


private:
    int m_nSelected;
    ColorMap *m_pColorMap;
    QRect GetItemRect(int nIndex);

};

#endif // MAPVIEW_H
