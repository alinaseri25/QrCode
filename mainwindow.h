#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <../../QRCode/qrcodegen.hpp>
#include <QPixmap>
#include <QPainter>
#include <QMessageBox>
#include <QTextEdit>
#include <QComboBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void onTxtQrCodeChanged(void);
    void onCmbQrCodeCurrentIndexChanged(int value);
    void onBtnSaveClicked(void);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void createQrCode(void);
    int MultipleSize,BorderSize;
    QImage QrCodeImg;
};
#endif // MAINWINDOW_H
