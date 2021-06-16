#include <qtfuzzy.h>

N::Fuzzy::Any:: Any   (void)
              : Hedge (    )
{
}

N::Fuzzy::Any::~Any (void)
{
}

QString N::Fuzzy::Any::talk(void) const
{
  return QObject::tr("Any") ;
}

QString N::Fuzzy::Any::name(void) const
{
  return "N::Fuzzy::Any" ;
}

double N::Fuzzy::Any::hedge(double) const
{
  return 1.0 ;
}
