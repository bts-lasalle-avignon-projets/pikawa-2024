#include "ihmpikawa.h"
#include "ui_ihmpikawa.h"

IhmPikawa::IhmPikawa(QWidget* parent) : QWidget(parent), ui(new Ui::IhmPikawa)
{
    ui->setupUi(this);
}

IhmPikawa::~IhmPikawa()
{
    delete ui;
}
