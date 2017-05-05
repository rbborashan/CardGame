#include "pile.h"
#include "card.h"
#include "gameboard.h"
#include "cardmove.h"

extern GameBoard* MainApp;
extern Game* game;
extern QList <Pile*> piles;

/* Drag and drop rule lists for different kinds of
 * piles. */
Rule* PileStock::dragRules[DRAGLAST];
Rule* PileStock::dropRules[DROPLAST];

Rule* PileFoundation::dragRules[DRAGLAST];
Rule* PileFoundation::dropRules[DROPLAST];

Rule* PileField::dragRules[DRAGLAST];
Rule* PileField::dropRules[DROPLAST];

Rule* PileFreeCell::dragRules[DRAGLAST];
Rule* PileFreeCell::dropRules[DROPLAST];

Rule* PileDealt::dragRules[DRAGLAST];
Rule* PileDealt::dropRules[DROPLAST];

/* Constructor adds the pile and its children to the game as QLabels. */
Pile::Pile(int x, int y, int dx, int dy, QWidget* parent)
    :QLabel(parent), delta(QPoint(dx,dy)), top(0), bottom(0)
{
    game->AddPile(this);
    move(x, y);
    resize(71, 96);
    setFrameShape(Box);
    setLineWidth(1);
    setStyleSheet("QLabel {color : green; }");
    show();
}

/* Destructor destroys the pile's children. */
Pile::~Pile()
{
    Card* card = bottom;
    while (card)
    {
        bottom = card->over;
            card->setParent(NULL);
            delete card;
            card = bottom;
    }
}

/* Adds a card (or stack of cards) to the pile and checks
 * for a game win if the accepting pile is a foundation pile. */
void Pile::AcceptCards(Card* card, bool show, bool record)
{
    QPoint cardPosition;

    if (record) new CardMove(card, card->pile, this);

    if (card->pile)
        card->pile->ReleaseCards(card, show);

    if (top)
    {
        card->under = top;
        top->over = card;
        cardPosition = top->pos() + (delta / ((top->faceup)?1:2));
    }

    else
    {
        cardPosition = pos();
        bottom = card;
        card->under = NULL;
    }

    card->pile = this;
    top = card->AdjustPositions(cardPosition, delta);

    if (card->pip == KING && Type() == PLAYOFF) game->CheckWin();
}

/* Removes a card (or stack of cards) from a pile. */
void Pile::ReleaseCards(Card* card, bool show)
{
    if(card && card->pile && card->pile == this)
    {
        if(card->under)
        {
            top = card->under;
            top->over = NULL;
            card->under = NULL;
            if (show) top->Faceup(true);
        }

        else {top = bottom = NULL;}
    }
}

/* Accepts a variable number of drop rules and
 * adds those restrictions to the pile. */
void Pile::AddDropRules(int n ...)
{
    va_list lp;
    va_start(lp, n);

    int i = 0;
    while(i < n)
        DropRule(i++, va_arg(lp, Rule*));

    DropRule(i, NULL);
    va_end(lp);
}

/* Accepts a variable number of drag rules and
 * adds those restrictions to the pile. */
void Pile::AddDragRules(int n ...)
{
    va_list lp;
    va_start(lp, n);

    int i = 0;
    while(i < n)
        DragRule(i++, va_arg(lp, Rule*));

    DragRule(i, NULL);
    va_end(lp);
}

/* Determines whether a given card can be legally
 * dropped on the pile. */
bool Pile::CanBeDropped(Card* card)
{
    int i = 0;
    bool ok = true;
    while (ok && DropRule(i))
        ok = DropRule(i++)->Enforce(this, card);
    return ok;
}

/* Determines whether a given card can be legally
 * dragged off of the pile. */
bool Pile::CanBeDragged(Card* card)
{
    int i = 0;
    bool ok = true;
    while (ok && DragRule(i))
        ok = DragRule(i++)->Enforce(this, card);
    return ok;
}

/* Finds the nearest pile which can legally have
 * a card dropped on it and drops it there. */
