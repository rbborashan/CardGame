#ifndef PILE_H
#define PILE_H

#include <QLabel>
#include <QMouseEvent>

#include "rule.h"
#include "game.h"

const int DRAGLAST = 6;
const int DROPLAST = 6;
enum pileType {PLAYOFF, DEAL, DEALT, FIELD, FREE_CELL};

class Card;

class Pile : public QLabel
{
    QPoint delta;
    Card* top;
    Card* bottom;
    int rulesSet;

public:
    Pile(int, int, int, int, QWidget*);
    ~Pile();

    Card* Top() {return top;}
    Card* Bottom() {return bottom;}
    QPoint Delta() {return delta;}
    bool Empty() {return !bottom;}
    bool CanBeDragged(Card*);
    bool CanBeDropped(Card*);

    void AcceptCards(Card*, bool show = true, bool record = true);
    void ReleaseCards(Card*, bool show = true);
    void FindClosestDrop(Card*);
    void Deal(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void AddDropRules(int n ...);
    void AddDragRules(int n ...);

    virtual void OnClickEvent(Card*) {}
    virtual void mouseDoubleClickEvent(Card*) {}
    virtual void DragRule(int, Rule*) = 0;
    virtual void DropRule(int, Rule*) = 0;
    virtual Rule* DragRule(int) = 0;
    virtual Rule* DropRule(int) = 0;
    virtual pileType Type() = 0;
};

class PileStock : public Pile
{
    static Rule* dragRules[DRAGLAST];
    static Rule* dropRules[DROPLAST];

public:
    PileStock(int, int, int, int, QWidget*);

    pileType Type() {return DEAL;}
    Rule* DragRule(int);
    Rule* DropRule(int);

    void DragRule(int, Rule*);
    void DropRule(int, Rule*);
    void OnClickEvent(Card*);
};

class PileFoundation : public Pile
{
    static Rule* dragRules[DRAGLAST];
    static Rule* dropRules[DROPLAST];

public:
    PileFoundation(int, int, int, int, QWidget*);

    pileType Type() {return PLAYOFF;}
    Rule* DragRule(int);
    Rule* DropRule(int);

    void DragRule(int, Rule*);
    void DropRule(int, Rule*);
};

class PileField : public Pile
{
    static Rule* dragRules[DRAGLAST];
    static Rule* dropRules[DROPLAST];

public:
    PileField(int, int, int, int, QWidget*);

    pileType Type() {return FIELD;}
    Rule* DragRule(int);
    Rule* DropRule(int);

    void DragRule(int, Rule*);
    void DropRule(int, Rule*);
    void OnClickEvent(Card*);
    void mouseDoubleClickEvent(Card*);
};

class PileFreeCell : public Pile
{
    static Rule* dragRules[DRAGLAST];
    static Rule* dropRules[DROPLAST];

public:
    PileFreeCell(int, int, int, int, QWidget*);

    pileType Type() {return FREE_CELL;}
    Rule* DragRule(int);
    Rule* DropRule(int);

    void DragRule(int, Rule*);
    void DropRule(int, Rule*);
    void OnClickEvent(Card*);
};

class PileDealt : public Pile
{
    static Rule* dragRules[DRAGLAST];
    static Rule* dropRules[DROPLAST];

public:
    PileDealt(int, int, int, int, QWidget*);

    pileType Type() {return DEALT;}
    Rule* DragRule(int);
    Rule* DropRule(int);

    void DragRule(int, Rule*);
    void DropRule(int, Rule*);
    void OnClickEvent(Card*);
};
#endif // PILE_H
