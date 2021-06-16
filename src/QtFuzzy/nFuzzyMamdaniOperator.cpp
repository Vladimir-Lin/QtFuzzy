#include <qtfuzzy.h>

N::Fuzzy::MamdaniOperator:: MamdaniOperator   (void)
                          : MamdaniExpression (true)
                          , left              (NULL)
                          , right             (NULL)
{
}

N::Fuzzy::MamdaniOperator::~MamdaniOperator(void)
{
  if (NotNull(left )) delete left  ;
  if (NotNull(right)) delete right ;
  left  = NULL                     ;
  right = NULL                     ;
}

QString N::Fuzzy::MamdaniOperator::toString(void) const
{
  return name ;
}
