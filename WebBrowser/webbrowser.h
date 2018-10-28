#ifndef WEBBROWSER_H
#define WEBBROWSER_H
#include<QtWebEngine>
#include<QtWidgets>
#include<QtWebEngineWidgets>

class WebBrowser:public QMainWindow
{
    Q_OBJECT
public:
    WebBrowser();
    QWidget *addtab();
    QWebEngineView *currentpage();
public slots:
    void tabchanged();
    void loadpage();
    void linkchange();
    void S_addtab();
    void S_back();
    void S_forward();
    void S_reload();
    void S_stop();
private:
    QTabWidget *m_tab;
    QWebEngineView *m_page;
    QLineEdit m_url;
    QMenu *m_file;
    QToolBar *m_tools;
};

#endif // WEBBROWSER_H
