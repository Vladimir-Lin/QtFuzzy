#include <qtfuzzy.h>

QString N::Fuzzy::Rule::FuzzyIF   = "if"   ;
QString N::Fuzzy::Rule::FuzzyIS   = "is"   ;
QString N::Fuzzy::Rule::FuzzyTHEN = "then" ;
QString N::Fuzzy::Rule::FuzzyAND  = "and"  ;
QString N::Fuzzy::Rule::FuzzyOR   = "or"   ;
QString N::Fuzzy::Rule::FuzzyWITH = "with" ;

N::Fuzzy::Rule:: Rule    ( void )
               : _weight ( 1.0  )
{
}

N::Fuzzy::Rule::~Rule(void)
{
}

void N::Fuzzy::Rule::setWeight(double weight)
{
  _weight = weight ;
}

double N::Fuzzy::Rule::getWeight(void) const
{
  return _weight ;
}

double N::Fuzzy::Rule::firingStrength (
        const TNorm * tnorm           ,
        const SNorm * snorm           ) const
{
  return getAntecedent()->firingStrength(tnorm, snorm) * _weight;
}

void N::Fuzzy::Rule::fire(double strength,const TNorm * activation) const
{
  return getConsequent()->fire(strength, activation) ;
}

void N::Fuzzy::Rule::setUnparsedRule(const QString & unparsedRule)
{
  _unparsedRule = unparsedRule ;
}

QString N::Fuzzy::Rule::getUnparsedRule(void) const
{
  return _unparsedRule ;
}

QString N::Fuzzy::Rule::errorString(void) const
{
  return _errorString ;
}

void N::Fuzzy::Rule::setError(QString errString)
{
  _errorString = errString ;
}

QString N::Fuzzy::Rule::logString(void) const
{
  return _logString ;
}

void N::Fuzzy::Rule::log(QString text,bool clearIt)
{
  if (clearIt) _logString = "" ;
  _logString += text           ;
}

QString N::Fuzzy::Rule::toString(void) const
{
  QString R = ""                              ;
  R  = QString("%1 %2 %3 %4"              )
          .arg(FuzzyIF                    )
          .arg(getAntecedent()->toString())
          .arg(FuzzyTHEN                  )
          .arg(getConsequent()->toString())   ;
  if ( ! Operation :: isEq ( _weight, 1.0))   {
    R += QString(" %1 %2"                     )
         .arg(FuzzyWITH                       )
         .arg(QString::number(_weight,'f',5)) ;
  }                                           ;
  return R                                    ;
}

QString N::Fuzzy::Rule::ifKeyword(void)
{
  return N::Fuzzy::Rule::FuzzyIF   ;
}

QString N::Fuzzy::Rule::isKeyword(void)
{
  return N::Fuzzy::Rule::FuzzyIS   ;
}

QString N::Fuzzy::Rule::thenKeyword(void)
{
  return N::Fuzzy::Rule::FuzzyTHEN ;
}

QString N::Fuzzy::Rule::andKeyword(void)
{
  return N::Fuzzy::Rule::FuzzyAND  ;
}

QString N::Fuzzy::Rule::orKeyword(void)
{
  return N::Fuzzy::Rule::FuzzyOR   ;
}

QString N::Fuzzy::Rule::withKeyword(void)
{
  return N::Fuzzy::Rule::FuzzyWITH ;
}
