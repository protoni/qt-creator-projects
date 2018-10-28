#ifndef SETUPVIEWMANAGER_H
#define SETUPVIEWMANAGER_H
#include <QObject>

namespace Ps {

    class SetupTab;
    class Instrument;
    class Settings;
    class SetupViewManager : public QObject
    {
        Q_OBJECT

    public:
        explicit SetupViewManager(QObject *parent, SetupTab& tab,
                                  Instrument& inst, Settings& config);

        ~SetupViewManager();

    signals:
        void NotifyStatusUpdated(const QString& value);
        void NotifyConnectEnabled(bool value);
        void NotifyDisconnectEnabled(bool value);
        void NotifyDirectCommandsEnabled(bool value);


    private slots:
        void onConnected();
        void onDisconnected();

    private:
        SetupTab& m_setupTab;
        Instrument& m_instrument;
        explicit SetupViewManager(const SetupViewManager& rhs) = delete;
        SetupViewManager& operator= (const SetupViewManager& rhs) = delete;
        void WireSettings(Settings &config);
        void WireHostAndPort();
        void WireMessages();
        void WireButtons();
        void WireDisplayUpdate();

    };
#endif // SETUPVIEWMANAGER_H


}
