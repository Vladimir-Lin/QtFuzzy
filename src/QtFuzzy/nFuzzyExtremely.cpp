#include <qtfuzzy.h>

N::Fuzzy::Extremely:: Extremely (void)
                    : Hedge     (    )
{
}

N::Fuzzy::Extremely::~Extremely (void)
{
}

QString N::Fuzzy::Extremely::talk(void) const
{
  return QObject::tr("Extremely") ;
}

QString N::Fuzzy::Extremely::name(void) const
{
  return "N::Fuzzy::Extremely" ;
}

double N::Fuzzy::Extremely::hedge(double x) const
{
  double x1 = 1 - x                                  ;
  double x0 = x                                      ;
  x0 *= x0                                           ;
  x0 += x0                                           ;
  x1 *= x1                                           ;
  x1 += x1                                           ;
  return Operation :: isLE ( x , 0.5 ) ? x0 : 1 - x1 ;
}
