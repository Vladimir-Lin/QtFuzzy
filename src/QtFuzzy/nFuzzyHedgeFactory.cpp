#include <qtfuzzy.h>

N::Fuzzy::HedgeFactory:: HedgeFactory(void)
{
}

N::Fuzzy::HedgeFactory::~HedgeFactory(void)
{
}

N::Fuzzy::Hedge * N::Fuzzy::HedgeFactory::create(const QString & zName) const
{
  if (zName == Any       () . name()) return new Any       () ;
  if (zName == Extremely () . name()) return new Extremely () ;
  if (zName == Not       () . name()) return new Not       () ;
  if (zName == Seldom    () . name()) return new Seldom    () ;
  if (zName == Somewhat  () . name()) return new Somewhat  () ;
  if (zName == Very      () . name()) return new Very      () ;
  return NULL                                                 ;
}

QVector<QString> N::Fuzzy::HedgeFactory::available(void) const
{
  QVector<QString> result                 ;
  result.push_back(Any       () . name()) ;
  result.push_back(Extremely () . name()) ;
  result.push_back(Not       () . name()) ;
  result.push_back(Seldom    () . name()) ;
  result.push_back(Somewhat  () . name()) ;
  result.push_back(Very      () . name()) ;
  return result                           ;
}
