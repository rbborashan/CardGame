#ifndef CARD_H
#define CARD_H

#include <QLabel>
#include <QImage>

enum cardColors {BLACK, RED};
enum pips {ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, SUIT_SIZE};
enum suits {CLUBS, DIAMONDS, HEARTS, SPADES};

class Pile;

class Card : public QLabel
{
    static QImage faces[53];
    static bool initialized;
    static QPoint mouseDownOffset;
    static QPoint startDragPos;
    static Qt::MouseButtons buttonDown;
    static QPoint popUpPos;
    static Card* popUpCard;

    cardColors color;
    pips pip;
    suits suit;
    int value;

    bool faceup;
    bool moving;
    bool okToDrag;
    bool hasMouseDown;

    Card* under;
    Card* over;
    Pile* pile;

public:
    Card(int, QWidget* parent = 0);
    Card(pips, suits, QWidget* parent = 0);

    bool Faceup() {return faceup;}
    suits Suit() {return suit;}
    pips Pip() {return pip;}
    cardColors Color() {return color;}
    Pile* Pilep() {return pile;}
    Card* Over() {return over;}
    Card* Under() {return under;}
    Card* AdjustPositions(QPoint, QPoint);
    QSize sizeHint() const;
    int StackSize();

    void Faceup(bool);
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseDoubleClickEvent(QMouseEvent*);
    void Move(Pile*, bool show = true);
    void AlignWithPile();
    void Flip();
    void Playoff();

    static void Initialize();

    friend class Pile;
};

void Shuffle(Card* Deck[], int);

#endif //CARD_H

