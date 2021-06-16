#include <qtfuzzy.h>

N::Fuzzy::MamdaniRule:: MamdaniRule (void)
                      : Rule        (    )
                      , _antecedent (NULL)
                      , _consequent (NULL)
{
}

N::Fuzzy::MamdaniRule::~MamdaniRule(void)
{
  if (NotNull(_antecedent)) delete _antecedent ;
  if (NotNull(_consequent)) delete _consequent ;
  _antecedent = NULL                           ;
  _consequent = NULL                           ;
}

void N::Fuzzy::MamdaniRule::setAntecedent(MamdaniAntecedent * antecedent)
{
  _antecedent = antecedent ;
}

N::Fuzzy::MamdaniAntecedent * N::Fuzzy::MamdaniRule::getAntecedent(void) const
{
  return _antecedent ;
}

void N::Fuzzy::MamdaniRule::setConsequent(MamdaniConsequent * consequent)
{
  _consequent = consequent ;
}

N::Fuzzy::MamdaniConsequent * N::Fuzzy::MamdaniRule::getConsequent(void) const
{
  return _consequent ;
}

N::Fuzzy::MamdaniRule * N::Fuzzy::MamdaniRule::parse(const QString & rule,Engine * engine)
{
  enum FSM                                               {
    S_NONE                                               ,
    S_IF                                                 ,
    S_THEN                                               ,
    S_WITH                                               ,
    S_END
  }                                                      ;
  ////////////////////////////////////////////////////////
  MamdaniRule * result = new MamdaniRule ( )             ;
  result -> setUnparsedRule ( rule )                     ;
  ////////////////////////////////////////////////////////
  FSM         state = S_NONE                             ;
  QStringList Token                                      ;
  QString     Rule  = rule                               ;
  QString     ossAntecedent = ""                         ;
  QString     ossConsequent = ""                         ;
  Token = Rule . split ( ' ' )                           ;
  nFullLoop ( i , Token.count() )                        {
    QString t = Token[i]                                 ;
    QString l = t.toLower()                              ;
    if (l.length()<=0) continue                          ;
    switch (state)                                       {
      case S_NONE                                        :
        if (l == FuzzyIF) state = S_IF ; else            {
          result->log                                    (
          QObject::tr("ignored token < %1 > in rule : %2")
                  .arg(t).arg(rule)                    ) ;
        }                                                ;
      break                                              ;
      case S_IF                                          :
        if (l == FuzzyTHEN) state = S_THEN ; else        {
          ossAntecedent += t                             ;
          ossAntecedent += " "                           ;
        }                                                ;
      break                                              ;
      case S_THEN                                        :
        if (l == FuzzyWITH) state = S_WITH ; else        {
          ossConsequent += t                             ;
          ossConsequent += " "                           ;
        }                                                ;
      break                                              ;
      case S_WITH                                        :
        result->setWeight( Operation :: toScalar ( t ) ) ;
        state = S_END                                    ;
      break                                              ;
      case S_END                                         :
        result->_errorString =
        QObject::tr("[syntax error] unexpected token < %1 > after the end of rule")
                .arg(t)                                  ;
      return result                                      ;
    }                                                    ;
  }                                                      ;
  ////////////////////////////////////////////////////////
  if (state == S_NONE)                                   {
    result->_errorString = QObject::tr("[syntax error] keyword < %1 > not found in rule : %2")
                   .arg(FuzzyIF).arg(rule)               ;
    return result                                        ;
  } else if (state == S_IF)                              {
    result->_errorString = QObject::tr("[syntax error] keyword < %1 > not found in rule : %2")
                   .arg(FuzzyTHEN).arg(rule)             ;
    return result                                        ;
  } else if (state == S_WITH)                            {
    result->_errorString = QObject::tr("[syntax error] expected a numeric value as the weight of the rule : %1")
                   .arg(rule)                            ;
    return result                                        ;
  }                                                      ;
  ////////////////////////////////////////////////////////
  result->_antecedent = new MamdaniAntecedent()          ;
  result->_antecedent->load(ossAntecedent,engine)        ;
  ////////////////////////////////////////////////////////
  result->_consequent = new MamdaniConsequent()          ;
  result->_consequent->load(ossConsequent,engine)        ;
  ////////////////////////////////////////////////////////
  return result                                          ;
}
