#include "instrument.h"
#include "Model/instsocket.h"
#include "../utils.h"
#include <QDebug>
#include <Model/settings.h>
#include <Model/provider.h>

namespace Ps {
    Ps::Instrument::Instrument(QObject *parent, InstSocket &sock) :
        QObject(parent),
        m_instSocket(sock),
        m_lastCommandSent(),
        m_settings(Provider::GetSettingsAsSingleton())
    {
        WireConnections();
    }
    Instrument::~Instrument()
    {
        Utils::DestructorMsg(this);
    }

    void Instrument::WireConnections()
    {
        connect(&m_instSocket, &InstSocket::NotifyConnected, this, &Instrument::onConnected);
        connect(&m_instSocket, &InstSocket::NotifyDisconnected, this, &Instrument::onDisconnected);
    }

    void Instrument::SetShortWaitMs(int value)
    {
        m_instSocket.SetShortWaitMs(value);
    }

    void Instrument::SetLongWaitMs(int value)
    {
        m_instSocket.SetLongWaitMs(value);
    }

    void Instrument::onHostNameChanged(const QString &hostName)
    {
        m_instSocket.SetHostName(hostName);
    }

    void Instrument::onPortChanged(quint16 port)
    {
        m_instSocket.SetPort(port);
    }

    void Instrument::Connect()
    {
        Disconnect();
        bool connected = m_instSocket.Connect();
        if(!connected)
        {
            emit NotifyErrorDetected(tr("ERROR: Did not connect to socket"));
        }
    }

    void Instrument::onConnected()
    {
        emit NotifyConnected();
    }

    bool Instrument::IsConnected() const
    {
        return m_instSocket.IsOpen();
    }

    void Instrument::Disconnect() const
    {
        if(m_instSocket.IsOpen())
        {
            m_instSocket.Disconnect();
        }
    }

    void Instrument::onDisconnected()
    {
        emit NotifyDisconnected();
    }

    QString Instrument::GetHostName() const
    {
        return m_instSocket.GetHostName();
    }

    quint16 Instrument::GetPort() const
    {
        return m_instSocket.GetPort();
    }

    void Instrument::onSendRequest(const QString &dataToSend)
    {
        m_lastCommandSent = dataToSend;
        qDebug() << "Instrument read to send data: " << dataToSend;
        m_instSocket.WriteData(dataToSend);
        emit NotifyDataSent(dataToSend);
    }

    void Instrument::onReceiveRequest()
    {
        QString input_buffer = m_instSocket.ReadData();
        if(input_buffer.size() == 0)
        {
            emit NotifyDataReceived("No data received.");
        }
        else
        {
            emit NotifyDataReceived(input_buffer);
        }
    }

    void Instrument::onPulseWidthChanged(double value)
    {
        auto cmd = m_settings.GetCommands(index_pulseWidthCommand);

        QString dataToSend = QString{"%1: %2"}.arg(cmd).arg(value, 3, 'f', 3);
        Instrument::onSendRequest(dataToSend);
    }

    void Instrument::onPulseDelayChanged(double value)
    {
        auto cmd = m_settings.GetCommands(index_pulseDelayCommand);

        QString dataToSend = QString{"%1: %2"}.arg(cmd).arg(value, 3, 'f', 3);
        Instrument::onSendRequest(dataToSend);

    }

    void Instrument::onModulationPulseChanged(bool toggled)
    {
        if(toggled)
        {
            auto cmd = m_settings.GetCommands(index_modCommand);

            QString dataToSend = QString{"%1: Pulse"}.arg(cmd);
            // qDebug() << dataToSend;
            Instrument::onSendRequest(dataToSend);
        }
    }

    void Instrument::onModulationCWChanged(bool toggled)
    {
        if(toggled)
        {
            auto cmd = m_settings.GetCommands(index_modCommand);

            QString dataToSend = QString{"%1: CW"}.arg(cmd);
            Instrument::onSendRequest(dataToSend);
        }
    }

    void Instrument::onModulationOffChanged(bool toggled)
    {
        if(toggled)
        {
            auto cmd = m_settings.GetCommands(index_modCommand);

            QString dataToSend = QString{"%1: Off"}.arg(cmd);
            Instrument::onSendRequest(dataToSend);
        }
    }

    void Instrument::onSynth1Changed(int checked)
    {
        auto cmd = m_settings.GetCommands(index_enableSynthCommand);
        QString dataToSend;
        if(checked)
        {
            dataToSend = QString{"%1 1: On"}.arg(cmd);
        }
        else
        {
            dataToSend = QString{"%1 1: Off"}.arg(cmd);
        }
        Instrument::onSendRequest(dataToSend);
    }

    void Instrument::onSynth2Changed(int checked)
    {
        auto cmd = m_settings.GetCommands(index_enableSynthCommand);
        QString dataToSend;
        if(checked)
        {
            dataToSend = QString{"%1 2: On"}.arg(cmd);
        }
        else
        {
            dataToSend = QString{"%1 2: Off"}.arg(cmd);
        }
        Instrument::onSendRequest(dataToSend);
    }
}
