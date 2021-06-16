#include <qtfuzzy.h>

N::Fuzzy::Engine:: Engine       ( const QString & name )
                 : Object       ( 0 , None             )
                 , _name        ( name                 )
                 , _error       ( false                )
                 , _errorString ( ""                   )
{
}

N::Fuzzy::Engine::~Engine (void)
{
  for (int i = numberOfRuleBlocks     () - 1; i >= 0; --i) {
    delete removeRuleBlock      (i)                        ;
  }                                                        ;
  for (int i = numberOfHedges() - 1; i >= 0; --i)          {
    delete removeHedge          (i)                        ;
  }                                                        ;
  for (int i = numberOfOutputVariables() - 1; i >= 0; --i) {
    delete removeOutputVariable (i)                        ;
  }                                                        ;
  for (int i = numberOfInputVariables () - 1; i >= 0; --i) {
    delete removeInputVariable  (i)                        ;
  }                                                        ;
}

bool N::Fuzzy::Engine::isError(void)
{
  return _error ;
}

void N::Fuzzy::Engine::setError(QString errString,bool err)
{
  _error       = err       ;
  _errorString = errString ;
}

QString N::Fuzzy::Engine::ErrorString(void)
{
  return _errorString ;
}

N::Fuzzy::TNorm * N::Fuzzy::Engine::createTnorm(const QString & classname) const
{
  return Factory::instance()->tnorm()->create(classname) ;
}

N::Fuzzy::SNorm * N::Fuzzy::Engine::createSnorm(const QString & classname) const
{
  return Factory::instance()->snorm()->create(classname) ;
}

N::Fuzzy::Defuzzifier * N::Fuzzy::Engine::createDefuzzifier(const QString & classname) const
{
  return Factory::instance()->defuzzifier()->create(classname) ;
}

void N::Fuzzy::Engine::configure                    (
        const QString & tnorm             ,
        const QString & snorm             ,
        const QString & activationTnorm   ,
        const QString & accumulationSnorm ,
        const QString & defuzzifier       ,
        int             divisions         )
{
  nFullLoop ( i , _ruleblocks      . size() )                               {
    RuleBlock * frb = _ruleblocks.at(i)                                     ;
    frb -> setTnorm     (createTnorm(tnorm          ))                      ;
    frb -> setSnorm     (createSnorm(snorm          ))                      ;
    frb -> setActivation(createTnorm(activationTnorm))                      ;
  }                                                                         ;
  ///////////////////////////////////////////////////////////////////////////
  nFullLoop ( i , _outputVariables . size() )                               {
    OutputVariable * fov = _outputVariables.at(i)                           ;
    fov                  ->setDefuzzifier  (createDefuzzifier(defuzzifier)) ;
    fov->getDefuzzifier()->Divisions = divisions                            ;
    fov->output        ()->setAccumulation (createSnorm(accumulationSnorm)) ;
  }                                                                         ;
}

void N::Fuzzy::Engine::process(void)
{
  nFullLoop ( i , _outputVariables . size () )           {
    _outputVariables . at(i) -> output    () -> clear () ;
  }                                                      ;
  ////////////////////////////////////////////////////////
  nFullLoop ( i , _ruleblocks      . size () )           {
    _ruleblocks      . at(i) -> fireRules ()             ;
  }                                                      ;
}

void N::Fuzzy::Engine::processVariables(void)
{
  nFullLoop ( i , numberOfInputVariables  () ) {
    InputVariable  * fiv                       ;
    fiv = getInputVariable  ( i )              ;
    QString name = fiv->getName()              ;
    if (ioVariables.contains(name))            {
      fiv->setInput(ioVariables[name])         ;
    }                                          ;
  }                                            ;
  //////////////////////////////////////////////
  process()                                    ;
  //////////////////////////////////////////////
  nFullLoop ( i , numberOfOutputVariables () ) {
    OutputVariable * fov                       ;
    fov = getOutputVariable ( i )              ;
    double v = fov->defuzzify()                ;
    QString name = fov->getName()              ;
    ioVariables[name] = v                      ;
  }                                            ;
}

void N::Fuzzy::Engine::setName(const QString & name)
{
  _name = name ;
}

QString N::Fuzzy::Engine::getName(void) const
{
  return _name ;
}

void N::Fuzzy::Engine::addInputVariable(InputVariable* inputVariable)
{
  _inputVariables.push_back(inputVariable) ;
}

