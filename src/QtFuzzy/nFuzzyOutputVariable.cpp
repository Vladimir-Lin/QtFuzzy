#include <qtfuzzy.h>

N::Fuzzy::OutputVariable:: OutputVariable                                                    (
                             const QString &      name                                       ,
                             double               minimum                                    ,
                             double               maximum                                    )
                         : Variable              (name,minimum,maximum                       )
                         , _output               (new Accumulated("output", minimum, maximum))
                         , _defuzzifier          (NULL                                       )
                         , _defaultValue         (std::numeric_limits<double>::quiet_NaN()   )
                         , _defuzzifiedValue     (std::numeric_limits<double>::quiet_NaN()   )
                         , _lockDefuzzifiedValue (true                                       )
{
}

N::Fuzzy::OutputVariable::~OutputVariable(void)
{
  delete _output ;
}

N::Fuzzy::Accumulated * N::Fuzzy::OutputVariable::output(void) const
{
  return _output ;
}

void N::Fuzzy::OutputVariable::setMinimum(double minimum)
{
  Variable :: setMinimum ( minimum ) ;
  _output  -> setMinimum ( minimum ) ;
}

void N::Fuzzy::OutputVariable::setMaximum(double maximum)
{
  Variable :: setMaximum ( maximum ) ;
  _output  -> setMaximum ( maximum ) ;
}

void N::Fuzzy::OutputVariable::setDefuzzifier(Defuzzifier * defuzzifier)
{
  if (NotNull(_defuzzifier)) delete _defuzzifier ;
  _defuzzifier = defuzzifier                     ;
}

N::Fuzzy::Defuzzifier * N::Fuzzy::OutputVariable::getDefuzzifier(void) const
{
  return _defuzzifier ;
}

void N::Fuzzy::OutputVariable::setDefaultValue(double defaultValue)
{
  _defaultValue = defaultValue ;
}

double N::Fuzzy::OutputVariable::getDefaultValue(void) const
{
  return _defaultValue ;
}

void N::Fuzzy::OutputVariable::setDefuzzifiedValue(double defuzzifiedValue)
{
  _defuzzifiedValue = defuzzifiedValue ;
}

double N::Fuzzy::OutputVariable::getDefuzzifiedValue(void) const
{
  return _defuzzifiedValue ;
}

void N::Fuzzy::OutputVariable::setLockDefuzzifiedValue(bool lock)
{
  _lockDefuzzifiedValue = lock ;
}

bool N::Fuzzy::OutputVariable::lockDefuzzifiedValue(void) const
{
  return _lockDefuzzifiedValue ;
}

double N::Fuzzy::OutputVariable::defuzzify(void)
{
  double result = defuzzifyIgnoreLock()                 ;
  if (_lockDefuzzifiedValue) _defuzzifiedValue = result ;
  return result                                         ;
}

double N::Fuzzy::OutputVariable::defuzzifyIgnoreLock(void) const
{
  if (this->_output->isEmpty())                                               {
    if (_lockDefuzzifiedValue && ! Operation :: isNan ( _defuzzifiedValue ) ) {
      return _defuzzifiedValue                                                ;
    }                                                                         ;
    return _defaultValue                                                      ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  double result = _defuzzifier->defuzzify(_output,_minimum,_maximum)          ;
  if ( Operation :: isLt ( result , _minimum ) ) result = _minimum            ;
  if ( Operation :: isGt ( result , _maximum ) ) result = _maximum            ;
  return result                                                               ;
}
