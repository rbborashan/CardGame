#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QtGui>
#include <QWidget>
#include <QMainWindow>
#include <QLabel>

#include "pile.h"
#include "card.h"

namespace Ui {
class GameBoard;
}

class GameBoard : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameBoard(QWidget *parent = 0);
    ~GameBoard();

public slots:
    void on_action_Freecell_triggered();

    void on_action_Redeal_triggered();

    void on_actionE_xit_triggered();

private:
    Ui::GameBoard *ui;
    QTime t;

private slots:
    void on_action_Undo_triggered();
    void on_actionPlayoff_triggered();
    void on_actionUndo_All_triggered();
    void on_actionKlondike_triggered();
    void on_action_About_triggered();
    void on_action_Rules_triggered();
    void on_action_Spider_triggered();
};
#endif // GAMEBOARD_H
