#ifndef IHMPIKAWA_H
#define IHMPIKAWA_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class IhmPikawa; }
QT_END_NAMESPACE

class IhmPikawa : public QWidget
{
    Q_OBJECT

public:
    explicit IhmPikawa(QWidget *parent = nullptr);
    ~IhmPikawa();

public slots:
    void AcctualiserAcceuil();

private:
    Ui::IhmPikawa *ui;
    QPushButton *accueil;
    QPushButton *choisirCafe;
    QPushButton *visualiserConsommation;
    QPushButton *analyseSante;
    QPushButton *gererPreferences;
    QPushButton *gererCapsules;
    QPushButton *voirAlertes;
};

#endif // IHMPIKAWA_H
