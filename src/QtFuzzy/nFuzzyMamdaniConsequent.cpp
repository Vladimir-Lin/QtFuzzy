#include <qtfuzzy.h>

N::Fuzzy::MamdaniConsequent:: MamdaniConsequent (void)
                            : Consequent        (    )
{
}

N::Fuzzy::MamdaniConsequent::~MamdaniConsequent (void)
{
  nFullLoop ( i , _conclusions.size() ) {
    delete _conclusions.at(i)           ;
  }                                     ;
  _conclusions . clear ( )              ;
}

QVector<N::Fuzzy::MamdaniProposition *> N::Fuzzy::MamdaniConsequent::conclusions(void) const
{
  return _conclusions ;
}

void N::Fuzzy::MamdaniConsequent::fire(double strength,const TNorm * activation)
{
  nFullLoop ( i , _conclusions.size() )                                     {
    MamdaniProposition * proposition = _conclusions.at(i)                   ;
    double threshold = strength                                             ;
    nFullLoop ( h , proposition->hedges.size() )                            {
      threshold = proposition->hedges.at(h)->hedge(threshold)               ;
    }                                                                       ;
    Thresholded * term = new Thresholded(_conclusions.at(i)->term)          ;
    term -> setThreshold  ( threshold  )                                    ;
    term -> setActivation ( activation )                                    ;
    OutputVariable * outputVariable                                         ;
    outputVariable  = dynamic_cast<OutputVariable *>(proposition->variable) ;
    outputVariable -> output()->addTerm(term)                               ;
  }                                                                         ;
}

bool N::Fuzzy::MamdaniConsequent::evaluate(const QString & consequent,Engine * engine)
{ Q_UNUSED ( consequent ) ;
  Q_UNUSED ( engine     ) ;
  return false            ;
}

void N::Fuzzy::MamdaniConsequent::load(const QString & consequent,Engine * engine)
{
  /***********************************************************
     Extracts the list of propositions from the consequent
     The rules are:
     1) After a variable comes 'is',
     2) After 'is' comes a hedge or a term
     3) After a hedge comes a hedge or a term
     4) After a term comes operators 'and' or 'with'
     5) After operator 'and' comes a variable
     6) After operator 'with' comes a float
   ***********************************************************/
  /////////////////////////////////////////////////////////////
  enum FSM                                                    {
    S_VARIABLE =  1                                           ,
    S_IS       =  2                                           ,
    S_HEDGE    =  4                                           ,
    S_TERM     =  8                                           ,
    S_AND      = 16
  }                                                           ;
  int state = S_VARIABLE                                      ;
  /////////////////////////////////////////////////////////////
  MamdaniProposition * proposition = NULL                     ;
  QStringList          Token = consequent.split(' ')          ;
  _conclusions . clear ( )                                    ;
  /////////////////////////////////////////////////////////////
  nFullLoop ( i , Token.count() )                             {
    QString t = Token [i]                                     ;
    QString l = t.toLower()                                   ;
    if (l.length()<=0) continue                               ;
    if (IsMask(state,S_VARIABLE))                             {
      if (engine->hasOutputVariable(t))                       {
        proposition = new MamdaniProposition()                ;
        proposition->variable = engine->getOutputVariable(t)  ;
        _conclusions.push_back(proposition)                   ;
        state = S_IS                                          ;
        continue                                              ;
      }                                                       ;
    }                                                         ;
    ///////////////////////////////////////////////////////////
    if (IsMask(state,S_IS))                                   {
      if (l == Rule::FuzzyIS)                                 {
        state = S_HEDGE | S_TERM                              ;
        continue                                              ;
      }                                                       ;
    }                                                         ;
    ///////////////////////////////////////////////////////////
    if (IsMask(state,S_HEDGE))                                {
      if (engine->hasHedge(t))                                {
        Hedge * hedge = engine->getHedge(t)                   ;
        proposition->hedges.push_back(hedge)                  ;
        state = S_HEDGE | S_TERM                              ;
        continue                                              ;
      }                                                       ;
    }                                                         ;
    ///////////////////////////////////////////////////////////
    if (IsMask(state,S_TERM))                                 {
      if (proposition->variable->hasTerm(t))                  {
        proposition->term = proposition->variable->getTerm(t) ;
        state = S_AND                                         ;
        continue                                              ;
      }                                                       ;
    }                                                         ;
    ///////////////////////////////////////////////////////////
    if (IsMask(state,S_AND))                                  {
      if (l == Rule::FuzzyAND)                                {
        state = S_VARIABLE                                    ;
        continue                                              ;
      }                                                       ;
    }                                                         ;
    ///////////////////////////////////////////////////////////
    //if reached this point, there was an error:
    if (IsMask(state,S_VARIABLE))                             {
      QString es                                              ;
      es = QObject::tr("[syntax error] expected output variable, but found < %1 >")
              .arg(t)                                         ;
      engine->setError(es)                                    ;
      return                                                  ;
    }                                                         ;
    ///////////////////////////////////////////////////////////
    if (IsMask(state,S_IS))                                   {
      QString es                                              ;
      es = QObject::tr("[syntax error] expected keyword < %1 >, but found < %2 >")
              .arg(Rule::FuzzyIS                              )
              .arg(t)                                         ;
      engine->setError(es)                                    ;
      return                                                  ;
    }                                                         ;
    ///////////////////////////////////////////////////////////
    if ((IsMask(state,S_HEDGE)) || (IsMask(state,S_TERM)))    {
      QString es                                              ;
      es = QObject::tr("[syntax error] expected hedge or term, but found < %1 >")
              .arg(t)                                         ;
      engine->setError(es)                                    ;
      return                                                  ;
    }                                                         ;
    ///////////////////////////////////////////////////////////
    if (IsMask(state,S_AND))                                  {
      QString es                                              ;
      es = QObject::tr("[syntax error] expected operator < %1 >, but found < %2 >")
              .arg(Rule::FuzzyAND                             )
              .arg(t)                                         ;
      engine->setError(es)                                    ;
      return                                                  ;
    }                                                         ;
    ///////////////////////////////////////////////////////////
    {
      QString es                                              ;
      es = QObject::tr("[syntax error] unexpected token < %1 >")
              .arg(t)                                         ;
      engine->setError(es)                                    ;
      return                                                  ;
    }                                                         ;
  }                                                           ;
}

QString N::Fuzzy::MamdaniConsequent::toString(void) const
{
  QString     J = QString(" %1 ").arg(Rule::FuzzyAND) ;
  QString     R                                       ;
  QStringList L                                       ;
  nFullLoop ( i , _conclusions.size() )               {
    L << _conclusions.at(i)->toString()               ;
  }                                                   ;
  R = L . join ( J )                                  ;
  return R                                            ;
}
