#include <qtfuzzy.h>

N::Fuzzy::FisExporter:: FisExporter (void)
                      : Exporter    (    )
{
}

N::Fuzzy::FisExporter::~FisExporter (void)
{
}

QString N::Fuzzy::FisExporter::name(void) const
{
  return "N::Fuzzy::FisExporter" ;
}

QString N::Fuzzy::FisExporter::toString(const Engine * engine) const
{
  QString R = ""                         ;
  R += exportSystem (engine) ; R += "\n" ;
  R += exportInputs (engine) ; R += "\n" ;
  R += exportOutputs(engine) ; R += "\n" ;
  R += exportRules  (engine) ; R += "\n" ;
  return R                               ;
}

QString N::Fuzzy::FisExporter::exportSystem(const Engine * engine) const
{
  QString R                                                                   ;
  R  = "[System]\n"                                                           ;
  R += QString("Name='%1'\n"     ).arg(engine->getName())                     ;
  R += QString("Type='mamdani'\n")                                            ;
  R += QString("Version=%1\n"    ).arg(EXCITON_VERSION_STRING)                ;
  R += QString("NumInputs=%1\n"  ).arg(engine->numberOfInputVariables ())     ;
  R += QString("NumOutputs=%1\n" ).arg(engine->numberOfOutputVariables())     ;
  // ?? this is questionable
  if (engine->numberOfRuleBlocks()>0)                                         {
    R += QString("NumRules=%1\n" )
         .arg(engine->getRuleBlock(0)->numberOfRules())                       ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  const TNorm  * tnorm        = NULL                                          ;
  const SNorm  * snorm        = NULL                                          ;
  const TNorm  * activation   = NULL                                          ;
  const SNorm  * accumulation = NULL                                          ;
  Defuzzifier  * defuzzifier  = NULL                                          ;
  /////////////////////////////////////////////////////////////////////////////
  nFullLoop ( i , engine->numberOfRuleBlocks() )                              {
    RuleBlock * rb = engine->getRuleBlock(i)                                  ;
    if (IsNull(rb->getTnorm     ())) continue                                 ;
    if (IsNull(rb->getSnorm     ())) continue                                 ;
    if (IsNull(rb->getActivation())) continue                                 ;
    ///////////////////////////////////////////////////////////////////////////
    if (IsNull(tnorm)) tnorm = rb->getTnorm(); else
    if (tnorm->className() != rb->getTnorm()->className()) break              ;
    if (IsNull(snorm)) snorm = rb->getSnorm(); else
    if (snorm->className() != rb->getSnorm()->className()) break              ;
    if (IsNull(activation)) activation = rb->getActivation(); else
    if (activation->className() != rb->getActivation()->className()) break    ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  if (IsNull(tnorm     )) return R                                            ;
  if (IsNull(snorm     )) return R                                            ;
  if (IsNull(activation)) return R                                            ;
  R += QString("AndMethod='%1'\n").arg(toFis(tnorm     ))                     ;
  R += QString("OrMethod='%1'\n" ).arg(toFis(snorm     ))                     ;
  R += QString("ImpMethod='%1'\n").arg(toFis(activation))                     ;
  /////////////////////////////////////////////////////////////////////////////
  nFullLoop ( i , engine->numberOfOutputVariables() )                         {
    OutputVariable * outputVariable = engine->getOutputVariable(i)            ;
    if (IsNull(outputVariable->getDefuzzifier())) continue                    ;
    if (IsNull(outputVariable->output()->getAccumulation())) continue         ;
    ///////////////////////////////////////////////////////////////////////////
    if (IsNull(defuzzifier))                                                  {
      defuzzifier = outputVariable->getDefuzzifier()                          ;
    } else
    if (defuzzifier->className() !=
      outputVariable->getDefuzzifier()->className()) break                    ;
    if (IsNull(accumulation))                                                 {
      accumulation = outputVariable->output()->getAccumulation()              ;
    } else
    if (accumulation->className() !=
        outputVariable->output()->getAccumulation()->className()) break       ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  if (IsNull(accumulation)) return R                                          ;
  if (IsNull(defuzzifier )) return R                                          ;
  /////////////////////////////////////////////////////////////////////////////
  R += QString("AggMethod='%1'\n"   ).arg(toFis(accumulation))                ;
  R += QString("DefuzzMethod='%1'\n").arg(toFis(defuzzifier  ))               ;
  return R                                                                    ;
}

QString N::Fuzzy::FisExporter::exportInputs(const Engine * engine) const
{
  QString R                                               ;
  nFullLoop ( ixVar , engine->numberOfInputVariables() )  {
    InputVariable * var = engine->getInputVariable(ixVar) ;
    R += QString("[%1]\n"     ).arg(var->getName())       ;
    R += QString("Name='%1'\n").arg(var->getName())       ;
    R += QString("Range=[%1 %2]\n")
         .arg(var->getMinimum())
         .arg(var->getMaximum())                          ;
    R += QString("NumMFs=%1\n").arg(var->numberOfTerms()) ;
    nFullLoop ( ixTerm , var->numberOfTerms() )           {
      R += QString("MF%1='%1':%2\n")
              .arg(ixTerm + 1)
              .arg(var->getTerm(ixTerm)->Name)
              .arg(toFis(var->getTerm(ixTerm)))           ;
    }                                                     ;
    R += "\n"                                             ;
  }                                                       ;
  return R                                                ;
}

QString N::Fuzzy::FisExporter::exportOutputs(const Engine * engine) const
{
  QString R                                                    ;
  nFullLoop ( ixVar , engine->numberOfOutputVariables() )      {
    OutputVariable * var = engine->getOutputVariable(ixVar)    ;
    R += QString("[%1]\n"     ).arg(var->getName())            ;
    R += QString("Name='%1'\n").arg(var->getName())            ;
    R += QString("Range=[%1 %2]\n")
         .arg(var->getMinimum())
         .arg(var->getMaximum())                               ;
    R += QString("Default=%1\n")
         .arg(Operation::str(var->getDefaultValue(),3))        ;
    R += QString("Lock=%1\n").arg(var->lockDefuzzifiedValue()) ;
    R += QString("NumMFs=%1\n").arg(var->numberOfTerms())      ;
    nFullLoop ( ixTerm , var->numberOfTerms() )                {
      R += QString("MF%1='%1':%2\n")
              .arg(ixTerm + 1)
              .arg(var->getTerm(ixTerm)->Name)
              .arg(toFis(var->getTerm(ixTerm)))                ;
    }                                                          ;
    R += "\n"                                                  ;
  }                                                            ;
  return R                                                     ;
}

QString N::Fuzzy::FisExporter::exportRules(const Engine * engine) const
{
  QString R = "[Rules]\n"                                  ;
  nFullLoop ( ixRuleBlock , engine->numberOfRuleBlocks() ) {
    RuleBlock * rb = engine->getRuleBlock(ixRuleBlock)     ;
    if (engine->numberOfRuleBlocks() > 1)                  {
      R += QString("# RuleBlock %1\n").arg(rb->getName())  ;
    }                                                      ;
    nFullLoop ( ixRule , rb->numberOfRules() )             {
      R += exportRule(dynamic_cast<MamdaniRule *>
                      (rb->getRule(ixRule)),engine)        ;
      R += "\n"                                            ;
    }                                                      ;
  }                                                        ;
  return R                                                 ;
}

QString N::Fuzzy::FisExporter::exportRule (
          const MamdaniRule * rule        ,
          const Engine      * engine      ) const
{
  QString R = ""                                                              ;
  if (IsNull(rule)) return R                                                  ;
  /////////////////////////////////////////////////////////////////////////////
  QVector<MamdaniProposition *> propositions                                  ;
  QVector<MamdaniOperator    *> operators                                     ;
  /////////////////////////////////////////////////////////////////////////////
  QQueue<MamdaniExpression *> bfsQueue                                        ;
  bfsQueue.enqueue(rule->getAntecedent()->getRoot())                          ;
  while (!bfsQueue.empty())                                                   {
    MamdaniExpression * front = bfsQueue.front()                              ;
    bfsQueue.dequeue()                                                        ;
    if (front->isOperator)                                                    {
      MamdaniOperator * op                                                    ;
      op = dynamic_cast<MamdaniOperator *> (front)                            ;
      if (NotNull(op))                                                        {
        bfsQueue  . enqueue   ( op->left  )                                   ;
        bfsQueue  . enqueue   ( op->right )                                   ;
        operators . push_back ( op        )                                   ;
      }                                                                       ;
    } else                                                                    {
      propositions.push_back(dynamic_cast<MamdaniProposition*>(front))        ;
    }                                                                         ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  bool equalOperators = true                                                  ;
  for (int i = 0; i < (int) operators.size() - 1; ++i)                        {
    if (operators.at(i)->name != operators.at(i + 1)->name)                   {
      equalOperators = false                                                  ;
      break                                                                   ;
    }                                                                         ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  if (!equalOperators) return R                                               ;
  QVector<Variable *> inputVariables, outputVariables                         ;
  nFullLoop ( i , engine->numberOfInputVariables () )                         {
    inputVariables.push_back(engine->getInputVariable(i))                     ;
  }                                                                           ;
  nFullLoop ( i , engine->numberOfOutputVariables() )                         {
    outputVariables.push_back(engine->getOutputVariable(i))                   ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  R += translate(propositions, inputVariables)                                ;
  R += ", "                                                                   ;
  R += translate(rule->getConsequent()->conclusions(), outputVariables)       ;
  R += QString("(%1) : ").arg(rule->getWeight())                              ;
  if (operators.size() == 0) R += "1" ; else                                  {
    if (operators.at(0)->name == Rule::FuzzyAND) R += "1" ; else
    if (operators.at(0)->name == Rule::FuzzyOR ) R += "2" ; else
      R += operators.at(0)->name                                              ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  return R                                                                    ;
}

QString N::Fuzzy::FisExporter::translate                     (
          const QVector<MamdaniProposition *> & propositions ,
          const QVector<Variable           *>   variables    ) const
{
  QString R = ""                                                              ;
  /////////////////////////////////////////////////////////////////////////////
  nFullLoop ( ixVariable , variables.size() )                                 {
    Variable * variable = variables.at(ixVariable)                            ;
    int    termIndexPlusOne = 0                                               ;
    double plusHedge        = 0                                               ;
    double negated          = 1                                               ;
    ///////////////////////////////////////////////////////////////////////////
    nFullLoop ( ixProposition  , propositions.size() )                        {
      MamdaniProposition * proposition = propositions.at(ixProposition)       ;
      if (proposition->variable != variable) continue                         ;
      nFullLoop ( termIndex , variable->numberOfTerms() )                     {
        if (variable->getTerm(termIndex) == proposition->term)                {
          termIndexPlusOne = termIndex + 1                                    ;
          break                                                               ;
        }                                                                     ;
      }                                                                       ;
      /////////////////////////////////////////////////////////////////////////
      QVector<Hedge *> hedges = proposition->hedges                           ;
      nFullLoop ( ixHedge , hedges.size() )                                   {
        Hedge * hedge = hedges.at(ixHedge)                                    ;
        if (hedge->name() == Not      ().name()) negated   *= -1 ; else
        if (hedge->name() == Somewhat ().name()) plusHedge +=  5 ; else
        if (hedge->name() == Extremely().name()) plusHedge +=  3 ; else
        if (hedge->name() == Very     ().name()) plusHedge +=  2 ; else
          plusHedge = std::numeric_limits<double>::quiet_NaN()                ;
      }                                                                       ;
      break                                                                   ;
    }                                                                         ;
    if (negated < 0) R += "-"                                                 ;
    R += termIndexPlusOne                                                     ;
    if (!Operation::isEq(plusHedge, 0.0))                                     {
      R += "."                                                                ;
      R += Operation::str(plusHedge,0.0)                                      ;
    }                                                                         ;
    R += " "                                                                  ;
  }                                                                           ;
  return R                                                                    ;
}

QString N::Fuzzy::FisExporter::toFis(const TNorm * tnorm) const
{
  if (IsNull(tnorm)) return ""                          ;
  QString name = tnorm->className()                     ;
  #define FMAP(A,B) if (name == A().className()) return B
  FMAP ( Minimum           , "min"                )     ;
  FMAP ( AlgebraicProduct  , "prod"               )     ;
  FMAP ( BoundedDifference , "bounded_difference" )     ;
  FMAP ( DrasticProduct    , "drastic_product"    )     ;
  FMAP ( EinsteinProduct   , "einstein_product"   )     ;
  FMAP ( HamacherProduct   , "hamacher_product"   )     ;
  #undef  FMAP
  return name                                           ;
}

QString N::Fuzzy::FisExporter::toFis(const SNorm * snorm) const
{
  if (IsNull(snorm)) return ""                          ;
  QString name = snorm->className()                     ;
  #define FMAP(A,B) if (name == A().className()) return B
  FMAP ( Maximum       , "max"            )             ;
  FMAP ( AlgebraicSum  , "sum"            )             ;
  FMAP ( BoundedSum    , "bounded_sum"    )             ;
  FMAP ( NormalizedSum , "normalized_sum" )             ;
  FMAP ( DrasticSum    , "drastic_sum"    )             ;
  FMAP ( EinsteinSum   , "einstein_sum"   )             ;
  FMAP ( HamacherSum   , "hamacher_sum"   )             ;
  #undef  FMAP
  return name                                           ;
}

QString N::Fuzzy::FisExporter::toFis(const Defuzzifier * defuzzifier) const
{
  nKickOut (IsNull(defuzzifier) , ""    ) ;
  #define FMAP(A,B) if (defuzzifier->className() == A().className()) return B
  FMAP ( Centroid          , "centroid" ) ;
  FMAP ( SmallestOfMaximum , "som"      ) ;
  FMAP ( LargestOfMaximum  , "lom"      ) ;
  FMAP ( MeanOfMaximum     , "mom"      ) ;
  #undef  FMAP
  return defuzzifier->className()         ;
}

QString N::Fuzzy::FisExporter::toFis(const Term * term) const
{
  QString R                                                                   ;
  /////////////////////////////////////////////////////////////////////////////
  if (term->className() == Bell().className())                                {
    const Bell * x = dynamic_cast<const Bell *>(term)                         ;
    double params[] = { x->getWidth() , x->getSlope() , x->getCenter() }      ;
    R += QString("'gbellmf',[%1]").arg(Operation::str(3,params," ",3))        ;
    return R                                                                  ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  if (term->className() == Discrete().className())                            {
    const Discrete * x = dynamic_cast<const Discrete *>(term)                 ;
    R += "'discretemf',["                                                     ;
    QStringList L                                                             ;
    nFullLoop ( i , x->x.size() )                                             {
      L << Operation::str(x->x.at(i),3)                                       ;
      L << Operation::str(x->y.at(i),3)                                       ;
    }                                                                         ;
    R += L.join(" ")                                                          ;
    R += "]"                                                                  ;
    return R                                                                  ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  if (term->className() == Gaussian().className())                            {
    const Gaussian * x = dynamic_cast<const Gaussian *> (term)                ;
    double params[] = { x->getStandardDeviation() , x->getMean() }            ;
    R += QString("'gaussmf',[%1]").arg(Operation::str(2,params," ",3))        ;
    return R                                                                  ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  if (term->className() == GaussianProduct().className())                     {
    const GaussianProduct * x                                                 =
      dynamic_cast<const GaussianProduct *> (term)                            ;
    double params[] = { x->getStandardDeviationA() , x->getMeanA()            ,
                        x->getStandardDeviationB() , x->getMeanB()          } ;
    R += QString("'gauss2mf',[%1]").arg(Operation::str(4,params," ",3))       ;
    return R                                                                  ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  if (term->className() == PiShape().className())                             {
    const PiShape * x = dynamic_cast<const PiShape *> (term)                  ;
    double params[] = { x->getBottomLeft() , x->getTopLeft    ()              ,
                        x->getTopRight  () , x->getBottomRight()            } ;
    R += QString("'pimf',[%1]").arg(Operation::str(4,params," ",3))           ;
    return R                                                                  ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  if (term->className() == Ramp().className())                                {
    const Ramp * x = dynamic_cast<const Ramp *> (term)                        ;
    double params[] = { x->getStart() , x->getEnd() }                         ;
    R += QString("'rampmf',[%1]").arg(Operation::str(2,params," ",3))         ;
    return R                                                                  ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  if (term->className() == Rectangle().className())                           {
    const Rectangle * x = dynamic_cast<const Rectangle *> (term)              ;
    double params[] = { x->getMinimum() , x->getMaximum() }                   ;
    R += QString("'rectmf',[%1]").arg(Operation::str(2,params," ",3))         ;
    return R                                                                  ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  if (term->className() == SShape().className())                              {
    const SShape * x = dynamic_cast<const SShape *> (term)                    ;
    double params[] = { x->getStart() , x->getEnd() }                         ;
    R += QString("'smf',[%1]").arg(Operation::str(2,params," ",3))            ;
    return R                                                                  ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  if (term->className() == Sigmoid().className())                             {
    const Sigmoid * x = dynamic_cast<const Sigmoid *> (term)                  ;
    double params[] = { x->getSlope() , x->getInflection() }                  ;
    R += QString("'sigmf',[%1]").arg(Operation::str(2,params," ",3))          ;
    return R                                                                  ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  if (term->className() == SigmoidDifference().className())                   {
    const SigmoidDifference * x = dynamic_cast<const SigmoidDifference *>(term);
    double params[] = { x->getRising () , x->getLeft ()                       ,
                        x->getFalling() , x->getRight()                     } ;
    R += QString("'dsigmf',[%1]").arg(Operation::str(4,params," ",3))         ;
    return R                                                                  ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  if (term->className() == SigmoidProduct().className())                      {
    const SigmoidProduct * x = dynamic_cast<const SigmoidProduct *> (term)    ;
    double params[] = { x->getRising () , x->getLeft ()                       ,
                        x->getFalling() , x->getRight()                     } ;
    R += QString("'psigmf',[%1]").arg(Operation::str(4,params," ",3))         ;
    return R                                                                  ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  if (term->className() == Trapezoid().className())                           {
    const Trapezoid * x = dynamic_cast<const Trapezoid *> (term)              ;
    double params[] = { x->getA() , x->getB() , x->getC() , x->getD() }       ;
    R += QString("'trapmf',[%1]").arg(Operation::str(4,params," ",3))         ;
    return R                                                                  ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  if (term->className() == Triangle().className())                            {
    const Triangle * x = dynamic_cast<const Triangle *> (term)                ;
    double params[] = { x->getA() , x->getB() , x->getC() }                   ;
    R += QString("'trimf',[%1]").arg(Operation::str(3,params," ",3))          ;
    return R                                                                  ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  if (term->className() == ZShape().className())                              {
    const ZShape * x = dynamic_cast<const ZShape *>(term)                     ;
    double params[] = { x->getStart() , x->getEnd() }                         ;
    R += QString("'zmf',[%1]").arg(Operation::str(2,params," ",3))            ;
    return R                                                                  ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
//    ss << "[exporter error] term of class <" << term->className() << "> not supported";
  return ""                                                                   ;
}
