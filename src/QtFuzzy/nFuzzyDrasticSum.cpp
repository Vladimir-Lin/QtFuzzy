#include <qtfuzzy.h>

N::Fuzzy::DrasticSum:: DrasticSum (void)
                     : SNorm      (    )
{
}

N::Fuzzy::DrasticSum::~DrasticSum (void)
{
}

int N::Fuzzy::DrasticSum::typeId(void) const
{
  return N::Fuzzy::IdDrasticSum ;
}

QString N::Fuzzy::DrasticSum::className (void) const
{
  return "N::Fuzzy::DrasticSum" ;
}

double N::Fuzzy::DrasticSum::compute(double a,double b) const
{
  if ( Operation :: isEq ( Operation :: Min ( a , b ) , 0.0 ) ) {
    return Operation :: Max ( a , b )                           ;
  }                                                             ;
  return 1.0                                                    ;
}
