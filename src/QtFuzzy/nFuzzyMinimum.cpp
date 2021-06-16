#include <qtfuzzy.h>

N::Fuzzy::Minimum:: Minimum (void)
                  : TNorm   (    )
{
}

N::Fuzzy::Minimum::~Minimum (void)
{
}

int N::Fuzzy::Minimum::typeId(void) const
{
  return N::Fuzzy::IdMinimum ;
}

QString N::Fuzzy::Minimum::className (void) const
{
  return "N::Fuzzy::Minimum" ;
}

double N::Fuzzy::Minimum::compute(double a,double b) const
{
  return Operation :: Min ( a , b ) ;
}
