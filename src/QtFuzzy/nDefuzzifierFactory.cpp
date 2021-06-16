#include <qtfuzzy.h>

N::Fuzzy::DefuzzifierFactory:: DefuzzifierFactory(void)
{
}

N::Fuzzy::DefuzzifierFactory::~DefuzzifierFactory(void)
{
}

N::Fuzzy::Defuzzifier * N::Fuzzy::DefuzzifierFactory::create(const QString & zName,int divisions)
{
  #define NDEF(CN) if (zName==CN().className()) return new CN (divisions)
  NDEF ( Centroid          ) ;
  NDEF ( SmallestOfMaximum ) ;
  NDEF ( LargestOfMaximum  ) ;
  NDEF ( MeanOfMaximum     ) ;
  #undef NDEF
  return NULL                ;
}

QVector<QString> N::Fuzzy::DefuzzifierFactory::available(void) const
{
  QVector<QString> result                           ;
  #define NFCX(CN) result.push_back(CN().className())
  NFCX ( Centroid          )                        ;
  NFCX ( SmallestOfMaximum )                        ;
  NFCX ( LargestOfMaximum  )                        ;
  NFCX ( MeanOfMaximum     )                        ;
  #undef  NFC
  return result                                     ;
}
