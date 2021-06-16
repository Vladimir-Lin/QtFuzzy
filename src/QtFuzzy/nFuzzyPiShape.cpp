#include <qtfuzzy.h>

N::Fuzzy::PiShape:: PiShape                     (
                    const QString & name        ,
                    double          bottomLeft  ,
                    double          topLeft     ,
                    double          topRight    ,
                    double          bottomRight )
                  : Term          ( name        )
                  , _bottomLeft   ( bottomLeft  )
                  , _topLeft      ( topLeft     )
                  , _topRight     ( topRight    )
                  , _bottomRight  ( bottomRight )
{
  addMap ( "bottomLeft"  , &_bottomLeft  ) ;
  addMap ( "topLeft"     , &_topLeft     ) ;
  addMap ( "topRight"    , &_topRight    ) ;
  addMap ( "bottomRight" , &_bottomRight ) ;
}

N::Fuzzy::PiShape::~PiShape(void)
{
}

QString N::Fuzzy::PiShape::talk(void) const
{
  return QObject::tr("Pi Shape") ;
}

QString N::Fuzzy::PiShape::className(void) const
{
  return "N::Fuzzy::PiShape" ;
}

N::Fuzzy::PiShape * N::Fuzzy::PiShape::copy(void) const
{
  return new PiShape ( ME ) ;
}

double N::Fuzzy::PiShape::membership(double x) const
{
  if ( Operation :: isNan ( x ) )                              {
    return std::numeric_limits<double>::quiet_NaN()            ;
  }                                                            ;
  //////////////////////////////////////////////////////////////
  double a_b_ave   = (_bottomLeft + _topLeft) / 2.0            ;
  double b_minus_a =  _topLeft    - _bottomLeft                ;
  double c_d_ave   = (_topRight + _bottomRight) / 2.0          ;
  double d_minus_c = _bottomRight - _topRight                  ;
  //////////////////////////////////////////////////////////////
  if ( Operation :: isLE ( x , _bottomLeft ) ) return 0.0 ; else
  if ( Operation :: isLE ( x , a_b_ave     ) )                 {
    return       2.0 * ::pow((x - _bottomLeft) / b_minus_a, 2) ;
  } else
  if ( Operation :: isLt ( x , _topLeft    ) )                 {
    return 1.0 - 2.0 * ::pow((x - _topLeft   ) / b_minus_a, 2) ;
  } else
  if ( Operation :: isLE ( x , _topRight   ) ) return 1.0 ; else
  if ( Operation :: isLE ( x , c_d_ave     ) )                 {
    return 1 -   2.0 * ::pow ((x - _topRight ) / d_minus_c, 2) ;
  } else
  if ( Operation :: isLt ( x , _bottomRight) )                 {
    return       2.0 * ::pow((x - _bottomRight)/ d_minus_c, 2) ;
  }                                                            ;
  //////////////////////////////////////////////////////////////
  return 0.0                                                   ;
}

QString N::Fuzzy::PiShape::toString(int precision) const
{
  QList<double> Vs = Term::values()          ;
  return Term :: toString ( precision , Vs ) ;
}

void N::Fuzzy::PiShape::setBottomLeft(double a)
{
  _bottomLeft = a ;
}

double N::Fuzzy::PiShape::getBottomLeft(void) const
{
  return _bottomLeft ;
}

void N::Fuzzy::PiShape::setTopLeft(double b)
{
  _topLeft = b ;
}

double N::Fuzzy::PiShape::getTopLeft(void) const
{
  return _topLeft ;
}

void N::Fuzzy::PiShape::setTopRight(double d)
{
  _topRight = d ;
}

double N::Fuzzy::PiShape::getTopRight(void) const
{
  return _topRight ;
}

void N::Fuzzy::PiShape::setBottomRight(double c)
{
  _bottomRight = c ;
}

double N::Fuzzy::PiShape::getBottomRight(void) const
{
  return _bottomRight ;
}
