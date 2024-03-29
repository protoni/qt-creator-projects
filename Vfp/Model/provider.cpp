#include "provider.h"
#include "Model/settings.h"
#include <QString>
#include "utils.h"

namespace Ps {
    static QString SETTINGS_FILE = QStringLiteral("settings.json");
    std::unique_ptr<Settings> Provider::m_instanceSettings = nullptr;

    //Provider::Provider() :
    //{
    //}

    Settings& Provider::GetSettingsAsSingleton()
    {
        if(m_instanceSettings == nullptr)
        {
            m_instanceSettings = Utils::make_unique<Settings>(nullptr, SETTINGS_FILE);
        }

        return *m_instanceSettings;
    }

}
