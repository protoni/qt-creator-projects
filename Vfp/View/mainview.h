#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>

namespace Ui {
    class MainView;
}

namespace Ps {
    class SetupTab;
    class ControlTab;
    class MainView : public QMainWindow
    {
        Q_OBJECT

    public:
        explicit MainView(QWidget *parent, SetupTab &setup, ControlTab &controlTab);
        ~MainView();

    public slots:
        void onConnected(bool value);

    private slots:
        void on_action_Exit_triggered();

    private:
        SetupTab& m_setupTab;
        ControlTab& m_controlTab;
        Ui::MainView *ui;
    };
}
#endif // MAINVIEW_H
