#include "karpuz.h"        // MEHMET SELEK  21100011043
#include "qtimer.h"

karpuz::karpuz(QWidget *parrent): QPushButton(parrent)
{
    setIcon(QIcon("karpuz.png"));
    setIconSize(QSize(80,80));
    setFixedSize(80,80);
    setFlat(true);
    tiklandi=0;
    kacirildi=0;
    TimerKarpuz = new QTimer(this);
    connect(TimerKarpuz,SIGNAL(timeout()),this,SLOT(deleteThis()));


}
void karpuz::deleteThis() {
    this->close();
}
