#include <qtfuzzy.h>

N::Fuzzy::DrasticProduct:: DrasticProduct (void)
                         : TNorm          (    )
{
}

N::Fuzzy::DrasticProduct::~DrasticProduct (void)
{
}

int N::Fuzzy::DrasticProduct::typeId(void) const
{
  return N::Fuzzy::IdDrasticProduct ;
}

QString N::Fuzzy::DrasticProduct::className (void) const
{
  return "N::Fuzzy::DrasticProduct" ;
}

double N::Fuzzy::DrasticProduct::compute(double a,double b) const
{
  if ( Operation :: isEq ( Operation :: Max ( a , b ) , 1.0 ) ) {
    return Operation :: Min ( a , b )                           ;
  }                                                             ;
  return 0.0                                                    ;
}
