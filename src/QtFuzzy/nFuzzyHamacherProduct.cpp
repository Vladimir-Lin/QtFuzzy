#include <qtfuzzy.h>

N::Fuzzy::HamacherProduct:: HamacherProduct (void)
                          : TNorm           (    )
{
}

N::Fuzzy::HamacherProduct::~HamacherProduct (void)
{
}

int N::Fuzzy::HamacherProduct::typeId(void) const
{
  return N::Fuzzy::IdHamacherProduct ;
}

QString N::Fuzzy::HamacherProduct::className (void) const
{
  return "N::Fuzzy::HamacherProduct" ;
}

double N::Fuzzy::HamacherProduct::compute(double a,double b) const
{
  double ab = ( a * b      ) ;
  return ab / ( a + b - ab ) ;
}
