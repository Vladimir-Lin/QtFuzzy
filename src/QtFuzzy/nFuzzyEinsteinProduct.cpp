#include <qtfuzzy.h>

N::Fuzzy::EinsteinProduct:: EinsteinProduct (void)
                          : TNorm           (    )
{
}

N::Fuzzy::EinsteinProduct::~EinsteinProduct (void)
{
}

int N::Fuzzy::EinsteinProduct::typeId(void) const
{
  return N::Fuzzy::IdEinsteinProduct ;
}

QString N::Fuzzy::EinsteinProduct::className (void) const
{
  return "N::Fuzzy::EinsteinProduct" ;
}

double N::Fuzzy::EinsteinProduct::compute(double a,double b) const
{
  double ab = ( a * b              ) ;
  return ab / ( 2 - ( a + b - ab ) ) ;
}
