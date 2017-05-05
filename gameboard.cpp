#include <QtGui>
#include <QWidget>
#include <QLabel>

#include "gameboard.h"
#include "ui_gameboard.h"
#include "aboutdialog.h"
#include "ruleswindow.h"
#include "cardmove.h"
#include "freecell.h"
#include "klondike.h"
#include "spider.h"

extern AboutDialog* about;
extern RulesWindow* rules;

Game* game = NULL;

GameBoard::GameBoard(QWidget* parent)
    :QMainWindow(parent), ui(new Ui::GameBoard)
{
    ui->setupUi(this);
    t.start();  // for qsrand()

    setWindowTitle("Solitaire");

    Card::Initialize();

    // avoid triggering these when no Game instance exists
    ui->action_Redeal->setEnabled(false);
    ui->actionPlayoff->setEnabled(false);
}

GameBoard::~GameBoard()
{
    delete ui;
}

void GameBoard::on_actionE_xit_triggered()
{
    exit(0);
}

void GameBoard::on_action_Redeal_triggered() {game->ReDeal();}

void GameBoard::on_action_Freecell_triggered()
{
    if(game)
        delete game;

    ui->label->hide();

    setMinimumSize(700, 600);
    setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum));

    game = new Freecell(ui->centralWidget);

    qsrand(t.elapsed());
    game->ReDeal();
    CardMove::Clear();

    setWindowTitle("Freecell");
    ui->action_Redeal->setEnabled(true);
    ui->actionPlayoff->setEnabled(true);
}

void GameBoard::on_action_Undo_triggered()
{
    CardMove::UndoMove();
}

void GameBoard::on_actionPlayoff_triggered()
{
    game->PlayOffAll();
}

void GameBoard::on_actionUndo_All_triggered()
{
    CardMove::UndoAllMove();
}

void GameBoard::on_actionKlondike_triggered()
{
    if(game)
        delete game;

    ui->label->hide();

    setMinimumSize(600, 600);
    setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum));

    game = new Klondike(ui->centralWidget);

    qsrand(t.elapsed());
    game->ReDeal();
    CardMove::Clear();

    setWindowTitle("Klondike");
    ui->action_Redeal->setEnabled(true);
    ui->actionPlayoff->setEnabled(true);
}

void GameBoard::on_action_Spider_triggered()
{
    if (game)
        delete game;

    ui->label->hide();

    setMinimumSize(850, 700);
    setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum));

    game = new Spider(ui->centralWidget);

    qsrand(t.elapsed());
    game->ReDeal();
    CardMove::Clear();

    setWindowTitle("Spider");
    ui->action_Redeal->setEnabled(true);
    ui->actionPlayoff->setEnabled(true);
}

void GameBoard::on_action_About_triggered()
{
    about->show();
}

void GameBoard::on_action_Rules_triggered()
{
    rules->show();
}
