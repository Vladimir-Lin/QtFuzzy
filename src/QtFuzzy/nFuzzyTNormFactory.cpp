#include <qtfuzzy.h>

N::Fuzzy::TNormFactory:: TNormFactory(void)
{
}

N::Fuzzy::TNormFactory::~TNormFactory(void)
{
}

N::Fuzzy::TNorm * N::Fuzzy::TNormFactory::create(const QString & zName) const
{
  #define NFMX(CN) if (zName==CN().className()) return new CN()
  NFMX ( Minimum           ) ;
  NFMX ( AlgebraicProduct  ) ;
  NFMX ( BoundedDifference ) ;
  NFMX ( DrasticProduct    ) ;
  NFMX ( EinsteinProduct   ) ;
  NFMX ( HamacherProduct   ) ;
  #undef  NFMX
  return NULL                ;
}

QVector<QString> N::Fuzzy::TNormFactory::available(void) const
{
  QVector<QString> result                           ;
  #define NFZX(CN) result.push_back(CN().className())
  NFZX ( Minimum           )                        ;
  NFZX ( AlgebraicProduct  )                        ;
  NFZX ( BoundedDifference )                        ;
  NFZX ( DrasticProduct    )                        ;
  NFZX ( EinsteinProduct   )                        ;
  NFZX ( HamacherProduct   )                        ;
  #undef  NFZX
  return result                                     ;
}
