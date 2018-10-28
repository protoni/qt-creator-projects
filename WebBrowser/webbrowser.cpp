#include "webbrowser.h"
#include "ui_webbrowser.h"
#include <QString>


WebBrowser::WebBrowser() :
    QMainWindow()

{
    /* Setup Web Browser */

    // Window
    m_tab = new QTabWidget;
    setCentralWidget(m_tab);
    m_tab->addTab(addtab(), "New tab");

    connect(m_tab, SIGNAL(currentChanged(int)), this, SLOT(tabchanged()));
    setWindowTitle("Web Browser");

    // Menu
    m_file=menuBar()->addMenu("File");
    m_file->addAction("New Tab");
    m_file->addAction("New Window");
    m_file->addAction("Save As");
    m_file->addAction("Exit");

    // Toolbar
    m_tools=addToolBar("tools");
    QAction *back=m_tools->addAction("Back");
    connect(back,SIGNAL(triggered(bool)),this,SLOT(S_back()));
    QAction *forward=m_tools->addAction("Forward");
    connect(forward,SIGNAL(triggered(bool)),this,SLOT(S_forward()));
    QAction *newtab=m_tools->addAction("New Tab");
    connect(newtab,SIGNAL(triggered(bool)),this,SLOT(S_addtab()));

    // Url
    m_url.setContentsMargins(50,0,90,0);
    m_tools->addWidget(&m_url);
    QAction *reload=m_tools->addAction("Reload");
    connect(reload,SIGNAL(triggered(bool)),this,SLOT(S_reload()));
    QAction *stop=m_tools->addAction("Stop");
    connect(stop,SIGNAL(triggered(bool)),this,SLOT(S_stop()));
    m_tools->setFixedHeight(40);
    m_tools->setContentsMargins(10,0,20,0);
    connect(&m_url,SIGNAL(returnPressed()),this,SLOT(loadpage()));
}

QWidget *WebBrowser::addtab()
{

    QWidget *window = new QWidget;
    QWebEngineView *webpage = new QWebEngineView;
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(webpage);
    layout->setContentsMargins(0, 0, 0, 0);
    window->setLayout(layout);
    webpage->load(QUrl(m_url.text()));

    connect(webpage, SIGNAL(urlChanged()), this, SLOT(linkchange()));
    m_tab->setCurrentWidget(window);


    qDebug() << "Signal: Add Tab!";
    return window;
}

QWebEngineView *WebBrowser::currentpage()
{
    return m_tab->currentWidget()->findChild<QWebEngineView*>();
}

void WebBrowser::loadpage()
{
    if(m_url.text() != "http://")
    {
        const QString text = m_url.text();
    }

    currentpage()->load(QUrl(m_url.text()));

    m_tab->setTabText(m_tab->currentIndex(), currentpage()->title());
    qDebug() << "Signal: Load Page! Page name: " << currentpage()->title();
}

void WebBrowser::tabchanged()
{


    const QString newlink = currentpage()->url().toString();
    m_url.setText(newlink);
}

void WebBrowser::linkchange()
{
    const QString myurl = currentpage()->url().toString();
    m_url.setText(myurl);
    m_tab->setTabText(m_tab->currentIndex(), currentpage()->title());
}

void WebBrowser::S_addtab()
{
    m_tab->addTab(addtab(), "New tab");
}

void WebBrowser::S_back()
{
    currentpage()->back();
}
void WebBrowser::S_forward()
{
    currentpage()->forward();
}
void WebBrowser::S_reload()
{
    currentpage()->reload();
}
void WebBrowser::S_stop()
{
    currentpage()->stop();
}

