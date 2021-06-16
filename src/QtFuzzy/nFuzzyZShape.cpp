#include <qtfuzzy.h>

N::Fuzzy::ZShape:: ZShape                (
                   const QString & name  ,
                   double          start ,
                   double          end   )
                 : Term          ( name  )
                 , _start        ( start )
                 , _end          ( end   )
{
  addMap ( "start" , &_start ) ;
  addMap ( "end"   , &_end   ) ;
}

N::Fuzzy::ZShape::~ZShape(void)
{
}

QString N::Fuzzy::ZShape::talk(void) const
{
  return QObject :: tr ( "Z Shape" ) ;
}

QString N::Fuzzy::ZShape::className(void) const
{
  return "N::Fuzzy::ZShape" ;
}

N::Fuzzy::ZShape * N::Fuzzy::ZShape::copy(void) const
{
  return new ZShape ( ME ) ;
}

double N::Fuzzy::ZShape::membership(double x) const
{
  if ( Operation :: isNan ( x ) )                          {
    return std::numeric_limits<double>::quiet_NaN()        ;
  }                                                        ;
  //////////////////////////////////////////////////////////
  double average    = (_start + _end   ) / 2               ;
  double difference =  _end   - _start                     ;
  //////////////////////////////////////////////////////////
  if ( Operation :: isLE ( x , _start  ) )                 {
    return 1.0                                             ;
  } else
  if ( Operation :: isLE ( x , average ) )                 {
    return 1.0 - 2.0 * ::pow((x - _start) / difference, 2) ;
  } else
  if ( Operation :: isLt ( x , _end    ) )                 {
    return 2.0 * ::pow((x - _end) / difference, 2)         ;
  }                                                        ;
  //////////////////////////////////////////////////////////
  return 0.0                                               ;
}

QString N::Fuzzy::ZShape::toString(int precision) const
{
  QList<double> Vs = Term::values()          ;
  return Term :: toString ( precision , Vs ) ;
}

void N::Fuzzy::ZShape::setStart(double start)
{
  _start = start ;
}

double N::Fuzzy::ZShape::getStart(void) const
{
  return _start ;
}

void N::Fuzzy::ZShape::setEnd(double end)
{
  _end = end ;
}

double N::Fuzzy::ZShape::getEnd(void) const
{
  return _end ;
}
