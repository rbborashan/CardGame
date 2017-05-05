#ifndef WINNINGDIALOG_H
#define WINNINGDIALOG_H

#include <QDialog>

namespace Ui {
class WinningDialog;
}

class WinningDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WinningDialog(QWidget *parent = 0);
    ~WinningDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::WinningDialog *ui;
};

#endif // WINNINGDIALOG_H
