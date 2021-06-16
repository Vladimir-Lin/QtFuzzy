#include <qtfuzzy.h>

N::Fuzzy::BoundedSum:: BoundedSum (void)
                     : SNorm      (    )
{
}

N::Fuzzy::BoundedSum::~BoundedSum (void)
{
}

int N::Fuzzy::BoundedSum::typeId(void) const
{
  return N::Fuzzy::IdBoundedSum ;
}

QString N::Fuzzy::BoundedSum::className (void) const
{
  return "N::Fuzzy::BoundedSum" ;
}

double N::Fuzzy::BoundedSum::compute(double a,double b) const
{
  return Operation :: Min ( 1 , a + b ) ;
}
