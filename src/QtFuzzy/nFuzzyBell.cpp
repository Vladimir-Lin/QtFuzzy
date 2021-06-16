#include <qtfuzzy.h>

N::Fuzzy::Bell:: Bell                   (
                 const QString & name   ,
                 double          center ,
                 double          width  ,
                 double          slope  )
               : Term    ( name         )
               , _center ( center       )
               , _width  ( width        )
               , _slope  ( slope        )
{
  addMap ( "center" , &_center ) ;
  addMap ( "width"  , &_width  ) ;
  addMap ( "slope"  , &_slope  ) ;
}

N::Fuzzy::Bell::~Bell(void)
{
}

QString N::Fuzzy::Bell::talk(void) const
{
  return QObject::tr("Bell") ;
}

QString N::Fuzzy::Bell::className(void) const
{
  return "N::Fuzzy::Bell" ;
}

N::Fuzzy::Bell * N::Fuzzy::Bell::copy(void) const
{
  return new Bell ( ME ) ;
}

double N::Fuzzy::Bell::membership(double x) const
{
  if ( Operation :: isNan ( x ) )                                       {
    return std::numeric_limits<double>::quiet_NaN()                     ;
  }                                                                     ;
  return 1.0 / (1.0 + ::pow(::abs((x - _center) / _width), 2 * _slope)) ;
}

QString N::Fuzzy::Bell::toString(int precision) const
{
  QList<double> Vs = Term::values()   ;
  return Term::toString(precision,Vs) ;
}

void N::Fuzzy::Bell::setWidth(double a)
{
  _width = a ;
}

double N::Fuzzy::Bell::getWidth(void) const
{
  return _width ;
}

void N::Fuzzy::Bell::setSlope(double b)
{
  _slope = b ;
}

double N::Fuzzy::Bell::getSlope(void) const
{
  return _slope ;
}

void N::Fuzzy::Bell::setCenter(double c)
{
  _center = c ;
}

double N::Fuzzy::Bell::getCenter(void) const
{
  return _center ;
}
