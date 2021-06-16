#include <qtfuzzy.h>

N::Fuzzy::Somewhat:: Somewhat (void)
                   : Hedge    (    )
{
}

N::Fuzzy::Somewhat::~Somewhat (void)
{
}

QString N::Fuzzy::Somewhat::talk(void) const
{
  return QObject::tr("Somewhat") ;
}

QString N::Fuzzy::Somewhat::name(void) const
{
  return "N::Fuzzy::Somewhat" ;
}

double N::Fuzzy::Somewhat::hedge(double x) const
{
  return ::sqrt ( x ) ;
}
