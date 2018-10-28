#include "mainview.h"
#include "ui_mainview.h"
#include "View/setuptab.h"
#include "View/controltab.h"
#include <QDebug>


namespace Ps {
    MainView::MainView(QWidget *parent, SetupTab& setup, ControlTab& controlTab) :
        QMainWindow(parent),
        m_setupTab(setup),
        m_controlTab(controlTab),
        ui(new Ui::MainView)
    {
        ui->setupUi(this);
        m_setupTab.setParent(this);
        m_controlTab.setParent(this);

        ui->loSetupTab->addWidget(&m_setupTab);
        ui->loControlTab->addWidget(&m_controlTab);
        MainView::onConnected(false);

    }

    MainView::~MainView()
    {
        delete ui;
    }

    void MainView::onConnected(bool value)
    {
        ui->tabControl->setEnabled(value);
    }

}

void Ps::MainView::on_action_Exit_triggered()
{
    QApplication::quit();
}
