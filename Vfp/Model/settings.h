#ifndef SETTINGS_H
#define SETTINGS_H
#include <QObject>



class QString;
class QStringListModel;
class QJsonParseError;
class QJsonObject;
class QFile;
class QDir;

namespace Ps {

    typedef std::pair<QJsonObject, QJsonParseError> JsonObjErrPair;

    class Settings : public QObject
    {
        Q_OBJECT
    public:
        explicit Settings(QObject *parent, QString filename);
        void ParseJsonData();
        QString getApplicationName() const {return m_applicationName;}
        QString getAppShortName() const {return m_appShortName;}
        QString getHostName() const {return m_hostName;}
        int getPortNumber() const {return m_portNumber;}
        int getShortWaitMs() const {return m_shortWaitMs;}
        int getLongWaitMs() const {return m_longWaitMs;}
        QStringListModel& getCommandsAsModel() const {return m_modelCommands;}
        QString getPulseWidthCommand() const {return m_pulseWidthCommand;}
        QString getPulseDelayCommand() const {return m_pulseDelayCommand;}
        QString getModCommand() const {return m_modCommand;}
        QString getEnableSynthdCommand() const {return m_enableSynthCommand;}

        QString GetCommands(int cmdIndex);
    signals:
        void NotifyStatusMessage(QString message);

    private:
        QString m_filename;
        QString m_applicationName;
        QString m_appShortName;
        QString m_hostName;
        int m_portNumber;
        int m_longWaitMs;
        int m_shortWaitMs;
        QStringListModel& m_modelCommands;
        QString m_pulseWidthCommand;
        QString m_pulseDelayCommand;
        QString m_modCommand;
        QString m_enableSynthCommand;

        QStringList m_cmd_list;
        QString ReadJsonFile();
        QString ReadJsonFromInternalResource();

        void SendErrorMessage(const QString &msg);
        JsonObjErrPair GetJsonObject(const QString &rawJson);

        void SetupCommands(QJsonObject json_obj);
        void ShowJsonParseError(QJsonParseError jsonError);

        QDir OpenConfigurationDirectory();
        void WriteDefaultsToStdConfigFile(QFile &stdConfigFile, const QString &settings);

        explicit Settings(const Settings& rhs) = delete;
        Settings& operator= (const Settings& rhs) = delete;


    };
}

#endif // SETTINGS_H


