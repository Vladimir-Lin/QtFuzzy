#include <qtfuzzy.h>

N::Fuzzy::NormalizedSum:: NormalizedSum (void)
                        : SNorm         (    )
{
}

N::Fuzzy::NormalizedSum::~NormalizedSum (void)
{
}

int N::Fuzzy::NormalizedSum::typeId(void) const
{
  return N::Fuzzy::IdNormalizedSum ;
}

QString N::Fuzzy::NormalizedSum::className (void) const
{
  return "N::Fuzzy::NormalizedSum" ;
}

double N::Fuzzy::NormalizedSum::compute(double a,double b) const
{
  return a + b / Operation :: Max ( 1 , Operation :: Max ( a , b ) ) ;
}
