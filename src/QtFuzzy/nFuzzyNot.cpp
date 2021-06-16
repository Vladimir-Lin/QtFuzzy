#include <qtfuzzy.h>

N::Fuzzy::Not:: Not   (void)
              : Hedge (    )
{
}

N::Fuzzy::Not::~Not (void)
{
}

QString N::Fuzzy::Not::talk(void) const
{
  return QObject::tr("Not") ;
}

QString N::Fuzzy::Not::name(void) const
{
  return "N::Fuzzy::Not" ;
}

double N::Fuzzy::Not::hedge(double x) const
{
  return ( 1 - x ) ;
}
