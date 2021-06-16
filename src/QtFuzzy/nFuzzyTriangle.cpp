#include <qtfuzzy.h>

N::Fuzzy::Triangle:: Triangle             (
                     const QString & name ,
                     double          a    ,
                     double          b    ,
                     double          c    )
                   : Term          ( name )
                   , _a            ( a    )
                   , _b            ( b    )
                   , _c            ( c    )
{
  addMap ( "a" , &_a ) ;
  addMap ( "b" , &_b ) ;
  addMap ( "c" , &_c ) ;
}

N::Fuzzy::Triangle::~Triangle(void)
{
}

QString N::Fuzzy::Triangle::talk(void) const
{
  return QObject :: tr ( "Triangle" ) ;
}

QString N::Fuzzy::Triangle::className(void) const
{
  return "N::Fuzzy::Triangle" ;
}

N::Fuzzy::Triangle * N::Fuzzy::Triangle::copy(void) const
{
  return new Triangle ( ME ) ;
}

double N::Fuzzy::Triangle::membership(double x) const
{
  if ( Operation :: isNan ( x ) )                   {
    return std::numeric_limits<double>::quiet_NaN() ;
  }                                                 ;
  ///////////////////////////////////////////////////
  double minimum = _a                               ;
  double maximum = _c                               ;
  ///////////////////////////////////////////////////
  if ( Operation :: isLE ( x , minimum )           ||
       Operation :: isGE ( x , maximum )          ) {
    return 0.0                                      ;
  } else
  if ( Operation :: isEq ( x , _b      )          ) {
    return 1.0                                      ;
  } else
  if ( Operation :: isLt ( x , _b      )          ) {
    return ( x - minimum ) / ( _b - minimum )       ;
  } else return ( maximum - x ) / ( maximum - _b )  ;
}

QString N::Fuzzy::Triangle::toString(int precision) const
{
  QList<double> Vs = Term::values()          ;
  return Term :: toString ( precision , Vs ) ;
}

void N::Fuzzy::Triangle::setA(double a)
{
  _a = a ;
}

double N::Fuzzy::Triangle::getA(void) const
{
  return _a ;
}

void N::Fuzzy::Triangle::setB(double b)
{
  _b = b ;
}

double N::Fuzzy::Triangle::getB(void) const
{
  return _b ;
}

void N::Fuzzy::Triangle::setC(double c)
{
  _c = c ;
}

double N::Fuzzy::Triangle::getC(void) const
{
  return _c ;
}
