#include "controlviewmanager.h"
#include "View/controltab.h"
#include "Model/instrument.h"
#include "View/mainview.h"
#include "utils.h"

namespace Ps {
    ControlViewManager::ControlViewManager(QObject *parent,
                                           ControlTab &control,
                                           Instrument &inst,
                                           Settings &config,
                                           MainView &mainView) :
        QObject(parent),
        m_controlTab(control),
        m_instrument(inst),
        m_mainView(mainView)
    {
        WireControls();
        WireDisplayUpdate();

    }

    ControlViewManager::~ControlViewManager()
    {
        Utils::DestructorMsg(this);
    }

    void ControlViewManager::onConnected()
    {
        emit NotifyControlTabEnabled(true);
    }

    void ControlViewManager::onDisconnected()
    {
        emit NotifyControlTabEnabled(false);
    }

    void ControlViewManager::WireControls()
    {
        // Pulse Settings
        connect(&m_controlTab, &ControlTab::NotifyPulseWidthChanged,
                &m_instrument, &Instrument::onPulseWidthChanged);
        connect(&m_controlTab, &ControlTab::NotifyPulseDelayChanged,
                &m_instrument, &Instrument::onPulseDelayChanged);

        // Modulation Settings

        connect(&m_controlTab, &ControlTab::NotifyModulationPulseChanged,
                &m_instrument, &Instrument::onModulationPulseChanged);

        connect(&m_controlTab, &ControlTab::NotifyModulationCWChanged,
                &m_instrument, &Instrument::onModulationCWChanged);

        connect(&m_controlTab, &ControlTab::NotifyModulationOffChanged,
                &m_instrument, &Instrument::onModulationOffChanged);

        // Synth Settings
        connect(&m_controlTab, &ControlTab::NotifyEnableSynth1Changed,
                &m_instrument, &Instrument::onSynth1Changed);

        connect(&m_controlTab, &ControlTab::NotifyEnableSynth2Changed,
                &m_instrument, &Instrument::onSynth2Changed);

    }


    void ControlViewManager::WireDisplayUpdate()
    {
        // Control tab
        connect(&m_instrument, &Instrument::NotifyConnected,
                this, &ControlViewManager::onConnected);
        connect(&m_instrument, &Instrument::NotifyDisconnected,
                this, &ControlViewManager::onDisconnected);

        connect(this, &ControlViewManager::NotifyControlTabEnabled,
                &m_mainView, &MainView::onConnected);

    }


}
