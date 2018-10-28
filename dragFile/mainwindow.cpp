#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDebug>
#include <QLabel>
#include <QHBoxLayout>
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAcceptDrops(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}

void MainWindow::createLabel(QString filename) {
     qDebug() << "Dropped file:" << filename;
     QLabel *label = new QLabel("filename");
QWidget*central = new QWidget(this);
    QGridLayout *layout = new QGridLayout(central);
    layout->addWidget(label, 10, 10, 100, 100);
    central->setLayout(layout);

     //Here is how to change position:
     //label->setGeometry(QRectF(10,10,30,80));
}

void MainWindow::dropEvent(QDropEvent *e)
{
    foreach (const QUrl &url, e->mimeData()->urls()) {

        createLabel(url.toLocalFile());

    }
}
