#include <qtfuzzy.h>

N::Fuzzy::InputVariable:: InputVariable                                     (
                            const QString & name                            ,
                            double          minimum                         ,
                            double          maximum                         )
                        : Variable (name , minimum , maximum                )
                        , _input   (std::numeric_limits<double>::quiet_NaN())
{
}

N::Fuzzy::InputVariable::~InputVariable(void)
{
}

void N::Fuzzy::InputVariable::setInput(double input)
{
  _input = input ;
}

double N::Fuzzy::InputVariable::getInput(void) const
{
  return _input ;
}
