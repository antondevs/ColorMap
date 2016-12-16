#include "mapview.h"
#include <QPainter>

MapView::MapView(QWidget *parent) : QWidget(parent)
{
    m_nSelected = 0;
    m_pColorMap = NULL;
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setMouseTracking(true);
}

MapView::~MapView()
{

}

void MapView::SetSelected(int nIndex)
{
    if (nIndex >= 0 && nIndex < COLOR_COUNT)
    {
        m_nSelected = nIndex;
        repaint();
        selectedChanged(nIndex);
    }
}

int MapView::GetSelected()
{
    return m_nSelected;
}

void MapView::mousePressEvent(QMouseEvent *event)
{
    for (int i = 0; i < 16; i++)
    {
        QRect rect = GetItemRect(i);

        if (rect.contains(event->pos()))
        {
            SetSelected(i);
            break;
        }
    }
}

void MapView::SetColorMap(ColorMap *pColorMap)
{
    m_pColorMap = pColorMap;
    repaint();
}

void MapView::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    // Current version support only 16 slots
    if (COLOR_COUNT != 16 || !m_pColorMap)
        return;

    for (int i = 0; i < 16; i++)
    {
        QRect rect = GetItemRect(i);

        int nRow = 1;
        int nIndex = 0;
        int nSize = rect.width() / 5;

        ColorSlot *pSlot = m_pColorMap->GetSlot(i);

        if (!pSlot)
            continue;

        if (m_nSelected == i)
        {
            // Draw selected arrow
            painter.fillRect(QRect(rect.left(), rect.top(), 5, 5), Qt::red);
            painter.fillRect(QRect(rect.left() + 5, rect.top() + 5, 5, 5), Qt::red);
            painter.fillRect(QRect(rect.left() + 10, rect.top() + 10, 5, 5), Qt::red);

        }

        for (int q = 0; q < 15; q++)
        {
            int nRowWidth = nRow * nSize;
            QRect boxRect(rect.left() + nSize * 2.5f - nRowWidth / 2.0f + (nIndex * nSize),
                          rect.top() + (nRow - 1) * nSize,
                          nSize,
                          nSize);

            QBrush brush(QColor(pSlot->aTable[q].nR, pSlot->aTable[q].nG, pSlot->aTable[q].nB));
            painter.fillRect(boxRect, brush);

            nIndex++;

            if (nIndex >= nRow)
            {
                nIndex = 0;
                nRow++;
            }
        }
    }
}

QRect MapView::GetItemRect(int nIndex)
{
    if (nIndex >= 0 && nIndex < 16)
    {
        // 10 pixels between triangles
        int nSpace = 10;
        int nBoxSize = width() > height() ? height() : width();
        int nSlotSize = (nBoxSize - (nSpace * 5)) / 4;
        int nY = (int) nIndex / 4;
        int nX = nIndex - nY * 4;
        int nOffset = (width() / 2) - (nSpace + 4 * nSlotSize + 4 * nSpace) / 2;

        return QRect(nOffset + nSpace + nX * nSlotSize + nX * nSpace,
                     nSpace + nY * nSlotSize + nSpace * nY,
                     nSlotSize,
                     nSlotSize);
    }

    return QRect();
}
