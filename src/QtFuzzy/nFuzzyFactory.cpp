#include <qtfuzzy.h>

N::Fuzzy::Factory * N::Fuzzy::Factory::_instance = NULL ;

N::Fuzzy::Factory * N::Fuzzy::Factory::instance(void)
{
  if (IsNull(_instance))                                    {
    _instance  = new Factory    (                         ) ;
    _instance -> setTnorm       (new TNormFactory       ()) ;
    _instance -> setSnorm       (new SNormFactory       ()) ;
    _instance -> setDefuzzifier (new DefuzzifierFactory ()) ;
    _instance -> setTerm        (new TermFactory        ()) ;
    _instance -> setHedge       (new HedgeFactory       ()) ;
  }                                                         ;
  return _instance                                          ;
}

N::Fuzzy::Factory:: Factory      (void)
                  : _tnorm       (NULL)
                  , _snorm       (NULL)
                  , _defuzzifier (NULL)
                  , _term        (NULL)
                  , _hedge       (NULL)
{
}

N::Fuzzy::Factory::~Factory(void)
{
  if (NotNull(_term       )) delete _term        ;
  if (NotNull(_defuzzifier)) delete _defuzzifier ;
  if (NotNull(_snorm      )) delete _snorm       ;
  if (NotNull(_tnorm      )) delete _tnorm       ;
}

void N::Fuzzy::Factory::setTnorm(TNormFactory * tnorm)
{
  if (NotNull(_tnorm)) delete _tnorm ;
  _tnorm = tnorm                     ;
}

N::Fuzzy::TNormFactory * N::Fuzzy::Factory::tnorm(void) const
{
  return _tnorm ;
}

void N::Fuzzy::Factory::setSnorm(SNormFactory * snorm)
{
  if (NotNull(_snorm)) delete _snorm ;
  _snorm = snorm                     ;
}

N::Fuzzy::SNormFactory * N::Fuzzy::Factory::snorm(void) const
{
  return _snorm ;
}

void N::Fuzzy::Factory::setDefuzzifier(DefuzzifierFactory * defuzzifier)
{
  if (NotNull(_defuzzifier)) delete _defuzzifier ;
  _defuzzifier = defuzzifier                     ;
}

N::Fuzzy::DefuzzifierFactory * N::Fuzzy::Factory::defuzzifier(void) const
{
  return _defuzzifier ;
}

void N::Fuzzy::Factory::setTerm(TermFactory * term)
{
  if (NotNull(_term)) delete _term ;
  _term = term                     ;
}

N::Fuzzy::TermFactory * N::Fuzzy::Factory::term(void) const
{
  return _term ;
}

void N::Fuzzy::Factory::setHedge(HedgeFactory * h)
{
  if (NotNull(_hedge)) delete _hedge ;
  _hedge = h                         ;
}

N::Fuzzy::HedgeFactory * N::Fuzzy::Factory::hedge(void) const
{
  return _hedge ;
}