void Pile::FindClosestDrop(Card* card)
{
    const int NUM = 3;
    QPoint drop = card->pos();
    Pile* closest[NUM] = {NULL, NULL, NULL};
    int distance[NUM] = {10000, 20000, 30000};
    for(int i = 0; i < game->piles.count(); i++)
    {
        Pile* pile = game->piles[i];

        if (pile == card->pile) continue;

        QPoint diff = drop - (pile->top?pile->top->pos():pile->pos());
        int dist = diff.manhattanLength();

        for (int j = 0; j < NUM; j++)
        {
            if(dist < distance[j])
            {
                std::swap(dist, distance[j]);

                std::swap(pile, closest[j]);
            }
        }
    }
    for (int i = 0; i < NUM; i++)
    {
        if (closest[i] && closest[i]->CanBeDropped(card))
        {
            closest[i]->AcceptCards(card);
            return;
        }
    }

    QPoint p = card->under?(card->under->pos() + card->pile->Delta() / (card->under->faceup?1:2)):card->pile->pos();
    card->AdjustPositions(p,card->pile->delta);
}

/* Releases a card when the mouse is released. */
void Pile::mouseReleaseEvent(QMouseEvent* event) {OnClickEvent(NULL);}

/* Constructor and method definitions for child Pile classes */
PileField::PileField(int x, int y, int dx, int dy, QWidget* parent):
    Pile(x, y, dx, dy, parent) {}

Rule* PileField::DragRule(int i) {return dragRules[i];}

void PileField::DragRule(int i, Rule* r) {dragRules[i] = r;}

Rule* PileField::DropRule(int i) {return dropRules[i];}

void PileField::DropRule(int i, Rule* r) {dropRules[i] = r;}

void PileField::OnClickEvent(Card* card) {game->OnFieldClick(card);}

void PileField::mouseDoubleClickEvent(Card* card) {game->OnFieldDoubleClick(card);}

PileFoundation::PileFoundation(int x, int y, int dx, int dy, QWidget* parent):
    Pile(x,y,dx,dy,parent){}

Rule* PileFoundation::DragRule(int i) {return dragRules[i];}

void PileFoundation::DragRule(int i, Rule* r) {dragRules[i] = r;}

Rule* PileFoundation::DropRule(int i) {return dropRules[i];}

void PileFoundation::DropRule(int i, Rule* r) {dropRules[i] = r;}

PileStock::PileStock(int x, int y, int dx, int dy, QWidget* parent):
    Pile(x, y, dx, dy, parent) {}

Rule* PileStock::DragRule(int i) {return dragRules[i];}

void PileStock::DragRule(int i, Rule* r) {dragRules[i] = r;}

Rule* PileStock::DropRule(int i) {return dropRules[i];}

void PileStock::DropRule(int i, Rule* r) {dropRules[i] = r;}

void PileStock::OnClickEvent(Card* card) {game->OnStockClick(card);}

PileDealt::PileDealt(int x, int y, int dx, int dy, QWidget* parent):
    Pile(x, y, dx, dy, parent) {}

Rule* PileDealt::DragRule(int i) {return dragRules[i];}

void PileDealt::DragRule(int i, Rule* r) {dragRules[i] = r;}

Rule* PileDealt::DropRule(int i) {return dropRules[i];}

void PileDealt::DropRule(int i, Rule* r) {dropRules[i] = r;}

void PileDealt::OnClickEvent(Card* card) {game->OnDealtClick(card);}

PileFreeCell::PileFreeCell(int x, int y, int dx, int dy, QWidget* parent):
    Pile(x, y, dx, dy, parent) {}

Rule* PileFreeCell::DragRule(int i) {return dragRules[i];}

void PileFreeCell::DragRule(int i, Rule* r) {dragRules[i] = r;}

Rule* PileFreeCell::DropRule(int i) {return dropRules[i];}

void PileFreeCell::DropRule(int i, Rule* r) {dropRules[i] = r;}

void PileFreeCell::OnClickEvent(Card* card) {game->OnFreeCellClick(card);}