void N::Fuzzy::Engine::insertInputVariable(InputVariable* inputVariable, int index)
{
  _inputVariables.insert(_inputVariables.begin() + index,inputVariable) ;
}

N::Fuzzy::InputVariable * N::Fuzzy::Engine::getInputVariable(int index) const
{
  return _inputVariables.at(index) ;
}

N::Fuzzy::InputVariable * N::Fuzzy::Engine::getInputVariable(const QString & name) const
{
  nFullLoop ( i , _inputVariables.size() )        {
    if (_inputVariables.at(i)->getName() == name) {
      return _inputVariables.at(i)                ;
    }                                             ;
  }                                               ;
  return NULL                                     ;
}

bool N::Fuzzy::Engine::hasInputVariable(const QString & name) const
{
  nFullLoop ( i , _inputVariables.size() )                    {
    if (_inputVariables.at(i)->getName() == name) return true ;
  }                                                           ;
  return false                                                ;
}

N::Fuzzy::InputVariable * N::Fuzzy::Engine::removeInputVariable(int index)
{
  InputVariable * result = _inputVariables.at(index)     ;
  _inputVariables.erase(_inputVariables.begin() + index) ;
  return result                                          ;
}

N::Fuzzy::InputVariable * N::Fuzzy::Engine::removeInputVariable(const QString & name)
{
  nFullLoop ( i , _inputVariables.size() )               {
    if (_inputVariables.at(i)->getName() == name)        {
      InputVariable * result = _inputVariables.at(i)     ;
      _inputVariables.erase(_inputVariables.begin() + i) ;
      return result                                      ;
    }                                                    ;
  }                                                      ;
  return NULL                                            ;
}

int N::Fuzzy::Engine::numberOfInputVariables(void) const
{
  return _inputVariables.size() ;
}

const QVector<N::Fuzzy::InputVariable *> & N::Fuzzy::Engine::inputVariables(void) const
{
  return _inputVariables ;
}

void N::Fuzzy::Engine::addOutputVariable(N::Fuzzy::OutputVariable * outputVariable)
{
  _outputVariables.push_back(outputVariable) ;
}

void N::Fuzzy::Engine::insertOutputVariable(N::Fuzzy::OutputVariable * outputVariable,int index)
{
  _outputVariables.insert(_outputVariables.begin() + index, outputVariable) ;
}

N::Fuzzy::OutputVariable * N::Fuzzy::Engine::getOutputVariable(int index) const
{
  return _outputVariables.at(index) ;
}

N::Fuzzy::OutputVariable * N::Fuzzy::Engine::getOutputVariable(const QString & name) const
{
  nFullLoop ( i , _outputVariables.size() )        {
    if (_outputVariables.at(i)->getName() == name) {
      return _outputVariables.at(i)                ;
    }                                              ;
  }                                                ;
  return NULL                                      ;
}

bool N::Fuzzy::Engine::hasOutputVariable(const QString & name) const
{
  nFullLoop ( i , _outputVariables.size() )                    {
    if (_outputVariables.at(i)->getName() == name) return true ;
  }                                                            ;
  return false                                                 ;
}

N::Fuzzy::OutputVariable * N::Fuzzy::Engine::removeOutputVariable(int index)
{
  OutputVariable * result = _outputVariables.at(index)     ;
  _outputVariables.erase(_outputVariables.begin() + index) ;
  return result                                            ;
}

N::Fuzzy::OutputVariable * N::Fuzzy::Engine::removeOutputVariable(const QString & name)
{
  nFullLoop ( i , _outputVariables.size() )                {
    if (_outputVariables.at(i)->getName() == name)         {
      OutputVariable * result = _outputVariables.at(i)     ;
      _outputVariables.erase(_outputVariables.begin() + i) ;
      return result                                        ;
    }                                                      ;
  }                                                        ;
  return NULL                                              ;
}

int N::Fuzzy::Engine::numberOfOutputVariables(void) const
{
  return _outputVariables.size() ;
}

const QVector<N::Fuzzy::OutputVariable *> & N::Fuzzy::Engine::outputVariables(void) const
{
  return _outputVariables ;
}

void N::Fuzzy::Engine::addRuleBlock(RuleBlock * ruleblock)
{
  _ruleblocks.push_back(ruleblock) ;
}

