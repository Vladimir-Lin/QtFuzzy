#include <qtfuzzy.h>

N::Fuzzy::MaximumDefuzzifier:: MaximumDefuzzifier      (
                               enum FmdTypes type      ,
                               int           divisions )
                             : Defuzzifier ( divisions )
                             , _type       ( type      )
{
}

N::Fuzzy::MaximumDefuzzifier:: MaximumDefuzzifier(const MaximumDefuzzifier & m)
                             : Defuzzifier       (m.Divisions                 )
                             , _type             (m._type                     )
{
}

N::Fuzzy::MaximumDefuzzifier::~MaximumDefuzzifier(void)
{
}

QString N::Fuzzy::MaximumDefuzzifier::Name(void) const
{
  return QObject::tr("Maximum defuzzifier") ;
}

QString N::Fuzzy::MaximumDefuzzifier::className(void) const
{
  switch (_type)                                         {
    case SMALLEST : return "N::Fuzzy::SmallestOfMaximum" ;
    case LARGEST  : return "N::Fuzzy::LargestOfMaximum"  ;
    case MEAN     : return "N::Fuzzy::MeanOfMaximum"     ;
  }                                                      ;
  return ""                                              ;
}

double N::Fuzzy::MaximumDefuzzifier::defuzzify (
         const Term * term                     ,
         double       minimum                  ,
         double       maximum                  ) const
{
  nKickOut ( (maximum - minimum > Divisions) , 0 )         ;
  //////////////////////////////////////////////////////////
  double dx        = (maximum - minimum) / Divisions       ;
  double ymax      = -1.0                                  ;
  double xsmallest                                         ;
  double xlargest                                          ;
  double x                                                 ;
  double y                                                 ;
  //////////////////////////////////////////////////////////
  bool samePlateau = false                                 ;
  nFullLoop ( i , Divisions )                              {
    x = minimum + (i + 0.5) * dx                           ;
    y = term->membership(x)                                ;
    ////////////////////////////////////////////////////////
    if ( Operation :: isGt (y, ymax))                      {
      xsmallest   = x                                      ;
      ymax        = y                                      ;
      samePlateau = true                                   ;
    } else
    if ( Operation :: isEq (y, ymax) && samePlateau)       {
      xlargest    = x                                      ;
    } else
    if ( Operation :: isLt (y, ymax))                      {
      samePlateau = false                                  ;
    }                                                      ;
  }                                                        ;
  //////////////////////////////////////////////////////////
  switch (_type)                                           {
     case SMALLEST : return              xsmallest         ;
     case LARGEST  : return   xlargest                     ;
     case MEAN     : return ( xlargest + xsmallest ) / 2.0 ;
  }                                                        ;
  //////////////////////////////////////////////////////////
  return std::numeric_limits<double>::quiet_NaN()          ;
}

void N::Fuzzy::MaximumDefuzzifier::setType(enum FmdTypes type)
{
  _type = type ;
}

N::Fuzzy::MaximumDefuzzifier::FmdTypes N::Fuzzy::MaximumDefuzzifier::getType(void) const
{
  return _type ;
}
