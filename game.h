#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QList>

class Pile;
class Card;

class Game
{
protected:
    QWidget* parent;
    QList <Pile*> piles;

public:
    Game(QWidget*);
    virtual ~Game();

    void Clear();
    void AddPile(Pile*);

    virtual int FreeMoves() {return 0;}
    virtual bool PlayOff(Card*);

    virtual void OnFieldDoubleClick(Card*) {}
    virtual void OnFieldClick(Card*) {}
    virtual void OnStockClick(Card*) {}
    virtual void OnDealtClick(Card*) {}
    virtual void OnFreeCellClick(Card*) {}
    virtual void CheckWin();
    virtual void PlayOffAll();
    virtual void ReDeal() = 0;

    friend class Pile;
};

#endif // GAME_H
