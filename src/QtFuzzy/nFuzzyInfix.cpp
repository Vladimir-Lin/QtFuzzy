#include <qtfuzzy.h>

N::Fuzzy::Infix:: Infix(void)
{
  loadGenericFunctions ( ) ;
  loadGenericOperators ( ) ;
}

N::Fuzzy::Infix::~Infix(void)
{
  QStringList K                 ;
  ///////////////////////////////
  K = _genericOperators.keys( ) ;
  nFullLoop ( i , K . count() ) {
    QString k = K[i]            ;
    delete _genericOperators[k] ;
  }                             ;
  _genericOperators . clear ( ) ;
  K                 . clear ( ) ;
  ///////////////////////////////
  K = _genericFunctions.keys( ) ;
  nFullLoop ( i , K . count() ) {
    QString k = K[i]            ;
    delete _genericFunctions[k] ;
  }                             ;
  _genericFunctions . clear ( ) ;
  K                 . clear ( ) ;
}

bool N::Fuzzy::Infix::isOperand(const QString & name) const
{
  //An operand is not a parenthesis...
  if (name == "(" || name == ")" || name == ",") return false ;
  //nor an operator...
  if (isOperator(name)                         ) return false ;
  //nor a function...
  if (isFunction(name)                         ) return false ;
  //...it is everything else :)
  return true                                                 ;
}

bool N::Fuzzy::Infix::isOperator(const QString & name) const
{
  return _genericOperators . contains ( name ) ;
}

bool N::Fuzzy::Infix::isFunction(const QString & name) const
{
  return _genericFunctions . contains ( name ) ;
}

