#include <qtfuzzy.h>

N::Fuzzy::SShape:: SShape                (
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

N::Fuzzy::SShape::~SShape(void)
{
}

QString N::Fuzzy::SShape::talk(void) const
{
  return QObject::tr("S Shape") ;
}

QString N::Fuzzy::SShape::className(void) const
{
  return "N::Fuzzy::SShape" ;
}

N::Fuzzy::SShape * N::Fuzzy::SShape::copy(void) const
{
  return new SShape ( ME ) ;
}

double N::Fuzzy::SShape::membership(double x) const
{
  if ( Operation :: isNan ( x ) )                          {
    return std::numeric_limits<double>::quiet_NaN()        ;
  }                                                        ;
  //////////////////////////////////////////////////////////
  double average    = ( _start + _end   ) / 2              ;
  double difference =   _end   - _start                    ;
  //////////////////////////////////////////////////////////
  if ( Operation :: isLE ( x , _start  ) ) return 0.0 ; else
  if ( Operation :: isLE ( x , average ) )                 {
    return 2 * ::pow((x - _start) / difference, 2)         ;
  } else
  if ( Operation :: isLt ( x , _end    ) )                 {
    return 1.0 - 2.0 * ::pow((x - _end) / difference, 2)   ;
  }                                                        ;
  //////////////////////////////////////////////////////////
  return 1.0                                               ;
}

QString N::Fuzzy::SShape::toString(int precision) const
{
  QList<double> Vs = Term::values()          ;
  return Term :: toString ( precision , Vs ) ;
}

void N::Fuzzy::SShape::setStart(double start)
{
  _start = start ;
}

double N::Fuzzy::SShape::getStart(void) const
{
  return _start ;
}

void N::Fuzzy::SShape::setEnd(double end)
{
  _end = end ;
}

double N::Fuzzy::SShape::getEnd(void) const
{
  return _end ;
}
