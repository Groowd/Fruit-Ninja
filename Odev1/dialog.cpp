#include "dialog.h"        // MEHMET SELEK  21100011043
#include "ui_dialog.h"

int sure=30;
int xkoordinat=0;
int ykoordinat=0;
int randomsayi;
int kesilenkarpuz=0;
int kacirilankarpuz=0;
int maxskor=0;
int konumdosyasisatir=0;
int skor=0;


Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QFile konumdosyam("konumlar.txt");
    if(!konumdosyam.open(QIODevice::ReadOnly)){
        QMessageBox::critical(this,"Hata!",konumdosyam.errorString());
    }
    QTextStream konumstream(&konumdosyam);
    while(!konumstream.atEnd()){
        konumstream.readLine();
        konumdosyasisatir+=1;
    }
    konumdosyam.close();

    QFile skordosyam("skorlar.txt");
    if(!skordosyam.open(QIODevice::ReadOnly)){
        QMessageBox::critical(this,"Hata!",skordosyam.errorString());
    }
    QTextStream skorstream(&skordosyam);
    while(!skorstream.atEnd()){
        skor = skorstream.readLine().toInt();
        if(skor>maxskor){
            maxskor=skor;
        }
    }
    skordosyam.close();
    Timer = new QTimer(this);
    connect(Timer,SIGNAL(timeout()),this,SLOT(ZamanFonksiyonu()));     //Sureyi tutmak icin
    Timer->start(1000);

    Timer2 = new QTimer(this);
    connect(Timer2,SIGNAL(timeout()),this,SLOT(KarpuzOlusturma()));   //Ekranda rastgele karpuzlar olusturmak icin
    Timer2->start(400);

    Timer3 = new QTimer(this);
    connect(Timer3,SIGNAL(timeout()),this,SLOT(HareketEttir()));   //Karpuzlarin hareket etmesi icin
    Timer3->start(20);

    Timer4 = new QTimer(this);
    connect(Timer4,SIGNAL(timeout()),this,SLOT(KarpuzKes()));    //Karpuzlara tiklandiginda kesilen karpuz olusmasi icin
    Timer4->start(1);

    Timer5 = new QTimer(this);
    connect(Timer5,SIGNAL(timeout()),this,SLOT(KarpuzSayaclariKontrol()));    //Kesilen ve kacirilan karpuzlari yazdirmak icin
    Timer5->start(1);


}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::ZamanFonksiyonu()
{
    if(sure>=0){
        ui->lbl_yazsure->setText(QString::number(sure));
        if(sure==0)
        {
            Timer->disconnect();
            Timer2->disconnect();
            Timer3->disconnect();
            Timer4->disconnect();
            Timer5->disconnect();

            QFile skordosyasi("skorlar.txt");
            if(!skordosyasi.open(QIODevice::Append)){
                QMessageBox::critical(this,"Hata!",skordosyasi.errorString());
            }
            QTextStream skorstreami(&skordosyasi);
            skorstreami<<QString::number(kesilenkarpuz)+"\n";
            skordosyasi.close();

            if(kesilenkarpuz>maxskor){
                QMessageBox::information(this,"Bilgilendirme!","Oyun Bitti! Tebrikler Maksimum Skor Sizde!\nKesilen Karpuz Sayısı : "+ui->lbl_yazkesilen->text()+"\nKaçırılan Karpuz Sayısı : "+ui->lbl_yazkacirilan->text()+"\nMaksimum Skor : "+QString::number(maxskor));
                this->close();
            }
            else if(kesilenkarpuz<maxskor){
                QMessageBox::information(this,"Bilgilendirme!","Oyun Bitti! Maksimum Skoru Geçemediniz!\nKesilen Karpuz Sayısı : "+ui->lbl_yazkesilen->text()+"\nKaçırılan Karpuz Sayısı : "+ui->lbl_yazkacirilan->text()+"\nMaksimum Skor : "+QString::number(maxskor));
                this->close();
            }
            else{
                QMessageBox::information(this,"Bilgilendirme!","Oyun Bitti! Maksimum Skora Ortak Oldunuz!\nKesilen Karpuz Sayısı : "+ui->lbl_yazkesilen->text()+"\nKaçırılan Karpuz Sayısı : "+ui->lbl_yazkacirilan->text()+"\nMaksimum Skor : "+QString::number(maxskor));
                this->close();
            }
        }  
    } 

    sure=sure-1;
}

void Dialog::KarpuzOlusturma()
{
    if(sure>=0){
        int sayac=0;
        randomsayi=QRandomGenerator::global()->bounded(0,konumdosyasisatir);

        QFile dosyam("konumlar.txt");
        if(!dosyam.open(QIODevice::ReadOnly)){
            QMessageBox::critical(this,"Hata!",dosyam.errorString());
        }

        QTextStream stream(&dosyam);
        while(!stream.atEnd()){
            QString satir = stream.readLine();
            if(sayac==randomsayi){
                QStringList satir2 =satir.split(" ");
                xkoordinat=satir2.at(0).toInt();
                ykoordinat=satir2.at(1).toInt();
                break;
            }
            sayac+=1;
        }
        karpuz *olusankarpuz = new karpuz(this);
        olusankarpuz->tiklandi=0;
        olusankarpuz->kacirildi=0;
        olusankarpuz->setCheckable(true);
        QPixmap pix(":/icons/images/karpuz.png");
        olusankarpuz->setGeometry(xkoordinat,ykoordinat,80,80);
        olusankarpuz->setIcon(pix.scaled(80,80,Qt::KeepAspectRatio));
        olusankarpuz->setStyleSheet("background-color: transparent; border: none;");
        karpuz_liste.push_back(olusankarpuz);
        olusankarpuz->show();
        dosyam.close();
    }
}


void Dialog::HareketEttir()
{
    if(sure>=0){
        for(int i=0;i<karpuz_liste.size();i++){
            karpuz_liste[i]->setGeometry(karpuz_liste[i]->x(),karpuz_liste[i]->y()+3,80,80);
        }
    }
}

void Dialog::KarpuzKes()
{
    if(sure>=0){
        for(int j=0;j<karpuz_liste.size();j++){
            if(karpuz_liste[j]->isChecked()){
                karpuz_liste[j]->tiklandi=1;
                QPixmap pix2(":/icons/images/kesikkarpuz.png");
                karpuz_liste[j]->setFlat(true);
                karpuz_liste[j]->setAutoFillBackground(false);
                karpuz_liste[j]->setCheckable(false);
                karpuz_liste[j]->setIcon(pix2);
                karpuz_liste[j]->setStyleSheet("background-color: transparent; border: none;");
                kesilenkarpuz+=1;
                kesilenKarpuz_liste.push_back(karpuz_liste[j]);
                karpuz_liste[j]->TimerKarpuz->start(3000);
                karpuz_liste.removeAt(j);
            }
        }
    }
}


void Dialog::KarpuzSayaclariKontrol()
{
    if(sure>=0){
        ui->lbl_yazkesilen->setText(QString::number(kesilenkarpuz));
        for(int m=0;m<karpuz_liste.size();m++){
            if(karpuz_liste[m]->y()>820 && karpuz_liste[m]->kacirildi==0){
                kacirilankarpuz+=1;
                karpuz_liste[m]->kacirildi=1;
            }
        }
        ui->lbl_yazkacirilan->setText(QString::number(kacirilankarpuz));
    }
}




