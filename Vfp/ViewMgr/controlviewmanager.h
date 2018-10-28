#ifndef CONTROLVIEWMANAGER_H
#define CONTROLVIEWMANAGER_H
#include <QObject>

namespace Ps {
    class ControlTab;
    class Instrument;
    class Settings;
    class MainView;
    class ControlViewManager : public QObject
    {
        Q_OBJECT
    public:
        explicit ControlViewManager(QObject *parent, ControlTab& control,
                                    Instrument& inst, Settings& config,
                                    MainView &mainView);


    ~ControlViewManager();

    signals:
        void NotifyConnectEnabled(bool value);
        void NotifyDisconnectEnabled(bool value);
        void NotifyControlTabEnabled(bool value);

    private slots:
        void onConnected();
        void onDisconnected();

    private:
        ControlTab& m_controlTab;
        Instrument& m_instrument;
        MainView& m_mainView;
        explicit ControlViewManager(const ControlViewManager& rhs) = delete;
        ControlViewManager& operator= (const ControlViewManager& rhs) = delete;
        void WireControls();
        void WireDisplayUpdate();
    };
}
#endif // CONTROLVIEWMANAGER_H


