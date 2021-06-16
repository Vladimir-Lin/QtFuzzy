#include <qtfuzzy.h>

N::Fuzzy::Very:: Very  (void)
               : Hedge (    )
{
}

N::Fuzzy::Very::~Very (void)
{
}

QString N::Fuzzy::Very::talk(void) const
{
  return QObject::tr("Very") ;
}

QString N::Fuzzy::Very::name(void) const
{
  return "N::Fuzzy::Very" ;
}

double N::Fuzzy::Very::hedge(double x) const
{
  return nSquare ( x ) ;
}
