#include <qtfuzzy.h>

N::Fuzzy::SmallestOfMaximum:: SmallestOfMaximum  ( int        divisions )
                            : MaximumDefuzzifier ( SMALLEST , divisions )
{
}

N::Fuzzy::SmallestOfMaximum:: SmallestOfMaximum  (const SmallestOfMaximum & som)
                            : MaximumDefuzzifier (som._type , som.Divisions    )
{
}

N::Fuzzy::SmallestOfMaximum::~SmallestOfMaximum (void)
{
}

QString N::Fuzzy::SmallestOfMaximum::Name(void) const
{
  return QObject :: tr ( "Smallest of maximum defuzzifier" ) ;
}
