#include <qtfuzzy.h>

N::Fuzzy::Sigmoid:: Sigmoid                    (
                    const QString & name       ,
                    double          inflection ,
                    double          slope      )
                  : Term          ( name       )
                  , _inflection   ( inflection )
                  , _slope        ( slope      )
{
  addMap ( "inflection" , &_inflection ) ;
  addMap ( "slope"      , &_slope      ) ;
}

N::Fuzzy::Sigmoid::~Sigmoid(void)
{
}

QString N::Fuzzy::Sigmoid::talk(void) const
{
  return QObject::tr("Sigmoid") ;
}

QString N::Fuzzy::Sigmoid::className(void) const
{
  return "N::Fuzzy::Sigmoid" ;
}

N::Fuzzy::Sigmoid * N::Fuzzy::Sigmoid::copy(void) const
{
  return new Sigmoid ( ME ) ;
}

double N::Fuzzy::Sigmoid::membership(double x) const
{
  if ( Operation :: isNan ( x ) )                         {
    return std::numeric_limits<double>::quiet_NaN()       ;
  }                                                       ;
  return 1.0 / (1.0 + ::exp(-_slope * (x - _inflection))) ;
}

QString N::Fuzzy::Sigmoid::toString(int precision) const
{
  QList<double> Vs = Term::values()          ;
  return Term :: toString ( precision , Vs ) ;
}

void N::Fuzzy::Sigmoid::setSlope(double a)
{
  _slope = a ;
}

double N::Fuzzy::Sigmoid::getSlope(void) const
{
  return _slope ;
}

void N::Fuzzy::Sigmoid::setInflection(double c)
{
  _inflection = c ;
}

double N::Fuzzy::Sigmoid::getInflection(void) const
{
  return _inflection ;
}
