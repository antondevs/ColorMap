#include "colormap.h"
#include <QtCore/qmath.h>

ColorMap::ColorMap()
{
    float fSlotRange = (int) (360.0 / COLOR_COUNT);

    // Init default color table
    for (int i = 0; i < COLOR_COUNT; i++)
    {
        UpdateSlot(i, fSlotRange * i );
    }
}

ColorMap::~ColorMap()
{

}

ColorSlot *ColorMap::GetSlot(int nIndex)
{
    if (nIndex >= 0 && nIndex < COLOR_COUNT)
    {
        return &m_aSlots[nIndex];
    }

    return nullptr;
}

void ColorMap::UpdateColor(Color &cColor, float fHueAngle, float fSaturation, float fBrightness)
{
    double r = 0, g = 0, b = 0;

    if (fSaturation == 0)
    {
        r = fBrightness;
        g = fBrightness;
        b = fBrightness;
    }
    else
    {
        int i;
        double f, p, q, t;

        if (fHueAngle == 360)
            fHueAngle = 0;
        else
            fHueAngle = fHueAngle / 60;

        i = (int)trunc(fHueAngle);
        f = fHueAngle - i;

        p = fBrightness * (1.0 - fSaturation);
        q = fBrightness * (1.0 - (fSaturation * f));
        t = fBrightness * (1.0 - (fSaturation * (1.0 - f)));

        switch (i)
        {
        case 0:
            r = fBrightness;
            g = t;
            b = p;
            break;

        case 1:
            r = q;
            g = fBrightness;
            b = p;
            break;

        case 2:
            r = p;
            g = fBrightness;
            b = t;
            break;

        case 3:
            r = p;
            g = q;
            b = fBrightness;
            break;

        case 4:
            r = t;
            g = p;
            b = fBrightness;
            break;

        default:
            r = fBrightness;
            g = p;
            b = q;
            break;
        }

    }

    cColor.nR = (unsigned char)(r * 255);
    cColor.nG = (unsigned char)(g * 255);
    cColor.nB = (unsigned char)(b * 255);
}

void ColorMap::UpdateSlot(int nIndex, float fHueAngle)
{
    // Saturation & Brightness values: 100%, 80%, 60%, 40%, 20%
    int nRange[5] = { 255, 204, 153, 102, 51 };

    if (nIndex >= 0 && nIndex < COLOR_COUNT)
    {
        m_aSlots[nIndex].fHueAngle = fHueAngle;

        // Color triangle matrix

        UpdateColor(m_aSlots[nIndex].aTable[0], fHueAngle, 0.6f, 0.2f);       // Row1

        UpdateColor(m_aSlots[nIndex].aTable[1], fHueAngle, 0.8f, 0.4f);       // Row2
        UpdateColor(m_aSlots[nIndex].aTable[2], fHueAngle, 0.6f, 0.4f);       // Row2

        UpdateColor(m_aSlots[nIndex].aTable[3], fHueAngle, 0.4f, 0.6f);       // Row3
        UpdateColor(m_aSlots[nIndex].aTable[4], fHueAngle, 0.6f, 0.6f);       // Row3
        UpdateColor(m_aSlots[nIndex].aTable[5], fHueAngle, 0.8f, 0.6f);       // Row3

        UpdateColor(m_aSlots[nIndex].aTable[6], fHueAngle, 0.2f, 0.8f);       // Row4
        UpdateColor(m_aSlots[nIndex].aTable[7], fHueAngle, 0.4f, 0.8f);       // Row4
        UpdateColor(m_aSlots[nIndex].aTable[8], fHueAngle, 0.6f, 0.8f);       // Row4
        UpdateColor(m_aSlots[nIndex].aTable[9], fHueAngle, 0.8f, 0.8f);       // Row4

        UpdateColor(m_aSlots[nIndex].aTable[10], fHueAngle, 0.2f, 1.0f);      // Row5
        UpdateColor(m_aSlots[nIndex].aTable[11], fHueAngle, 0.4f, 1.0f);      // Row5
        UpdateColor(m_aSlots[nIndex].aTable[12], fHueAngle, 0.6f, 1.0f);      // Row5
        UpdateColor(m_aSlots[nIndex].aTable[13], fHueAngle, 0.8f, 1.0f);      // Row5
        UpdateColor(m_aSlots[nIndex].aTable[14], fHueAngle, 1.0f, 1.0f);      // Row5
    }
}
