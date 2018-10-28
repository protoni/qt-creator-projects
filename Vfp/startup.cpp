#include "startup.h"
#include "View/setuptab.h"
#include "View/controltab.h"
#include "View/mainview.h"
#include "utils.h"
#include "Model/settings.h"
#include "Model/provider.h"
#include "Model/instsocket.h"
#include "Model/instrument.h"
#include "ViewMgr/setupviewmanager.h"
#include "ViewMgr/controlviewmanager.h"

namespace Ps {

    Startup::Startup() :
        QObject(nullptr),
      m_setupTab(*new SetupTab(nullptr)),
      m_controlTab(*new ControlTab(nullptr)),
      m_mainView(*new MainView(nullptr, m_setupTab, m_controlTab)),
      m_instrument(new Instrument(this,
                                  *new InstSocket(this))),
      m_setupVm(new SetupViewManager(this, m_setupTab,
                                     *m_instrument,
                                     Provider::GetSettingsAsSingleton())),
      m_controlVm(new ControlViewManager(this, m_controlTab,
                                         *m_instrument,
                                         Provider::GetSettingsAsSingleton(),
                                         m_mainView))
    {
        Settings& my_settings = Provider::GetSettingsAsSingleton();
        my_settings.ParseJsonData();
    }

    Startup::~Startup()
    {
        Utils::DestructorMsg(this);
        delete &m_mainView;
    }

    void Startup::show() const
    {
        m_mainView.show();
    }
}
