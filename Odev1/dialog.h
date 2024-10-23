#ifndef DIALOG_H      // MEHMET SELEK  21100011043
#define DIALOG_H

#include <QDialog>
#include <QTimer>
#include <QDebug>
#include <QMessageBox>
#include <QMouseEvent>
#include "karpuz.h"
#include <QFile>
#include <QTextStream>
#include <QRandomGenerator>
#include <QPixmap>
#include <QDebug>


QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
public slots:
    void ZamanFonksiyonu();
    void KarpuzOlusturma();
    void HareketEttir();
    void KarpuzKes();
    void KarpuzSayaclariKontrol();

private:
    Ui::Dialog *ui;

    QTimer *Timer;
    QTimer *Timer2;
    QTimer *Timer3;
    QTimer *Timer4;
    QTimer *Timer5;
    QList <karpuz*> karpuz_liste;
    QList <karpuz*> kesilenKarpuz_liste;
    QTextStream *stream;
};
#endif // DIALOG_H
