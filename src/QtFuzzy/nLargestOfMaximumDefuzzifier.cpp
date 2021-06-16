#include <qtfuzzy.h>

N::Fuzzy::LargestOfMaximum:: LargestOfMaximum   ( int       divisions )
                           : MaximumDefuzzifier ( LARGEST , divisions )
{
}

N::Fuzzy::LargestOfMaximum:: LargestOfMaximum   (const LargestOfMaximum & lom)
                           : MaximumDefuzzifier ( lom._type , lom.Divisions  )
{
}

N::Fuzzy::LargestOfMaximum::~LargestOfMaximum (void)
{
}

QString N::Fuzzy::LargestOfMaximum::Name(void) const
{
  return QObject :: tr ( "Largest of maximum defuzzifier" ) ;
}
