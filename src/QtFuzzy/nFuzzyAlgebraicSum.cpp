#include <qtfuzzy.h>

N::Fuzzy::AlgebraicSum:: AlgebraicSum (void)
                       : SNorm        (    )
{
}

N::Fuzzy::AlgebraicSum::~AlgebraicSum (void)
{
}

int N::Fuzzy::AlgebraicSum::typeId(void) const
{
  return N::Fuzzy::IdAlgebraicSum ;
}

QString N::Fuzzy::AlgebraicSum::className (void) const
{
  return "N::Fuzzy::AlgebraicSum" ;
}

double N::Fuzzy::AlgebraicSum::compute(double a,double b) const
{
  return ( a + b ) - (a * b) ;
}
