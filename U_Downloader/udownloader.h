#ifndef UDOWNLOADER_H
#define UDOWNLOADER_H

#include <QApplication>
#include <QtWidgets>
#include <QWidget>
#include <QtNetwork>



class UDownloader : public QWidget
{
    Q_OBJECT

public:
    UDownloader();

public slots:
    void download();
    void save();
    void S_downloadprogress(qint64, qint64);
    void errormsg(QNetworkReply::NetworkError);


private:
    QLabel *label;
    QLineEdit *mylink;
    QPushButton *dbutton;
    QProgressBar *dprogress;
    QVBoxLayout *vlayout;
    QHBoxLayout *hlayout;
    QLabel *filenamelabel;
    void setProxy();
};

#endif // UDOWNLOADER_H
