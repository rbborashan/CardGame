#include "gameboard.h"
#include "winningdialog.h"
#include "aboutdialog.h"
#include "ruleswindow.h"

#include <QApplication>

GameBoard* board;
WinningDialog* win;
AboutDialog* about;
RulesWindow* rules;

int main (int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameBoard gb;
    WinningDialog wd;
    AboutDialog ad;
    RulesWindow rw;

    board = &gb;
    win = &wd;
    about = &ad;
    rules = &rw;

    gb.show();

    return a.exec();
}
