#include <qtfuzzy.h>

N::Fuzzy::Trapezoid:: Trapezoid            (
                      const QString & name ,
                      double          a    ,
                      double          b    ,
                      double          c    ,
                      double          d    )
                    : Term          ( name )
                    , _a            ( a    )
                    , _b            ( b    )
                    , _c            ( c    )
                    , _d            ( d    )
{
  addMap ( "a" , &_a ) ;
  addMap ( "b" , &_b ) ;
  addMap ( "c" , &_c ) ;
  addMap ( "d" , &_d ) ;
}

N::Fuzzy::Trapezoid::~Trapezoid(void)
{
}

QString N::Fuzzy::Trapezoid::talk(void) const
{
  return QObject::tr("Trapezoid") ;
}

QString N::Fuzzy::Trapezoid::className(void) const
{
  return "N::Fuzzy::Trapezoid" ;
}

N::Fuzzy::Trapezoid * N::Fuzzy::Trapezoid::copy(void) const
{
  return new Trapezoid ( ME ) ;
}

double N::Fuzzy::Trapezoid::membership(double x) const
{
  if ( Operation :: isNan ( x ) )                   {
    return std::numeric_limits<double>::quiet_NaN() ;
  }                                                 ;
  ///////////////////////////////////////////////////
  double minimum = _a                               ;
  double maximum = _d                               ;
  ///////////////////////////////////////////////////
  if ( Operation :: isLE ( x , minimum )           ||
       Operation :: isGE ( x , maximum )          ) {
    return 0.0                                      ;
  } else
  if ( Operation :: isLE ( x , _b      )          ) {
    return ( x - minimum ) / ( _b - minimum )       ;
  } else
  if ( Operation :: isLE ( x , _c      )          ) {
    return 1.0                                      ;
  } else
  if ( Operation :: isLE ( x , maximum )          ) {
    return ( maximum - x ) / ( maximum - _c )       ;
  } else return 0.0                                 ;
}

QString N::Fuzzy::Trapezoid::toString(int precision) const
{
  QList<double> Vs = Term::values()          ;
  return Term :: toString ( precision , Vs ) ;
}

void N::Fuzzy::Trapezoid::setA(double a)
{
  _a = a ;
}

double N::Fuzzy::Trapezoid::getA(void) const
{
  return _a ;
}

void N::Fuzzy::Trapezoid::setB(double b)
{
  _b = b ;
}

double N::Fuzzy::Trapezoid::getB(void) const
{
  return _b ;
}

void N::Fuzzy::Trapezoid::setC(double c)
{
  _c = c ;
}

double N::Fuzzy::Trapezoid::getC(void) const
{
  return _c ;
}

void N::Fuzzy::Trapezoid::setD(double d)
{
  _d = d ;
}

double N::Fuzzy::Trapezoid::getD(void) const
{
  return _d ;
}
