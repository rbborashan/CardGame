#include "ruleswindow.h"
#include "ui_ruleswindow.h"

RulesWindow::RulesWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RulesWindow)
{
    ui->setupUi(this);
    setWindowTitle("Game Rules");
}

RulesWindow::~RulesWindow()
{
    delete ui;
}
