#include <qtfuzzy.h>

N::Fuzzy::MamdaniProposition:: MamdaniProposition (void )
                             : MamdaniExpression  (false)
                             , variable           (NULL )
                             , term               (NULL )
{
}

N::Fuzzy::MamdaniProposition::~MamdaniProposition(void)
{
}

QString N::Fuzzy::MamdaniProposition::toString(void) const
{
  QStringList L                   ;
  L << variable->getName()        ;
  L << Rule::FuzzyIS              ;
  nFullLoop ( i , hedges.size() ) {
    L << hedges.at(i)->name()     ;
  }                               ;
  L << term->Name                 ;
  return L . join ( " " )         ;
}
