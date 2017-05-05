#include "game.h"
#include "pile.h"
#include "card.h"
#include "winningdialog.h"
#include "cardmove.h"

extern WinningDialog* win;

Game::Game(QWidget* _parent) :parent(_parent) {}

Game::~Game() {Clear();}

/* Clears all piles on the field. */
void Game::Clear()
{
    while(!piles.empty())
    {
        Pile* pile = piles.takeLast();
        if (pile) delete pile;
    }
}

/* Determines if a game is won by checking the
 * necessary win conditions. Clears the piles
 * and displays the win dialog if the game is won. */
void Game::CheckWin()
{
    int i = piles.count();
    bool allEmpty = true;

    while (allEmpty && i >= 0 && piles[--i]->Type() != PLAYOFF)
        allEmpty = piles[i]->Empty();

    if (allEmpty)
    {
        win->show();
        CardMove::Clear();
    }
}

/* Adds a pile to the list of piles. */
void Game::AddPile(Pile* pile) {piles.append(pile);}

/* Plays a single card off to the foundation pile if
 * it can be moved. */
bool Game::PlayOff(Card* card)
{
    if(card->Pilep() && card->Pilep()->CanBeDragged(card))
    {
        int i = 0;
        while (i < piles.count() && piles[i] &&
              !(piles[i]->Type() == PLAYOFF &&
                piles[i]->CanBeDropped(card)))
            i++;

        if (i < piles.count())
        {
            piles[i]->AcceptCards(card);
            return true;
        }
    }
    return false;
}

/* Plays off all cards to the foundation pile if
 * they can be moved. */
void Game::PlayOffAll()
{
    bool cardFound;

    do
    {
        cardFound = false;
        int i = 0;
        int j = piles.count();

        while(i < j)
        {
            if (piles[i]->Type() > DEAL && piles[i]->Top())
                cardFound |= PlayOff(piles[i]->Top());
            i++;
        }
    } while (cardFound);
}
