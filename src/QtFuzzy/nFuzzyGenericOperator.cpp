#include <qtfuzzy.h>

N::Fuzzy::GenericOperator:: GenericOperator                (
                            const QString & _name          ,
                            short           _precedence    ,
                            short           _arity         ,
                            short           _associativity )
                          : name          ( _name          )
                          , precedence    ( _precedence    )
                          , arity         ( _arity         )
                          , associativity ( _associativity )
{
}

N::Fuzzy::GenericOperator::~GenericOperator(void)
{
}

QString N::Fuzzy::GenericOperator::toString(void) const
{
  std::stringstream ss                                  ;
  ss << "name='"          << name.toStdString() << "' "
     << "precedence='"    << precedence         << "' "
     << "arity='"         << arity              << "' "
     << "associativity='" << associativity      << "' " ;
  return QString::fromStdString(ss.str())               ;
}