void N::Fuzzy::Engine::insertRuleBlock(RuleBlock * ruleblock,int index)
{
  _ruleblocks.insert(_ruleblocks.begin() + index, ruleblock) ;
}

N::Fuzzy::RuleBlock * N::Fuzzy::Engine::getRuleBlock(int index) const
{
  return _ruleblocks.at(index) ;
}

N::Fuzzy::RuleBlock * N::Fuzzy::Engine::getRuleBlock(const QString & name) const
{
  nFullLoop ( i , _ruleblocks.size() )        {
    if (_ruleblocks.at(i)->getName() == name) {
      return _ruleblocks.at(i)                ;
    }                                         ;
  }                                           ;
  return NULL                                 ;
}

bool N::Fuzzy::Engine::hasRuleBlock(const QString & name) const
{
  nFullLoop ( i , _ruleblocks.size() )                    {
    if (_ruleblocks.at(i)->getName() == name) return true ;
  }                                                       ;
  return false                                            ;
}

N::Fuzzy::RuleBlock * N::Fuzzy::Engine::removeRuleBlock(int index)
{
  RuleBlock * result = _ruleblocks.at(index)     ;
  _ruleblocks.erase(_ruleblocks.begin() + index) ;
  return result                                  ;
}

N::Fuzzy::RuleBlock * N::Fuzzy::Engine::removeRuleBlock(const QString & name)
{
  nFullLoop ( i , _ruleblocks.size() )             {
    if (_ruleblocks.at(i)->getName() == name)      {
      RuleBlock * result = _ruleblocks.at(i)       ;
      _ruleblocks.erase(_ruleblocks.begin() + i)   ;
      return result                                ;
    }                                              ;
  }                                                ;
  return NULL                                      ;
}

int N::Fuzzy::Engine::numberOfRuleBlocks(void) const
{
  return _ruleblocks.size() ;
}

const QVector<N::Fuzzy::RuleBlock *> & N::Fuzzy::Engine::ruleBlocks(void) const
{
  return _ruleblocks ;
}

N::Fuzzy::Hedge * N::Fuzzy::Engine::chosen(double x)
{
  Hedge * f  = NULL                  ;
  double        hs = 0               ;
  nFullLoop ( n , numberOfHedges() ) {
    Hedge * h = getHedge(n)          ;
    double hv = h->hedge(x)          ;
    if (hv>hs)                       {
      f  = h                         ;
      hs = hv                        ;
    }                                ;
  }                                  ;
  return f ;
}

void N::Fuzzy::Engine::addHedge(Hedge * hedge)
{
  _hedges.push_back(hedge) ;
}

void N::Fuzzy::Engine::insertHedge(Hedge * hedge,int index)
{
  _hedges.insert(_hedges.begin() + index, hedge) ;
}

N::Fuzzy::Hedge * N::Fuzzy::Engine::getHedge(int index) const
{
  return _hedges.at(index) ;
}

N::Fuzzy::Hedge * N::Fuzzy::Engine::getHedge(const QString & name) const
{
  nFullLoop ( i , _hedges.size() )     {
    if (name == _hedges.at(i)->name()) {
      return _hedges.at(i)             ;
    }                                  ;
  }                                    ;
  return NULL                          ;
}

bool N::Fuzzy::Engine::hasHedge(const QString & name) const
{
  nFullLoop ( i , _hedges.size() )      {
     if (name == _hedges.at(i)->name()) {
       return true                      ;
     }                                  ;
  }                                     ;
  return false                          ;
}

N::Fuzzy::Hedge * N::Fuzzy::Engine::removeHedge(int index)
{
  Hedge * result = _hedges.at(index)     ;
  _hedges.erase(_hedges.begin() + index) ;
  return result                          ;
}

N::Fuzzy::Hedge * N::Fuzzy::Engine::removeHedge(const QString & name)
{
  nFullLoop ( i , _hedges.size() )           {
    if (name == this->_hedges.at(i)->name()) {
      Hedge * result = _hedges.at(i)         ;
      _hedges.erase(_hedges.begin() + i)     ;
      return result                          ;
    }                                        ;
  }                                          ;
  return NULL                                ;
}

int N::Fuzzy::Engine::numberOfHedges(void) const
{
  return _hedges.size();
}

const QVector<N::Fuzzy::Hedge *> & N::Fuzzy::Engine::hedges(void) const
{
  return _hedges ;
}
