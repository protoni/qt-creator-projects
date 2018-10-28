#include "udownloader.h"
#include "ui_udownloader.h"
#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDir>

UDownloader::UDownloader():QWidget()
{
    setFixedSize(300,200);

    vlayout = new QVBoxLayout(this);
    hlayout = new QHBoxLayout;
    label = new QLabel("URL");
    mylink = new QLineEdit;
    dbutton = new QPushButton("Download");
    dprogress = new QProgressBar;
    filenamelabel = new QLabel;
    dprogress->setTextVisible(true);

    hlayout->addWidget(label);
    hlayout->addWidget(mylink);

    vlayout->addLayout(hlayout);
    vlayout->addWidget(dbutton);
    vlayout->addWidget(dprogress);
    vlayout->addWidget(filenamelabel);

    connect(dbutton, SIGNAL(clicked(bool)), this, SLOT(download()));

}

/*
void UDownloader::setProxy()
{
    QNetworkProxy proxy;
    proxy.setType(QNetworkProxy::HttpProxy);
    proxy.setHostName("proxy.com");
    proxy.setPort(1080);
    proxy.setUser("username");
    proxy.setPassword("password");

    QNetworkProxy::setApplicationProxy(proxy);
    qDebug() << "Proxy set!: ";
}*/

void UDownloader::download()
{
    const QUrl myurl = QUrl(mylink->text());
    if(!myurl.isEmpty())
    {
        const QNetworkRequest request(myurl);
        QNetworkAccessManager *manager = new QNetworkAccessManager;
        QNetworkReply *reply = manager->get(request);

        connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(errormsg(QNetworkReply::NetworkError)));
        connect(reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(S_downloadprogress(qint64, qint64)));
        connect(reply, SIGNAL(finished()), this, SLOT(save()));
    }
    else
    {
        QMessageBox::critical(this, "url empty", "You must fill the URL field!");
    }
}

void UDownloader::errormsg(QNetworkReply::NetworkError)
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    QMessageBox::critical(this, "networking error", reply->errorString());
}

void UDownloader::S_downloadprogress(qint64 bytereceived, qint64 totalbytes)
{
    dprogress->setRange(0, totalbytes);
    dprogress->setValue(bytereceived);
}

// http://newsmaritime.com/wp-content/uploads/2016/06/Check-out-the-new-and-functional-programming-language.jpg
void UDownloader::save()
{
    QString path = QDir::currentPath();
    QString suffix = "image.jpg";
    QString filename = path + "/" + suffix;
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    QFile *file = new QFile(filename);


    if(file->open(QIODevice::WriteOnly))
    {
        file->write(reply->readAll());
        file->close();
        QMessageBox::information(this, "download finished", "your file has been downloaded");

            /*
        qDebug() << "Opened network reply! Reply: " << reply;
        if(myimage.load(reply, NULL))
        {
            qDebug() << "loaded reply to image!";
            if(myimage.save("myimage"))
            {
                qDebug() << "saved image!";
                QMessageBox::information(this, "download finished", "your file has been downloaded");
            }
        }*/

    }
    else QMessageBox::critical(this, "Error:", "Could not create a file");

}

