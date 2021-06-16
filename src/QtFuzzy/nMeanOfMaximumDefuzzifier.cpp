#include <qtfuzzy.h>

N::Fuzzy::MeanOfMaximum:: MeanOfMaximum      ( int    divisions )
                        : MaximumDefuzzifier ( MEAN , divisions )
{
}

N::Fuzzy::MeanOfMaximum:: MeanOfMaximum      ( const MeanOfMaximum & mom )
                        : MaximumDefuzzifier ( mom._type , mom.Divisions )
{
}

N::Fuzzy::MeanOfMaximum::~MeanOfMaximum (void)
{
}

QString N::Fuzzy::MeanOfMaximum::Name(void) const
{
  return QObject :: tr ( "Mean of maximum defuzzifier" ) ;
}
