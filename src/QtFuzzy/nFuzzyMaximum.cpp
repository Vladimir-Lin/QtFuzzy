#include <qtfuzzy.h>

N::Fuzzy::Maximum:: Maximum (void)
                  : SNorm   (    )
{
}

N::Fuzzy::Maximum::~Maximum (void)
{
}

int N::Fuzzy::Maximum::typeId(void) const
{
  return N::Fuzzy::IdMaximum ;
}

QString N::Fuzzy::Maximum::className (void) const
{
  return "N::Fuzzy::Maximum" ;
}

double N::Fuzzy::Maximum::compute(double a,double b) const
{
  return Operation :: Max ( a , b ) ;
}
