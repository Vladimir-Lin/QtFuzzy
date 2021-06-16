#include <qtfuzzy.h>

N::Fuzzy::Seldom:: Seldom (void)
                 : Hedge  (    )
{
}

N::Fuzzy::Seldom::~Seldom (void)
{
}

QString N::Fuzzy::Seldom::talk(void) const
{
  return QObject::tr("Seldom") ;
}

QString N::Fuzzy::Seldom::name(void) const
{
  return "N::Fuzzy::Seldom" ;
}

double N::Fuzzy::Seldom::hedge(double x) const
{
  return Operation :: isLE ( x , 0.5) ?
         ::sqrt     (      x  / 2 )   :
         1 - ::sqrt ( (1 - x) / 2 )   ;
}
