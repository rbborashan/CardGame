#include <QMouseEvent>
#include <QtGlobal>
#include <QString>

#include "card.h"
#include "pile.h"
#include "gameboard.h"
#include "game.h"

extern Game* game;

QImage Card::faces[53];
QPoint Card::mouseDownOffset;
QPoint Card::startDragPos;
QPoint Card::popUpPos;
Card* Card::popUpCard;
Qt::MouseButtons Card::buttonDown;
bool Card::initialized = false;

Card::Card(int _value, QWidget* parent):
    QLabel(parent), value(_value), under(0), over(0),pile(0), faceup(false),
    moving(false), hasMouseDown(false)
{
    suit = static_cast<suits> (value / 13);
    pip = static_cast<pips> (value % 13);
    color = static_cast<cardColors> ((suit > 1) ^ (suit & 1));

    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    Faceup(faceup);
}

Card::Card(pips _pip, suits _suit, QWidget* parent):
    QLabel(parent), under(0), over(0), pile(0), pip(_pip), suit(_suit), faceup(false),
    moving(false), hasMouseDown(false)
{
    value = suit * SUIT_SIZE + pip;
    color = static_cast<cardColors> ((suit > 1) ^ (suit & 1));

    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    Faceup(faceup);
}

QSize Card::sizeHint() const {return QSize(71, 96);}

void Card::Move(Pile* to, bool show)
{
    to->AcceptCards(this, show, false);
}

/* Initializes global array of card faces from files. */
void Card::Initialize()
{
    if (initialized) return;

    initialized = true;

    char suit[] = {'c','d','h','s'};
    char pip[] = {'1','2','3','4','5','6','7','8','9','a','b','c','d'};
    QString fname = ":/cards/c1.bmp";
    int n = 0;

    for(int s = CLUBS; s <= SPADES; ++s)
    {
        fname[8] = suit[s];
        for(int p = ACE; p <= KING; ++p)
        {
            fname[9] = pip[p];
            faces[n++] = QImage(fname);
        }
    }

    faces[n] = QImage(":/cards/zCardBack.bmp");
}

void Card::Flip() {Faceup(!faceup);}

/* Set faceup member and select the proper card image. */
void Card::Faceup(bool _faceup)
{
    faceup = _faceup;
    setPixmap(QPixmap::fromImage(faces[faceup?value:52]));
}

void Shuffle(Card* Deck[], int size)
{
    Card* temp;
    int r;
    while(size > 0)
    {
        r = qrand() % size--;
        temp = Deck[r];
        Deck[r] = Deck[size];
        Deck[size] = temp;
        temp->raise();
    }
}

void Card::mousePressEvent(QMouseEvent* event)
{
    switch (event->button())
    {
        case Qt::LeftButton:
            startDragPos = pos();
            mouseDownOffset = pos() - event->globalPos();
            okToDrag = faceup && pile->CanBeDragged(this);
            break;
        case Qt::RightButton:
            popUpPos = pos();
            popUpCard = this;
            move(pos() + QPoint(0,-20));
            break;
        default: ;
    }
}

void Card::mouseMoveEvent(QMouseEvent* event)
{
    QPoint point = event->globalPos() + mouseDownOffset;
    QPoint moved = point - pos();

    if (okToDrag && moved.manhattanLength() > 4)
        moving = true;

    if (moving)
        AdjustPositions(point, pile?pile->Delta():QPoint(0, 10));
}

void Card::mouseReleaseEvent(QMouseEvent* event)
{
    if(event->buttons()) return;

    if(popUpCard)
    {
        popUpCard->move(popUpPos);
        popUpCard = NULL;
        return;
    }

    if(moving && pile)
        pile->FindClosestDrop(this);

    else
        if(pile)
        {
            QPoint point = event->globalPos() + mouseDownOffset;
            QPoint moved = point - pos();

            if (moved.manhattanLength() <= 4)
                pile->OnClickEvent(this);
        }

    moving = false;
    okToDrag = false;
}

Card* Card::AdjustPositions(QPoint newPos, QPoint delta)
{
    Card* card = this;
    Card* top;
    do{
        card->move(newPos);
        card->raise();
        card->show();
        newPos += (delta/(card->faceup?1:2));
        top = card;
        card->pile = pile;
        card = card->over;
    } while(card);
    return top;
}

void Card::AlignWithPile() {move(pile->pos());}

int Card::StackSize()
{
    int count = 0;
    Card* card = this;

    do
    {
        count++;
        card = card->over;
    } while(card);

    return count;
}

void Card::mouseDoubleClickEvent(QMouseEvent*)
{
    if (pile)
        pile->mouseDoubleClickEvent(this);
}

void Card::Playoff() {game->PlayOff(this);}

