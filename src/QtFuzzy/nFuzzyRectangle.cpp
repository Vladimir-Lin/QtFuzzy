#include <qtfuzzy.h>

N::Fuzzy::Rectangle:: Rectangle               (
                      const QString & name    ,
                      double          minimum ,
                      double          maximum )
                    : Term          ( name    )
                    , _minimum      ( minimum )
                    , _maximum      ( maximum )
{
  addMap ( "minimum" , &_minimum ) ;
  addMap ( "maximum" , &_maximum ) ;
}

N::Fuzzy::Rectangle::~Rectangle(void)
{
}

QString N::Fuzzy::Rectangle::talk(void) const
{
  return QObject::tr("Rectangle") ;
}

QString N::Fuzzy::Rectangle::className(void) const
{
  return "N::Fuzzy::Rectangle" ;
}

N::Fuzzy::Rectangle * N::Fuzzy::Rectangle::copy(void) const
{
  return new Rectangle ( ME ) ;
}

double N::Fuzzy::Rectangle::membership(double x) const
{
  if ( Operation :: isNan ( x ) )                      {
    return std::numeric_limits<double>::quiet_NaN()    ;
  }                                                    ;
  if ( Operation :: isLt ( x , _minimum )             ||
       Operation :: isGt ( x , _maximum ) ) return 0.0 ;
  return 1.0                                           ;
}

QString N::Fuzzy::Rectangle::toString(int precision) const
{
  QList<double> Vs = Term::values()          ;
  return Term :: toString ( precision , Vs ) ;
}

void N::Fuzzy::Rectangle::setMinimum(double minimum)
{
  _minimum = minimum ;
}

double N::Fuzzy::Rectangle::getMinimum(void) const
{
  return _minimum ;
}

void N::Fuzzy::Rectangle::setMaximum(double maximum)
{
  _maximum = maximum ;
}

double N::Fuzzy::Rectangle::getMaximum(void) const
{
  return _maximum ;
}
