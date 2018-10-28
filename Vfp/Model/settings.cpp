#include "settings.h"
#include <QString>
#include <QFile>
#include <QDir>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QStringListModel>
#include <utility>
#include <QMessageBox>
#include <QStandardPaths>

namespace Ps {
    static auto RESOURCE_PREFIX = QStringLiteral(":/json");
    Settings::Settings(QObject *parent, QString filename) :
        QObject(parent),
        m_filename(filename),
        m_modelCommands(*new QStringListModel (this))
    {

    }

    void Settings::ParseJsonData()
    {
        QString raw_json = ReadJsonFile();
        if(raw_json.size() == 0) return;

        auto json_result = GetJsonObject(raw_json);
        auto json_err = json_result.second;
        if(json_err.error != QJsonParseError::NoError)
        {
            ShowJsonParseError(json_err);
        }
        auto json_obj = json_result.first;
        m_applicationName = json_obj["applicationName"].toString();
        m_appShortName = json_obj["appShortName"].toString();
        m_hostName = json_obj["hostName"].toString();
        m_portNumber = json_obj["port"].toInt();
        m_longWaitMs = json_obj["tcpLongWaitMs"].toInt();
        m_shortWaitMs = json_obj["tcpShortWaitMs"].toInt();
        SetupCommands(json_obj);
    }

    QString Settings::ReadJsonFile()
    {
        auto default_settings = ReadJsonFromInternalResource();
        QDir config_dir = OpenConfigurationDirectory();
        auto path = config_dir.filePath(m_filename);

        QFile std_file(path);
        if(std_file.exists())
        {
            if(!std_file.open(QFile::ReadOnly|QFile::Text))
            {
                SendErrorMessage("Could not open " + path);
                return default_settings;
            }
            QString settings = std_file.readAll();
            std_file.close();
            return settings;
        }
        else
        {
            WriteDefaultsToStdConfigFile(std_file, default_settings);
            return default_settings;
        }
    }

    void Settings::WriteDefaultsToStdConfigFile(QFile& stdConfigFile, const QString &settings)
    {
        int length = settings.length();
        if(!stdConfigFile.open(QFile::WriteOnly|QFile::Text))
        {
            SendErrorMessage("Could not open file to write - " + stdConfigFile.fileName());
        }

        auto bytes_written = stdConfigFile.write(qPrintable(settings), length);
        if(bytes_written != length)
        {
            SendErrorMessage("Could not write the settings to -" + stdConfigFile.fileName());
            if(!stdConfigFile.remove())
            {
                SendErrorMessage("Couldn't remove configuration file. Please delete manually:"+
                                 stdConfigFile.fileName());
            }
        }

        stdConfigFile.close();
    }

    QDir Settings::OpenConfigurationDirectory()
    {
        QDir config_dir(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation));
        if(!config_dir.exists())
        {
            QDir dir;
            dir.mkpath(config_dir.path());
        }
        return config_dir;
    }

    void Settings::ShowJsonParseError(QJsonParseError jsonError)
    {
        QString msg = tr("Error parsing Json settings file. \n");
        msg.append(jsonError.errorString());
        QMessageBox::critical(nullptr, tr("VFP"), msg);
    }

    JsonObjErrPair Settings::GetJsonObject(const QString& rawJson)
    {
            QJsonParseError json_parse_error;
            QJsonDocument json_doc = QJsonDocument::fromJson(rawJson.toUtf8(),
                                                             &json_parse_error);

            QJsonObject json_obj = json_doc.object();

            return std::make_pair(json_obj, json_parse_error);
    }

    QString Settings::GetCommands(int cmdIndex)
    {
        QString ret = "";
        auto index = m_modelCommands.index(cmdIndex);
        auto cmd = m_modelCommands.data(index, Qt::DisplayRole);


        if(cmdIndex < m_cmd_list.size())
        {
            ret = cmd.toString();
        }
        else
        {
            ret = "";
            emit NotifyStatusMessage("Unable to get command name");
        }

        return ret;
    }

    void Settings::SetupCommands(QJsonObject json_obj)
    {
        QJsonArray cmd_array = json_obj["commands"].toArray();

        for (auto item: cmd_array)
        {
            m_cmd_list.append(item.toString());
        }
        m_modelCommands.setStringList(m_cmd_list);

    }

    QString Settings::ReadJsonFromInternalResource()
    {
        QDir res_dir(RESOURCE_PREFIX);
        if(!res_dir.exists())
        {
            SendErrorMessage("Internal resource path missing " +
                             res_dir.canonicalPath());
            return "";
        }
        auto path = res_dir.filePath(m_filename);
        QFile res_file(path);
        if(!res_file.open(QFile::ReadOnly | QFile::Text))
        {
            SendErrorMessage("Internal resource path missing " +
                             path);
            return "";
        }
        QString settings = res_file.readAll();

        return settings;
    }

    void Settings::SendErrorMessage(const QString& msg)
    {
        emit NotifyStatusMessage(msg);
    }

}
