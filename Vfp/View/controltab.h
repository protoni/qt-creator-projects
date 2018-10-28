#ifndef CONTROLTAB_H
#define CONTROLTAB_H

#include <QWidget>

namespace Ui {
    class ControlTab;
}

namespace Ps {
    class ControlTab : public QWidget
    {
        Q_OBJECT

    public:
        explicit ControlTab(QWidget *parent = nullptr);
        ~ControlTab();

    signals:
        void NotifyPulseWidthChanged(double value);
        void NotifyPulseDelayChanged(double value);
        void NotifyModulationPulseChanged(double value);
        void NotifyModulationCWChanged(double value);
        void NotifyModulationOffChanged(double value);
        void NotifyEnableSynth1Changed(int checked);
        void NotifyEnableSynth2Changed(int checked);

    private slots:
        void on_pulseWidth_valueChanged(double value);
        void on_pulseDelay_valueChanged(double value);
        void on_modulationPulse_toggled(bool toggled);
        void on_modulationCW_toggled(bool toggled);
        void on_modulationOff_toggled(bool toggled);
        void on_EnableSynth1_stateChanged(int checked);
        void on_EnableSynth2_stateChanged(int checked);

    private:
        Ui::ControlTab *ui;

    };
}
#endif // CONTROLTAB_H
