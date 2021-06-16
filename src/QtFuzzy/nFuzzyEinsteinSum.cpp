#include <qtfuzzy.h>

N::Fuzzy::EinsteinSum:: EinsteinSum (void)
                      : SNorm       (    )
{
}

N::Fuzzy::EinsteinSum::~EinsteinSum (void)
{
}

int N::Fuzzy::EinsteinSum::typeId(void) const
{
  return N::Fuzzy::IdEinsteinSum ;
}

QString N::Fuzzy::EinsteinSum::className (void) const
{
  return "N::Fuzzy::EinsteinSum" ;
}

double N::Fuzzy::EinsteinSum::compute(double a,double b) const
{
  return ( a + b ) / ( 1 + ( a * b ) ) ;
}
