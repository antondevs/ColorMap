#ifndef COLORMAP_H
#define COLORMAP_H

#define COLOR_COUNT     16

struct Color
{
    unsigned char nR, nG, nB;         // Color components RGB

    Color()
    {
        nR = nG = nB = 255;
    };
};

struct ColorSlot
{
    float fHueAngle;        // Hue angle
    Color aTable[15];       // Color table array

    ColorSlot()
    {
        fHueAngle = 0.0f;
    };
};

class ColorMap
{
private:
    // Plus 1 - for black&gray&white
    ColorSlot m_aSlots[COLOR_COUNT + 1];
    void UpdateColor(Color &cColor, float fHueAngle, float fSaturation, float fBrightness);

public:
    ColorMap();
    ~ColorMap();

    void Reset();
    void UpdateSlot(int nIndex, float fHueAngle);
    ColorSlot *GetSlot(int nIndex);
};

#endif // COLORMAP_H
