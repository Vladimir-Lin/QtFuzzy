#include <qtfuzzy.h>

N::Fuzzy::SigmoidDifference:: SigmoidDifference       (
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

N::Fuzzy::SigmoidDifference::~SigmoidDifference(void)
{
}

QString N::Fuzzy::SigmoidDifference::talk(void) const
{
  return QObject::tr("Sigmoid difference") ;
}

QString N::Fuzzy::SigmoidDifference::className(void) const
{
  return "N::Fuzzy::SigmoidDifference" ;
}

N::Fuzzy::SigmoidDifference * N::Fuzzy::SigmoidDifference::copy(void) const
{
  return new N::Fuzzy::SigmoidDifference ( ME ) ;
}

double N::Fuzzy::SigmoidDifference::membership(double x) const
{
  if ( Operation :: isNan ( x ) )                         {
    return std::numeric_limits<double>::quiet_NaN()       ;
  }                                                       ;
  double a = 1.0 / (1 + ::exp(-_rising  * (x - _left )) ) ;
  double b = 1.0 / (1 + ::exp(-_falling * (x - _right)) ) ;
  return ::abs ( a - b )                                  ;
}

QString N::Fuzzy::SigmoidDifference::toString(int precision) const
{
  QList<double> Vs = Term::values()          ;
  return Term :: toString ( precision , Vs ) ;
}

void N::Fuzzy::SigmoidDifference::setLeft(double leftInflection)
{
  _left = leftInflection ;
}

double N::Fuzzy::SigmoidDifference::getLeft(void) const
{
  return _left ;
}

void N::Fuzzy::SigmoidDifference::setRising(double risingSlope)
{
  _rising = risingSlope ;
}

double N::Fuzzy::SigmoidDifference::getRising(void) const
{
  return _rising ;
}

void N::Fuzzy::SigmoidDifference::setFalling(double fallingSlope)
{
  _falling = fallingSlope ;
}

double N::Fuzzy::SigmoidDifference::getFalling(void) const
{
  return _falling ;
}

void N::Fuzzy::SigmoidDifference::setRight(double rightInflection)
{
  _right = rightInflection ;
}

double N::Fuzzy::SigmoidDifference::getRight(void) const
{
  return _right ;
}

