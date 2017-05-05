#ifndef RULE_H
#define RULE_H

class Pile;
class Card;

class Rule
{
public:
    virtual bool Enforce(Pile*, Card*) = 0;
};

class RuleBaseNone : public Rule
{
    bool Enforce(Pile*, Card*);
};

class RuleBaseAce : public Rule
{
    bool Enforce(Pile*, Card*);
};

class RuleBaseKing : public Rule
{
    bool Enforce(Pile*, Card*);
};

class RuleNoStack : public Rule
{
    bool Enforce(Pile*, Card*);
};

class  RuleStackSameSuit : public Rule
{
    bool Enforce(Pile*, Card*);
};

class RuleStackAlternateColor  : public Rule
{
    bool Enforce(Pile*, Card*);
};

class RuleStackMinusOne : public Rule
{
    bool Enforce(Pile*, Card*);
};

class RuleStackPlusOne : public Rule
{
    bool Enforce(Pile*, Card*);
};

class RuleStackAny : public Rule
{
    bool Enforce(Pile*, Card*);
};

class RuleStackNone : public Rule
{
    bool Enforce(Pile*, Card*);
};

class  RuleStackOneAtATime : public Rule
{
    bool Enforce(Pile*, Card*);
};

class  RuleStack13 : public Rule
{
    bool Enforce(Pile*, Card*);
};

class  RuleStackLengthLimited : public Rule
{
    bool Enforce(Pile*, Card*);
};

class  RuleMoveSameSuit : public Rule
{
    bool Enforce(Pile*, Card*);
};

class  RuleMoveAltColor : public Rule
{
    bool Enforce(Pile*, Card*);
};

class  RuleMoveSeqDecreasing : public Rule
{
    bool Enforce(Pile*, Card*);
};

class  RuleMoveSeqIncreasing : public Rule
{
    bool Enforce(Pile*, Card*);
};

class  RuleMoveLenghtLimited : public Rule
{
    bool Enforce(Pile*, Card*);
};

class  RuleMoveNone : public Rule
{
    bool Enforce(Pile*, Card*);
};

class  RuleMoveOneAtATime : public Rule
{
    bool Enforce(Pile*, Card*);
};

class RuleStackSameSlot : public Rule
{
    bool Enforce(Pile*, Card*);
};
#endif // RULE_H
