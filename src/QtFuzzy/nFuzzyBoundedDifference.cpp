#include <qtfuzzy.h>

N::Fuzzy::BoundedDifference:: BoundedDifference (void)
                            : TNorm             (    )
{
}

N::Fuzzy::BoundedDifference::~BoundedDifference (void)
{
}

int N::Fuzzy::BoundedDifference::typeId(void) const
{
  return N::Fuzzy::IdBoundedDifference ;
}

QString N::Fuzzy::BoundedDifference::className (void) const
{
  return "N::Fuzzy::BoundedDifference" ;
}

double N::Fuzzy::BoundedDifference::compute(double a,double b) const
{
  return Operation :: Max ( 0 , a + b - 1 ) ;
}
