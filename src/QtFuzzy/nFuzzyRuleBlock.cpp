#include <qtfuzzy.h>

N::Fuzzy::RuleBlock:: RuleBlock   ( const QString & name )
                    : _name       (                 name )
                    , _tnorm      ( NULL                 )
                    , _snorm      ( NULL                 )
                    , _activation ( NULL                 )
{
}

N::Fuzzy::RuleBlock::~RuleBlock(void)
{
  nFullLoop ( i , _rules.size() ) delete _rules.at(i) ;
}

void N::Fuzzy::RuleBlock::fireRules(void)
{
  nFullLoop ( i , _rules.size() )                                 {
    double strength = _rules.at(i)->firingStrength(_tnorm,_snorm) ;
    if ( Operation :: isGt ( strength , 0.0 ) )                   {
      _rules.at(i)->fire(strength, _activation)                   ;
    }                                                             ;
  }                                                               ;
}

void N::Fuzzy::RuleBlock::setName(QString name)
{
  _name = name ;
}

QString N::Fuzzy::RuleBlock::getName(void) const
{
  return _name ;
}

void N::Fuzzy::RuleBlock::setTnorm(const TNorm * tnorm)
{
  if (NotNull(_tnorm)) delete _tnorm ;
  _tnorm = tnorm                     ;
}

const N::Fuzzy::TNorm * N::Fuzzy::RuleBlock::getTnorm(void) const
{
  return _tnorm ;
}

void N::Fuzzy::RuleBlock::setSnorm(const SNorm * snorm)
{
  if (NotNull(_snorm)) delete _snorm ;
  _snorm = snorm                     ;
}

const N::Fuzzy::SNorm * N::Fuzzy::RuleBlock::getSnorm(void) const
{
  return _snorm ;
}

void N::Fuzzy::RuleBlock::setActivation(const TNorm * activation)
{
  if (NotNull(_activation)) delete _activation ;
  _activation = activation                     ;
}

const N::Fuzzy::TNorm * N::Fuzzy::RuleBlock::getActivation(void) const
{
  return _activation;
}

QString N::Fuzzy::RuleBlock::toString(void) const
{
  QString R = ""                                                ;
  R += QString("name='%1' "     ).arg(_name                   ) ;
  R += QString("tnorm='%1' "    ).arg(_tnorm     ->className()) ;
  R += QString("snorm='%1' "    ).arg(_snorm     ->className()) ;
  R += QString("activation='%1'").arg(_activation->className()) ;
  return R                                                      ;
}

void N::Fuzzy::RuleBlock::addRule(Rule * rule)
{
  _rules . push_back ( rule ) ;
}

void N::Fuzzy::RuleBlock::insertRule(Rule * rule, int index)
{
  _rules . insert ( index , rule ) ;
}

N::Fuzzy::Rule * N::Fuzzy::RuleBlock::getRule(int index) const
{
  return _rules.at(index) ;
}

N::Fuzzy::Rule * N::Fuzzy::RuleBlock::removeRule(int index)
{
  Rule * result = _rules.at(index) ;
  _rules . remove ( index )        ;
  return result                    ;
}

int N::Fuzzy::RuleBlock::numberOfRules(void) const
{
  return _rules . size() ;
}

const QVector<N::Fuzzy::Rule*> & N::Fuzzy::RuleBlock::rules(void) const
{
  return _rules ;
}
