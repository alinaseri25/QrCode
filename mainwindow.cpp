#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

void MainWindow::onTxtQrCodeChanged()
{
    createQrCode();
}

void MainWindow::onCmbQrCodeCurrentIndexChanged(int value)
{
    //QMessageBox::about(this,QString("test"),ui->CmbQrCode->currentText());
    createQrCode();
}

void MainWindow::onBtnSaveClicked()
{
    //ui->LblQrCode->pixmap().toImage().save(QString("C:\1.jpg"));
    QrCodeImg.save(QString("C:\\1.jpg"));
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MultipleSize = 3;
    BorderSize = 4;

    QPalette pal;
    pal.setColor(QPalette::Window,QColor(0x1C,0x33,0x4E));
    this->setPalette(pal);

    pal.setColor(QPalette::WindowText,QColor(0xFF,0xFF,0xFF));
    ui->CmbQrCode->setPalette(pal);

    ui->TxtQrCode->setPlainText(QString("email:alinaseri25@gmail.com"));

    connect(ui->TxtQrCode,&QTextEdit::textChanged,this,&MainWindow::onTxtQrCodeChanged);

    //connect(ui->CmbQrCode,&QComboBox::currentIndexChanged,this,&MainWindow::onCmbQrCodeCurrentIndexChanged);
    connect(ui->CmbQrCode,static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&MainWindow::onCmbQrCodeCurrentIndexChanged);

    connect(ui->BtnSave,&QPushButton::clicked,this,&MainWindow::onBtnSaveClicked);

    ui->CmbQrCode->addItem(QString("Low"));
    ui->CmbQrCode->addItem(QString("Medium"));
    ui->CmbQrCode->addItem(QString("High"));
    ui->CmbQrCode->addItem(QString("Quartile"));

    createQrCode();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createQrCode()
{
    qrcodegen::QrCode::Ecc errCorLvl = qrcodegen::QrCode::Ecc::LOW;  // Error correction level
    switch (ui->CmbQrCode->currentIndex()) {
    case 0:
        errCorLvl = qrcodegen::QrCode::Ecc::LOW;
    break;
    case 1:
        errCorLvl = qrcodegen::QrCode::Ecc::MEDIUM;
    break;
    case 2:
        errCorLvl = qrcodegen::QrCode::Ecc::HIGH;
    break;
    case 3:
        errCorLvl = qrcodegen::QrCode::Ecc::QUARTILE;
    break;
    default:
        errCorLvl = qrcodegen::QrCode::Ecc::LOW;
    }

    QString text = ui->TxtQrCode->toPlainText();

    QrCodeImg = qrcodegen::QrCode::encodeToImag(text,errCorLvl,MultipleSize,BorderSize);

    ui->LblQrCode->setPixmap(QPixmap::fromImage(QrCodeImg));
}
