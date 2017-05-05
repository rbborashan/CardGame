#include "winningdialog.h"
#include "ui_winningdialog.h"
#include "cardmove.h"

WinningDialog::WinningDialog(QWidget *parent)
    :QDialog(parent), ui(new Ui::WinningDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("You Win");
}

WinningDialog::~WinningDialog() {delete ui;}

void WinningDialog::on_pushButton_clicked()
{
    this->close();
}
