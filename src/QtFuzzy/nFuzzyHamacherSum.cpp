#include <qtfuzzy.h>

N::Fuzzy::HamacherSum:: HamacherSum (void)
                      : SNorm       (    )
{
}

N::Fuzzy::HamacherSum::~HamacherSum (void)
{
}

int N::Fuzzy::HamacherSum::typeId(void) const
{
  return N::Fuzzy::IdHamacherSum ;
}

QString N::Fuzzy::HamacherSum::className (void) const
{
  return "N::Fuzzy::HamacherSum" ;
}

double N::Fuzzy::HamacherSum::compute(double a,double b) const
{
  double ab = ( a * b )                   ;
  return ( a + b - ab - ab ) / ( 1 - ab ) ;
}
