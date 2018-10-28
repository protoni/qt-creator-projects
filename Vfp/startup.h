#ifndef STARTUP_H
#define STARTUP_H
#include <QObject>


namespace Ps {
    class MainView;
    class SetupTab;
    class ControlTab;
    class Instrument;
    class SetupViewManager;
    class ControlViewManager;

    class Startup final : public QObject
    {
        Q_OBJECT
    public:
        explicit Startup();
        void show() const;

        ~Startup();
    private:
        SetupTab& m_setupTab;
        ControlTab& m_controlTab;
        MainView& m_mainView;
        Instrument* m_instrument;
        SetupViewManager* m_setupVm;
        ControlViewManager *m_controlVm;
        explicit Startup(const Startup& rhs) = delete;
        Startup& operator= (const Startup& rhs) = delete;
    };
}
#endif
