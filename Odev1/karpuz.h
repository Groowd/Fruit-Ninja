#ifndef KARPUZ_H      // MEHMET SELEK  21100011043
#define KARPUZ_H

#include <QPushButton>
#include <QWidget>

class karpuz : public QPushButton
{
    Q_OBJECT
public:
    karpuz(QWidget *parrent=0);
    int tiklandi;
    int kacirildi;
    QTimer *TimerKarpuz;
public slots:
    void deleteThis();

};

#endif // KARPUZ_H
