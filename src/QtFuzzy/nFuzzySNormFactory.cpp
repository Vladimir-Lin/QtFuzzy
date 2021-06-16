#include <qtfuzzy.h>

N::Fuzzy::SNormFactory:: SNormFactory(void)
{
}

N::Fuzzy::SNormFactory::~SNormFactory(void)
{
}

N::Fuzzy::SNorm * N::Fuzzy::SNormFactory::create(const QString & zName) const
{
  #define FSNF(CN) if (zName==CN().className()) return new CN()
  FSNF ( Maximum       ) ;
  FSNF ( AlgebraicSum  ) ;
  FSNF ( BoundedSum    ) ;
  FSNF ( NormalizedSum ) ;
  FSNF ( DrasticSum    ) ;
  FSNF ( EinsteinSum   ) ;
  FSNF ( HamacherSum   ) ;
  #undef  FSNF
  return NULL            ;
}

QVector<QString> N::Fuzzy::SNormFactory::available(void) const
{
  QVector<QString> result                           ;
  #define FSNX(CN) result.push_back(CN().className())
  FSNX ( Maximum       )                            ;
  FSNX ( AlgebraicSum  )                            ;
  FSNX ( BoundedSum    )                            ;
  FSNX ( NormalizedSum )                            ;
  FSNX ( DrasticSum    )                            ;
  FSNX ( EinsteinSum   )                            ;
  FSNX ( HamacherSum   )                            ;
  #undef  FSNX
  return result                                     ;
}
