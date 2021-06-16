#include <qtfuzzy.h>

N::Fuzzy::AlgebraicProduct:: AlgebraicProduct (void)
                           : TNorm            (    )
{
}

N::Fuzzy::AlgebraicProduct::~AlgebraicProduct (void)
{
}

int N::Fuzzy::AlgebraicProduct::typeId(void) const
{
  return N::Fuzzy::IdAlgebraicProduct ;
}

QString N::Fuzzy::AlgebraicProduct::className (void) const
{
  return "N::Fuzzy::AlgebraicProduct" ;
}

double N::Fuzzy::AlgebraicProduct::compute(double a,double b) const
{
  return ( a * b ) ;
}
