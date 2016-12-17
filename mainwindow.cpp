#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);    
    m_pColorMap = new ColorMap();

    m_szFileName = "";
    m_pMapView = findChild<MapView *>("mapview");
    m_pMapView->SetColorMap(m_pColorMap);
}

MainWindow::~MainWindow()
{
    delete ui;

    if (m_pColorMap)
        delete m_pColorMap;
}

void MainWindow::changeHue(int nValue)
{
    int nSelected = m_pMapView->GetSelected();

    if (nSelected >= 0)
    {
        m_pColorMap->UpdateSlot(nSelected, nValue);
    }

    m_pMapView->repaint();
}

void MainWindow::on_actionNewMap_triggered()
{
    m_szFileName = "";
    m_pColorMap->Reset();
    m_pMapView->SetSelected(0);
    m_pMapView->repaint();
}

void MainWindow::on_actionOpenMap_triggered()
{
    m_szFileName = QFileDialog::getOpenFileName(this,
                                   tr("Open Project"), ".",
                                   tr("ColorMap project (*.cmp)"));

    QFile file(m_szFileName);

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        return;
    }

    QXmlStreamReader xmlReader(&file);
    xmlReader.readNext();

    int nIndex = 0;

    while(!xmlReader.atEnd())
    {
        if(xmlReader.isStartElement())
        {
            if(xmlReader.name() == "colormap")
            {
               xmlReader.readNext();
            }
            else if(xmlReader.name() == "hue")
            {
                QString value = xmlReader.readElementText();
                m_pColorMap->GetSlot(nIndex)->fHueAngle = value.toFloat();
                nIndex++;

                if (nIndex >= COLOR_COUNT)
                    break;
            }
        }
        else
        {
            xmlReader.readNext();
        }
    }

    file.close();

    m_pMapView->SetSelected(0);
    m_pMapView->repaint();
}

void MainWindow::on_actionSaveMap_triggered()
{
    m_szFileName = QFileDialog::getSaveFileName(this,
                                           tr("Save Project"), ".",
                                           tr("ColorMap project (*.cmp)"));

    if (m_szFileName == "")
        return;

    QFile file(m_szFileName);
    file.open(QIODevice::WriteOnly);

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("colormap");

    for (int i = 0; i < COLOR_COUNT; i++)
    {
        ColorSlot *pSlot = m_pColorMap->GetSlot(i);
        xmlWriter.writeTextElement("hue", QString::number(pSlot->fHueAngle));
    }

    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();

    file.close();
}

void MainWindow::on_actionExport_triggered()
{
    QString szFileName = QFileDialog::getSaveFileName(this,
                                           tr("Export Project"), ".",
                                           tr("json format (*.json)"));

    if (szFileName == "")
        return;

    QFile file(szFileName);

    if (!file.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }

    QJsonArray groups;

    for (int i = 0; i <= COLOR_COUNT; i++)
    {
        QJsonObject group;
        QJsonArray colors;

        ColorSlot *pSlot = m_pColorMap->GetSlot(i);

        for (int q = 0; q < 15; q++)
        {
            QJsonObject color;

            if (pSlot)
            {
                color["r"] = pSlot->aTable[q].nR;
                color["g"] = pSlot->aTable[q].nG;
                color["b"] = pSlot->aTable[q].nB;
            }

            colors.append(color);
        }

        group["index"] = i + 1;
        group["colors"] = colors;


        groups.append(group);
    }

    QJsonObject object;
    object["groups"] = groups;

    QJsonDocument saveDoc(object);
    file.write(saveDoc.toJson());
}
