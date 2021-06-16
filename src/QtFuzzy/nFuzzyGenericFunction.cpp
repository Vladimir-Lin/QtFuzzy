#include <qtfuzzy.h>

N::Fuzzy::GenericFunction:: GenericFunction         (
                            const QString &  _name  ,
                            short            _arity )
                          : name           ( _name  )
                          , arity          ( _arity )
                          , associativity  ( -1     )
                          , oneArgFunction ( NULL   )
                          , twoArgFunction ( NULL   )
{
}

N::Fuzzy::GenericFunction:: GenericFunction                  (
                            const QString &  _name           ,
                            OneArgFunction   _oneArgFunction )
                          : name           ( _name           )
                          , arity          (  1              )
                          , associativity  ( -1              )
                          , oneArgFunction ( _oneArgFunction )
                          , twoArgFunction ( NULL            )
{
}

N::Fuzzy::GenericFunction:: GenericFunction                  (
                            const QString &  _name           ,
                            TwoArgFunction   _twoArgFunction )
                          : name           ( _name           )
                          , arity          (  2              )
                          , associativity  ( -1              )
                          , oneArgFunction ( NULL            )
                          , twoArgFunction ( _twoArgFunction )
{
}

N::Fuzzy::GenericFunction::~GenericFunction(void)
{
}

QString N::Fuzzy::GenericFunction::toString(void) const
{
  QString R                                                ;
  R = QString ( "name='%1' arity='%2' associativity='%3' " )
      . arg   ( name                                       )
      . arg   ( arity                                      )
      . arg   ( associativity)                             ;
  return R                                                 ;
}
