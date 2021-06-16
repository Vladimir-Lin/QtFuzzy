#include <qtfuzzy.h>

N::Fuzzy::Ramp:: Ramp   (const QString & name,double start,double end)
               : Term   (                name                        )
               , _start (                            start           )
               , _end   (                                         end)
{
  addMap ( "start" , &_start ) ;
  addMap ( "end"   , &_end   ) ;
}

N::Fuzzy::Ramp::~Ramp(void)
{
}

QString N::Fuzzy::Ramp::talk(void) const
{
  return QObject::tr("Ramp") ;
}

QString N::Fuzzy::Ramp::className(void) const
{
  return "N::Fuzzy::Ramp" ;
}

N::Fuzzy::Ramp * N::Fuzzy::Ramp::copy(void) const
{
  return new Ramp ( ME ) ;
}

double N::Fuzzy::Ramp::membership(double x) const
{
  if ( Operation :: isNan ( x ) )                           {
    return std::numeric_limits<double>::quiet_NaN()         ;
  }                                                         ;
  if ( Operation   :: isEq ( _start , _end   ) ) return 0.0 ;
  if ( Operation   :: isLt ( _start , _end   ) )            {
    if ( Operation :: isLE ( x      , _start ) ) return 0.0 ;
    if ( Operation :: isGE ( x      , _end   ) ) return 1.0 ;
    return ( x - _start ) / ( _end - _start  )              ;
  } else                                                    {
    if ( Operation :: isGE ( x      , _start ) ) return 0.0 ;
    if ( Operation :: isLE ( x      , _end   ) ) return 1.0 ;
    return ( _start - x ) / ( _start - _end  )              ;
  }                                                         ;
}

QString N::Fuzzy::Ramp::toString(int precision) const
{
  QList<double> Vs = Term::values()          ;
  return Term :: toString ( precision , Vs ) ;
}

void N::Fuzzy::Ramp::setStart(double start)
{
  _start = start ;
}

double N::Fuzzy::Ramp::getStart(void) const
{
  return _start ;
}

void N::Fuzzy::Ramp::setEnd(double end)
{
  _end = end ;
}

double N::Fuzzy::Ramp::getEnd(void) const
{
  return _end ;
}
