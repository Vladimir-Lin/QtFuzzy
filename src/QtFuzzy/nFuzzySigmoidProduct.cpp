#include <qtfuzzy.h>

N::Fuzzy::SigmoidProduct:: SigmoidProduct          (
                           const QString & name    ,
                           double          left    ,
                           double          rising  ,
                           double          falling ,
                           double          right   )
                         : Term          ( name    )
                         , _left         ( left    )
                         , _rising       ( rising  )
                         , _falling      ( falling )
                         , _right        ( right   )
{
  addMap ( "left"    , &_left    ) ;
  addMap ( "rising"  , &_rising  ) ;
  addMap ( "falling" , &_falling ) ;
  addMap ( "right"   , &_right   ) ;
}

N::Fuzzy::SigmoidProduct::~SigmoidProduct(void)
{
}

QString N::Fuzzy::SigmoidProduct::talk(void) const
{
  return QObject::tr("Sigmoid Product") ;
}

QString N::Fuzzy::SigmoidProduct::className(void) const
{
  return "N::Fuzzy::SigmoidProduct" ;
}

N::Fuzzy::SigmoidProduct * N::Fuzzy::SigmoidProduct::copy(void) const
{
  return new SigmoidProduct ( ME ) ;
}

double N::Fuzzy::SigmoidProduct::membership(double x) const
{
  double a = 1.0 / (1 + ::exp(-_rising  * (x - _left )) ) ;
  double b = 1.0 / (1 + ::exp(-_falling * (x - _right)) ) ;
  return ( a * b )                                        ;
}

QString N::Fuzzy::SigmoidProduct::toString(int precision) const
{
  QList<double> Vs = Term::values()          ;
  return Term :: toString ( precision , Vs ) ;
}

void N::Fuzzy::SigmoidProduct::setRising(double risingSlope)
{
  _rising = risingSlope ;
}

double N::Fuzzy::SigmoidProduct::getRising(void) const
{
  return _rising ;
}

void N::Fuzzy::SigmoidProduct::setLeft(double leftInflection)
{
  _left = leftInflection ;
}

double N::Fuzzy::SigmoidProduct::getLeft(void) const
{
  return _left ;
}

void N::Fuzzy::SigmoidProduct::setRight(double rightInflection)
{
  _right = rightInflection;
}

double N::Fuzzy::SigmoidProduct::getRight(void) const
{
  return _right ;
}

void N::Fuzzy::SigmoidProduct::setFalling(double fallingSlope)
{
  _falling = fallingSlope ;
}

double N::Fuzzy::SigmoidProduct::getFalling(void) const
{
  return _falling ;
}
