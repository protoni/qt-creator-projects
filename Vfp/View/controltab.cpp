#include "controltab.h"
#include "ui_controltab.h"
#include <QDebug>
#include "utils.h"

namespace Ps {
    ControlTab::ControlTab(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::ControlTab)
    {
        ui->setupUi(this);
    }

    ControlTab::~ControlTab()
    {
        delete ui;
        Utils::DestructorMsg(this);
    }


    void ControlTab::on_pulseWidth_valueChanged(double value)
    {
        emit NotifyPulseWidthChanged(value);
    }

    void ControlTab::on_pulseDelay_valueChanged(double value)
    {
        emit NotifyPulseDelayChanged(value);
    }

    void ControlTab::on_modulationPulse_toggled(bool toggled)
    {
        emit NotifyModulationPulseChanged(toggled);
    }

    void ControlTab::on_modulationCW_toggled(bool toggled)
    {
        emit NotifyModulationCWChanged(toggled);
    }

    void ControlTab::on_modulationOff_toggled(bool toggled)
    {
        emit NotifyModulationOffChanged(toggled);
    }

    void ControlTab::on_EnableSynth1_stateChanged(int checked)
    {
        emit NotifyEnableSynth1Changed(checked);
    }

    void ControlTab::on_EnableSynth2_stateChanged(int checked)
    {
        emit NotifyEnableSynth2Changed(checked);
    }


}

