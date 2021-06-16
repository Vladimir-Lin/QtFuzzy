#include <qtfuzzy.h>

N::Fuzzy::MamdaniAntecedent:: MamdaniAntecedent (void)
                            : _root             (NULL)
{
}

N::Fuzzy::MamdaniAntecedent::~MamdaniAntecedent (void)
{
  if (NotNull(_root)) delete _root ;
  _root = NULL ;
}

N::Fuzzy::MamdaniExpression * N::Fuzzy::MamdaniAntecedent::getRoot(void) const
{
  return _root ;
}

double N::Fuzzy::MamdaniAntecedent::firingStrength (
         const TNorm             * tnorm           ,
         const SNorm             * snorm           ,
         const MamdaniExpression * node            ) const
{
  if (!node->isOperator)                                                     {
    const MamdaniProposition * proposition                                   =
      dynamic_cast<const MamdaniProposition *> (node)                        ;
    bool isAny = false                                                       ;
    nFullLoop ( i , proposition->hedges.size() )                             {
      isAny |= ( proposition->hedges.at(i)->name() == Any().name() )         ;
      if (isAny) return 1.0                                                  ;
    }                                                                        ;
    InputVariable * inputVariable                                            =
      dynamic_cast<InputVariable *> ( proposition->variable )                ;
    double result = proposition->term->membership(inputVariable->getInput()) ;
    nFullLoop ( i , proposition->hedges.size() )                             {
      result = proposition->hedges.at(i)->hedge(result)                      ;
    }                                                                        ;
    return result                                                            ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  //if node is an operator
  const MamdaniOperator * mamdaniOperator                                    =
    dynamic_cast<const MamdaniOperator *> (node)                             ;
  if (IsNull(mamdaniOperator->left) || IsNull(mamdaniOperator->right))       {
//    ex << "[syntax error] left and right operands must exist";
    return 0                                                                 ;
  }                                                                          ;
  if (mamdaniOperator->name == Rule::FuzzyAND)                               {
    return tnorm->compute                                                    (
          firingStrength(tnorm,snorm,mamdaniOperator->left )                 ,
          firingStrength(tnorm,snorm,mamdaniOperator->right) )               ;
  }                                                                          ;
  if (mamdaniOperator->name == Rule::FuzzyOR)                                {
    return snorm->compute                                                    (
            this->firingStrength(tnorm, snorm, mamdaniOperator->left)        ,
            this->firingStrength(tnorm, snorm, mamdaniOperator->right) )     ;
  }                                                                          ;
//  ex << "[syntax error] operator <" << mamdaniOperator->name << "> not recognized";
  return 0                                                                   ;
}

double N::Fuzzy::MamdaniAntecedent::firingStrength (
         const TNorm * tnorm                       ,
         const SNorm * snorm                       ) const
{
  return firingStrength(tnorm,snorm,_root) ;
}

bool N::Fuzzy::MamdaniAntecedent::evaluate(const QString & antecedent,Engine * engine)
{
  return false ;
}

void N::Fuzzy::MamdaniAntecedent::load(const QString & antecedent,Engine * engine)
{
  /***************************************************************************
    Builds an proposition tree from the antecedent of a fuzzy rule.
    The rules are:
     1) After a variable comes 'is',
     2) After 'is' comes a hedge or a term
     3) After a hedge comes a hedge or a term
     4) After a term comes a variable or an operator
   ***************************************************************************/
  enum FSM                                                                    {
    S_VARIABLE =  1                                                           ,
    S_IS       =  2                                                           ,
    S_HEDGE    =  4                                                           ,
    S_TERM     =  8                                                           ,
    S_OPERATOR = 16
  }                                                                           ;
  Infix       infix                                                           ;
  QString     postfix = infix   . toPostfix ( antecedent )                    ;
  QStringList Token   = postfix . split     ( ' '        )                    ;
  int         state   = S_VARIABLE                                            ;
  std::stack<MamdaniExpression *> expressionStack                             ;
  MamdaniProposition * proposition = NULL                                     ;
  nFullLoop ( i , Token . count() )                                           {
    QString t = Token [ i ]                                                   ;
    QString l = t.toLower()                                                   ;
    if (l.length()<=0) continue                                               ;
    ///////////////////////////////////////////////////////////////////////////
    if (IsMask(state,S_VARIABLE))                                             {
      if (engine->hasInputVariable(t))                                        {
        proposition  = new MamdaniProposition()                               ;
        proposition -> variable = engine->getInputVariable(t)                 ;
        expressionStack.push(proposition)                                     ;
        state = S_IS                                                          ;
        continue                                                              ;
      }                                                                       ;
    }                                                                         ;
    ///////////////////////////////////////////////////////////////////////////
    if (IsMask(state,S_IS))                                                   {
      if (l == Rule::FuzzyIS)                                                 {
        state = S_HEDGE | S_TERM                                              ;
        continue                                                              ;
      }                                                                       ;
    }                                                                         ;
    ///////////////////////////////////////////////////////////////////////////
    if (IsMask(state,S_HEDGE))                                                {
      if (engine->hasHedge(t))                                                {
        Hedge * hedge = engine->getHedge(t)                                   ;
        proposition-> hedges.push_back(hedge)                                 ;
        if (t == Any().name())                                                {
          state = S_VARIABLE | S_OPERATOR                                     ;
        } else                                                                {
          state = S_HEDGE    | S_TERM                                         ;
        }                                                                     ;
        continue                                                              ;
      }                                                                       ;
    }                                                                         ;
    ///////////////////////////////////////////////////////////////////////////
    if (IsMask(state,S_TERM))                                                 {
      if (proposition->variable->hasTerm(t))                                  {
        proposition->term = proposition->variable->getTerm(t)                 ;
        state = S_VARIABLE | S_OPERATOR                                       ;
        continue                                                              ;
      }                                                                       ;
    }                                                                         ;
    ///////////////////////////////////////////////////////////////////////////
    if (IsMask(state,S_OPERATOR))                                             {
      if (infix.isOperator(t))                                                {
        if (expressionStack.size() < 2)                                       {
          QString es                                                          ;
          es = QString("[syntax error] operator < %1 > expects 2 operands, but found %2")
               .arg(t).arg(expressionStack.size())                            ;
          engine -> setError ( es )                                           ;
          return                                                              ;
        }                                                                     ;
        MamdaniOperator * mamdaniOperator = new MamdaniOperator()             ;
        mamdaniOperator->name  = t                                            ;
        mamdaniOperator->right = expressionStack.top()                        ;
        expressionStack.pop()                                                 ;
        mamdaniOperator->left  = expressionStack.top()                        ;
        expressionStack.pop()                                                 ;
        expressionStack.push(mamdaniOperator)                                 ;
        state = S_VARIABLE | S_OPERATOR                                       ;
        continue                                                              ;
      }                                                                       ;
    }                                                                         ;
    ///////////////////////////////////////////////////////////////////////////
    //If reached this point, there was an error
    if ((IsMask(state,S_VARIABLE)) || (IsMask(state,S_OPERATOR)))             {
      QString es                                                              ;
      es = QString("[syntax error] expected input variable or operator, but found < %1 >")
           .arg(t)                                                            ;
      engine->setError(es)                                                    ;
      return                                                                  ;
    }                                                                         ;
    ///////////////////////////////////////////////////////////////////////////
    if (IsMask(state,S_IS))                                                   {
      QString es                                                              ;
      es = QString("[syntax error] expected keyword < %1 >, but found < %2 >" )
           .arg(Rule::FuzzyIS                                                 )
           .arg(t)                                                            ;
      engine->setError(es)                                                    ;
    }                                                                         ;
    ///////////////////////////////////////////////////////////////////////////
    if ((IsMask(state,S_HEDGE)) || (IsMask(state,S_TERM)))                    {
      QString es                                                              ;
      es = QString("[syntax error] expected hedge or term, but found < %1 >")
           .arg(t)                                                            ;
      engine->setError(es)                                                    ;
    }                                                                         ;
    ///////////////////////////////////////////////////////////////////////////
    {
      QString es                                                              ;
      es = QString("[syntax error] unexpected token < %1 >")
           .arg(t)                                                            ;
      engine->setError(es)                                                    ;
    }                                                                         ;
  }                                                                           ;
  if (expressionStack.size() != 1)                                            {
    QString es                                                                ;
    es = QString("[syntax error] stack expected to contain the root, but contains %1 nodes")
            .arg(expressionStack.size())                                      ;
    engine->setError(es)                                                      ;
  }                                                                           ;
  _root = expressionStack.top()                                               ;
}

QString N::Fuzzy::MamdaniAntecedent::toString(void) const
{
  return toStringInfix(_root) ;
}

QString N::Fuzzy::MamdaniAntecedent::toStringPrefix(const MamdaniExpression * node) const
{
  if (IsNull(node)) node = _root                 ;
  if (!node->isOperator) return node->toString() ;
  const MamdaniOperator * mamdaniOperator        =
    dynamic_cast<const MamdaniOperator*> (node)  ;
  QString L = ""                                 ;
  L += mamdaniOperator->toString( )              ;
  L += " "                                       ;
  L += toStringPrefix(mamdaniOperator->left )    ;
  L += " "                                       ;
  L += toStringPrefix(mamdaniOperator->right)    ;
  L += " "                                       ;
  return L                                       ;
}

QString N::Fuzzy::MamdaniAntecedent::toStringInfix(const MamdaniExpression * node) const
{
  if (IsNull(node)) node = _root                 ;
  if (!node->isOperator) return node->toString() ;
  const MamdaniOperator * mamdaniOperator        =
    dynamic_cast<const MamdaniOperator*> (node)  ;
  QString L = ""                                 ;
  L += toStringInfix(mamdaniOperator->left )     ;
  L += " "                                       ;
  L += mamdaniOperator->toString( )              ;
  L += " "                                       ;
  L += toStringInfix(mamdaniOperator->right)     ;
  L += " "                                       ;
  return L                                       ;
}

QString N::Fuzzy::MamdaniAntecedent::toStringPostfix(const MamdaniExpression * node) const
{
  if (IsNull(node)) node = _root                 ;
  if (!node->isOperator) return node->toString() ;
  const MamdaniOperator * mamdaniOperator        =
    dynamic_cast<const MamdaniOperator*> (node)  ;
  QString L = ""                                 ;
  L += toStringPostfix(mamdaniOperator->left )   ;
  L += " "                                       ;
  L += toStringPostfix(mamdaniOperator->right)   ;
  L += " "                                       ;
  L += mamdaniOperator->toString( )              ;
  L += " "                                       ;
  return L                                       ;
}
