#ifndef IHMPIKAWA_H
#define IHMPIKAWA_H

#include <QtWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class IhmPikawa; }
QT_END_NAMESPACE

class IhmPikawa : public QWidget
{
    Q_OBJECT

public:
    IhmPikawa(QWidget *parent = nullptr);
    ~IhmPikawa();

private:
    Ui::IhmPikawa *ui;
};
#endif // IHMPIKAWA_H
