#ifndef INSTRUMENT_H
#define INSTRUMENT_H
#include <QObject>

#define index_pulseWidthCommand  5
#define index_pulseDelayCommand  6
#define index_modCommand         7
#define index_enableSynthCommand 8

namespace Ps {

    class InstSocket;
    class Settings;
    class Provider;
    class Instrument :public QObject
    {
        Q_OBJECT
    public:
        explicit Instrument(QObject *parent, InstSocket &sock);
        virtual ~Instrument();
        void Connect();
        void Disconnect() const;
        bool IsConnected() const;
        QString GetHostName() const;
        quint16 GetPort() const;
        void SetLongWaitMs(int value);
        void SetShortWaitMs(int value);

    signals:
        void NotifyConnected();
        void NotifyDisconnected();
        void NotifyDataSent(const QString& dataSent);
        void NotifyDataReceived(const QString& readData);
        void NotifyErrorDetected(const QString& errorMsg);
        void NotifyStatusUpdated(const QString& statusMsg);

    public slots:
        void onHostNameChanged(const QString& hostName);
        void onPortChanged(quint16 port);
        void onConnected();
        void onDisconnected();
        void onSendRequest(const QString& dataToSend);
        void onReceiveRequest();
        void onPulseWidthChanged(double value);
        void onPulseDelayChanged(double value);
        void onModulationPulseChanged(bool toggled);
        void onModulationCWChanged(bool toggled);
        void onModulationOffChanged(bool toggled);
        void onSynth1Changed(int checked);
        void onSynth2Changed(int checked);

    private:
        InstSocket& m_instSocket;
        QString m_lastCommandSent;
        Settings& m_settings;

        void WireConnections();
        explicit Instrument(const Instrument& rhs) = delete;
        Instrument& operator= (const Instrument& rhs) = delete;
    };
#endif // INSTRUMENT_H

}