QString N::Fuzzy::Infix::toPostfix(const QString & infixString)
{
  //TODO: inserts spaces in all operators, parentheses, and commas.
#ifdef UNFINISHED_BUSINESS
  std::vector<std::string> space;
  std::map<std::string, GenericOperator*>::const_iterator itGO = this->_genericOperators.begin();
  for (; itGO != this->_genericOperators.end(); ++itGO) {
    if (itGO->first == Rule::FL_AND or itGO->first == Rule::FL_OR)
    continue;
    space.push_back(itGO->first);
  }
  space.push_back("(");
  space.push_back(")");
  space.push_back(",");

  QString infix = infixString;
  for (std::size_t i = 0; i < space.size(); ++i) {
    infix = Op::findReplace(infix, space[i], " " + space[i] + " ", true);
  }
  FL_LOG("infix=" << infix);
#else
  QString infix = infixString                                                 ;
#endif
  /////////////////////////////////////////////////////////////////////////////
  QQueue<QString> queue                                                       ;
  QStack<QString> stack                                                       ;
  /////////////////////////////////////////////////////////////////////////////
  QStringList Token = infix.split(' ')                                        ;
  nFullLoop ( i , Token . count() )                                           {
    QString t = Token [ i ]                                                   ;
    if (isOperand(t))                                                         {
      queue . enqueue ( t )                                                   ;
    } else
    if (isFunction(t))                                                        {
      stack . push    ( t )                                                   ;
    } else
    if (t == ",")                                                             {
      while (!stack.empty() && stack.top() != "(")                            {
        queue . enqueue ( stack.top() )                                       ;
        stack . pop     (             )                                       ;
      }                                                                       ;
      if (stack.empty() || stack.top() != "(")                                {
//        ex << "mismatching parentheses in: " << infixString;
        return ""                                                             ;
      }                                                                       ;
    } else
    if (isOperator(t))                                                        {
      GenericOperator * op1 = getGenericOperator(t)                           ;
      while (true)                                                            {
        GenericOperator * op2 = NULL                                          ;
        if (!stack.empty() && isOperator(stack.top()))                        {
          op2 = getGenericOperator(stack.top())                               ;
        } else break                                                          ;
        if (((op1->associativity<0) && (op1->precedence<=op2->precedence))   ||
             (op1->precedence   <op2->precedence)                           ) {
          queue . enqueue ( stack.top() )                                     ;
          stack . pop     (             )                                     ;
        } else break                                                          ;
      }                                                                       ;
      stack . push ( t )                                                      ;
    } else
    if (t == "(")                                                             {
      stack.push(t)                                                           ;
    } else
    if (t == ")")                                                             {
      while (!stack.empty() && stack.top() != "(")                            {
        queue . enqueue ( stack.top() )                                       ;
        stack . pop     (             )                                       ;
      }                                                                       ;
      if (stack.empty() || stack.top() != "(")                                {
//        ex << "mismatching parentheses in: " << infixString;
        return ""                                                             ;
      }                                                                       ;
      stack . pop()                                                           ; //get rid of "("
      if (!stack.empty() && isFunction(stack.top()))                          {
        queue . enqueue ( stack.top() )                                       ;
        stack . pop     (             )                                       ;
      }                                                                       ;
    } else                                                                    {
//      ex << "this should have never occurred!";
      return ""                                                               ;
    }                                                                         ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  while (!stack.empty())                                                      {
    if (stack.top() == "(" || stack.top() == ")")                             {
//      ex << "mismatching parentheses in: " << infixString;
      return ""                                                               ;
    }                                                                         ;
    queue . enqueue ( stack.top() )                                           ;
    stack . pop     (             )                                           ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  QString SPF = ""                                                            ;
  while (!queue.empty())                                                      {
    SPF += queue.head()                                                       ;
    queue. dequeue   ()                                                       ;
    if (!queue.empty()) SPF += " "                                            ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  return SPF                                                                  ;
}

void N::Fuzzy::Infix::loadGenericOperators(void)
{
  char p = 7                                                                 ;
  // (!) Logical and (~) Bitwise NOT
  _genericOperators["!"           ] = new GenericOperator("!", p, 1        ) ;
  _genericOperators["~"           ] = new GenericOperator("~", p, 1        ) ;
  --p; //Power
  _genericOperators["^"           ] = new GenericOperator("^", p, 2, 1     ) ;
  --p; //Multiplication, Division, and Modulo
  _genericOperators["*"           ] = new GenericOperator("*"           , p) ;
  _genericOperators["/"           ] = new GenericOperator("/"           , p) ;
  _genericOperators["%"           ] = new GenericOperator("%"           , p) ;
  --p; //Addition, Subtraction
  _genericOperators["+"           ] = new GenericOperator("+"           , p) ;
  _genericOperators["-"           ] = new GenericOperator("-"           , p) ;
  --p; //Bitwise AND
  _genericOperators["&"           ] = new GenericOperator("&"           , p) ;
  --p; //Bitwise OR
  _genericOperators["|"           ] = new GenericOperator("|"           , p) ;
  --p; //Logical AND (symbolic and verbose)
  _genericOperators[Rule::FuzzyAND] = new GenericOperator(Rule::FuzzyAND, p) ;
  _genericOperators["&&"          ] = new GenericOperator("&&"          , p) ;
  --p; //Logical OR (symbolic and verbose)
  _genericOperators[Rule::FuzzyOR ] = new GenericOperator(Rule::FuzzyOR , p) ;
  _genericOperators["||"          ] = new GenericOperator("||"          , p) ;
}

void N::Fuzzy::Infix::loadGenericFunctions(void)
{
  #define GF(name) _genericFunctions[#name] = new GenericFunction(#name,&(std::name))
  GF ( acos  ) ;
  GF ( asin  ) ;
  GF ( atan  ) ;
  GF ( atan2 ) ;
  GF ( ceil  ) ;
  GF ( cos   ) ;
  GF ( cosh  ) ;
  GF ( exp   ) ;
  GF ( fabs  ) ;
  GF ( floor ) ;
  GF ( log   ) ;
  GF ( log10 ) ;
  GF ( pow   ) ;
  GF ( sin   ) ;
  GF ( sinh  ) ;
  GF ( sqrt  ) ;
  GF ( tan   ) ;
  GF ( tanh  ) ;
  #undef  GF
}

void N::Fuzzy::Infix::addGenericOperator(GenericOperator * genericOperator)
{
  _genericOperators[genericOperator->name] = genericOperator ;
}

N::Fuzzy::GenericOperator * N::Fuzzy::Infix::removeGenericOperator(const QString & key)
{
  if (!_genericOperators.contains(key)) return NULL ;
  GenericOperator * result = _genericOperators[key] ;
  _genericOperators.remove(key)                     ;
  return result                                     ;
}

N::Fuzzy::GenericOperator * N::Fuzzy::Infix::getGenericOperator(const QString & key) const
{
  if (!_genericOperators.contains(key)) return NULL ;
  return _genericOperators[key]                     ;
}

const QMap<QString,N::Fuzzy::GenericOperator *> & N::Fuzzy::Infix::genericOperators(void) const
{
  return _genericOperators ;
}

void N::Fuzzy::Infix::addGenericFunction(GenericFunction * genericFunction)
{
  _genericFunctions[genericFunction->name] = genericFunction ;
}

N::Fuzzy::GenericFunction * N::Fuzzy::Infix::removeGenericFunction(const QString & key)
{
  if (!_genericFunctions.contains(key)) return NULL           ;
  N::Fuzzy::GenericFunction * result = _genericFunctions[key] ;
  _genericFunctions.remove(key)                               ;
  return result                                               ;
}

N::Fuzzy::GenericFunction * N::Fuzzy::Infix::getGenericFunction(const QString & key) const
{
  if (!_genericFunctions.contains(key)) return NULL ;
  return _genericFunctions[key]                     ;
}

const QMap<QString,N::Fuzzy::GenericFunction *> & N::Fuzzy::Infix::genericFunctions(void) const
{
  return _genericFunctions ;
}
