#include <qtfuzzy.h>

N::Fuzzy::CppExporter:: CppExporter (void)
                      : Exporter    (    )
{
}

N::Fuzzy::CppExporter::~CppExporter(void)
{
}

QString N::Fuzzy::CppExporter::name(void) const
{
  return "N::Fuzzy::CppExporter" ;
}

QString N::Fuzzy::CppExporter::toString(const Engine * engine) const
{
  QString cpp = ""                                                            ;
  QString gn  = engine->getName()                                             ;
  /////////////////////////////////////////////////////////////////////////////
  cpp += QString("N::Fuzzy::Engine * %1 = new N::Fuzzy::Engine() ;\n").arg(gn);
  cpp += QString("%1->setName(\"%2\") ;\n").arg(gn).arg(gn)                   ;
  /////////////////////////////////////////////////////////////////////////////
  nFullLoop ( i , engine->numberOfHedges() )                                  {
    QString hn = toCpp(engine->getHedge(i))                                   ;
    if (hn.length()>0)                                                        {
      cpp += QString("%1->addHedge(%2) ;\n").arg(gn).arg(hn)                  ;
    }                                                                         ;
  }                                                                           ;
  cpp += "\n"                                                                 ;
  /////////////////////////////////////////////////////////////////////////////
  nFullLoop ( i , engine->numberOfInputVariables() )                          {
    InputVariable * input = engine->getInputVariable(i)                       ;
    cpp += QString("N::Fuzzy::InputVariable * %1 = new N::Fuzzy::InputVariable() ;\n")
           .arg(input->getName())                                             ;
    cpp += QString("%1->setName(\"%2\") ;\n")
           .arg(input->getName())
           .arg(input->getName())                                             ;
    cpp += QString("%1->setRange(%2,%3) ;\n")
            .arg(input->getName())
            .arg(Operation::str(input->getMinimum(),3))
            .arg(Operation::str(input->getMaximum(),3))                       ;
    nFullLoop( z , input->numberOfTerms() )                                   {
      cpp += QString("%1->addTerm(%2) ;\n")
             .arg(input->getName())
             .arg(toCpp(input->getTerm(z)))                                   ;
    }                                                                         ;
    cpp += QString("%1->addInputVariable(%2) ;\n\n")
           .arg(gn).arg(input->getName())                                     ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  nFullLoop ( i , engine->numberOfOutputVariables() )                         {
    OutputVariable * output = engine->getOutputVariable(i)                    ;
    cpp += QString("N::Fuzzy::OutputVariable * %1 = new N::Fuzzy::OutputVariable() ;\n")
           .arg(output->getName())                                            ;
    cpp += QString("%1->setName(\"%2\") ;\n")
           .arg(output->getName())
           .arg(output->getName())                                            ;
    cpp += QString("%1->setRange(%2,%3) ;\n")
           .arg(output->getName())
           .arg(Operation::str(output->getMinimum(),3))
           .arg(Operation::str(output->getMaximum(),3))                       ;
    cpp += QString("%1->setDefaultValue(")
           .arg(output->getName())                                            ;
    double defaultValue = output->getDefaultValue()                           ;
    if ( Operation :: isNan ( defaultValue ) )
      cpp += "std::numeric_limits<double>::quiet_NaN()"                       ;
    else
    if ( Operation :: isInf ( defaultValue ) )                                {
      cpp += (defaultValue < 0 ? "-" : "")                                    ;
      cpp += "std::numeric_limits<double>::infinity()"                        ;
    } else
      cpp += Operation :: str ( defaultValue , 3 )                            ;
    cpp += ") ;\n"                                                            ;
    cpp += QString("%1->setLockDefuzzifiedValue(%2) ;\n")
           .arg(output->getName())
           .arg((output->lockDefuzzifiedValue() ? "true" : "false"))          ;
    cpp += QString("%1->setDefuzzifier(%2) ;\n")
           .arg(output->getName())
           .arg(toCpp(output->getDefuzzifier()))                              ;
    cpp += QString("%1->output()->setAccumulation(%2) ;\n")
           .arg(output->getName())
           .arg(toCpp(output->output()->getAccumulation()))                   ;
    nFullLoop ( v , output->numberOfTerms() )                                 {
      cpp += QString("%1->addTerm(%2) ;\n")
             .arg(output->getName())
             .arg(toCpp(output->getTerm(v)))                                  ;
    }                                                                         ;
    cpp += QString("%1->addOutputVariable(%2) ;\n\n")
           .arg(gn).arg(output->getName())                                    ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  if (engine->numberOfRuleBlocks()>0)                                         {
    cpp += "QStringList RuleLists ;\n"                                        ;
  }                                                                           ;
  nFullLoop ( i , engine->numberOfRuleBlocks() )                              {
    RuleBlock * ruleblock = engine->getRuleBlock(i)                           ;
    cpp += QString("N::Fuzzy::RuleBlock * %1 = new N::Fuzzy::RuleBlock() ;\n" )
           .arg(ruleblock->getName())                                         ;
    cpp += QString("%1->setName(\"%2\") ;\n")
           .arg(ruleblock->getName())
           .arg(ruleblock->getName())                                         ;
    cpp += QString("%1->setTnorm(%2) ;\n")
           .arg(ruleblock->getName())
           .arg(toCpp(ruleblock->getTnorm()))                                 ;
    cpp += QString("%1->setSnorm(%2) ;\n")
           .arg(ruleblock->getName())
           .arg(toCpp(ruleblock->getSnorm()))                                 ;
    cpp += QString("%1->setActivation(%2) ;\n")
           .arg(ruleblock->getName())
           .arg(toCpp(ruleblock->getActivation()))                            ;
    cpp += "\n"                                                               ;
    if (ruleblock->numberOfRules() > 0)                                       {
      cpp += "RuleLists . clear () ;\n"                                       ;
    }                                                                         ;
    nFullLoop ( r , ruleblock->numberOfRules() )                              {
      cpp += QString("RuleLists << \"%1\" ;\n")
             .arg(ruleblock->getRule(r)->getUnparsedRule())                   ;
    }                                                                         ;
    if (ruleblock->numberOfRules() > 0)                                       {
      cpp += "for (int i=0;i<RuleLists.count();i++) {\n"                      ;
      cpp += "  QString rbl = RuleLists[i] ;\n"                               ;
      cpp += QString("  %1->addRule(N::Fuzzy::MamdaniRule::parse(rbl,engine)) ;\n")
             .arg(ruleblock->getName())                                       ;
      cpp += "} ;\n"                                                          ;
    }                                                                         ;
    cpp += QString("%1->addRuleBlock(%2) ;\n")
           .arg(gn).arg(ruleblock->getName())                                 ;
  }                                                                           ;
  cpp += "\n"                                                                 ;
  return cpp                                                                  ;
}

QString N::Fuzzy::CppExporter::toCpp(const Term * term) const
{
  if (IsNull(term)) return "NULL"                                             ;
  /////////////////////////////////////////////////////////////////////////////
  QString R                                                                   ;
  R = QString("new %1( \"%2\" , ").arg(term->className()).arg(term->Name)     ;
  /////////////////////////////////////////////////////////////////////////////
  if (term->className() == Bell().className())                                {
    const Bell * x = dynamic_cast<const Bell *> (term)                        ;
    double params[] = {x->getCenter(), x->getWidth(), x->getSlope()}          ;
    R += Operation :: str ( 3 , params , " , " , 3 )                          ;
    R += ")"                                                                  ;
    return R                                                                  ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  if (term->className() == Discrete().className())                            {
    QStringList L                                                             ;
    const Discrete * x = dynamic_cast<const Discrete *> (term)                ;
    R += QString("%1 , ").arg(x->x.size() + x->y.size())                      ;
    nFullLoop ( i , x->x.size() )                                             {
      L << QString("%1 , %2").arg(Operation::str(x->x.at(i)),3                )
                             .arg(Operation::str(x->y.at(i)),3              ) ;
    }                                                                         ;
    R += L.join(" , ")                                                        ;
    R += ")"                                                                  ;
    return R                                                                  ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  if (term->className() == Gaussian().className())                            {
    const Gaussian * x = dynamic_cast<const Gaussian *>(term)                 ;
    double params[] = { x->getMean() , x->getStandardDeviation() }            ;
    R += Operation::str( 2 , params , " , " , 3 )                             ;
    R += " )"                                                                 ;
    return R                                                                  ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  if (term->className() == GaussianProduct().className())                     {
    const GaussianProduct * x                                                 =
      dynamic_cast<const GaussianProduct *>(term)                             ;
    double params[] = {x->getMeanA(), x->getStandardDeviationA()              ,
                       x->getMeanB(), x->getStandardDeviationB()            } ;
    R += Operation::str( 4 , params , " , " , 3 )                             ;
    R += " )"                                                                 ;
    return R                                                                  ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  if (term->className() == PiShape().className())                             {
    const PiShape * x = dynamic_cast<const PiShape *>(term)                   ;
    double params[] = { x->getBottomLeft(), x->getTopLeft    ()               ,
                        x->getTopRight  (), x->getBottomRight()             } ;
    R += Operation::str( 4 , params , " , " , 3 )                             ;
    R += " )"                                                                 ;
    return R                                                                  ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  if (term->className() == Ramp().className())                                {
    const Ramp * x = dynamic_cast<const Ramp *>(term)                         ;
    double params[] = { x->getStart() , x->getEnd() }                         ;
    R += Operation::str( 2 , params , " , " , 3 )                             ;
    R += " )"                                                                 ;
    return R                                                                  ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  if (term->className() == Rectangle().className())                           {
    const Rectangle * x = dynamic_cast<const Rectangle *>(term)               ;
    double params[] = { x->getMinimum() , x->getMaximum() }                   ;
    R += Operation::str( 2 , params , " , " , 3 )                             ;
    R += " )"                                                                 ;
    return R                                                                  ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  if (term->className() == SShape().className())                              {
    const SShape * x = dynamic_cast<const SShape *>(term)                     ;
    double params[] = { x->getStart() , x->getEnd() }                         ;
    R += Operation::str( 2 , params , " , " , 3 )                             ;
    R += " )"                                                                 ;
    return R                                                                  ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  if (term->className() == Sigmoid().className())                             {
    const Sigmoid * x = dynamic_cast<const Sigmoid *>(term)                   ;
    double params[] = { x->getInflection() , x->getSlope() }                  ;
    R += Operation::str( 2 , params , " , " , 3 )                             ;
    R += " )"                                                                 ;
    return R                                                                  ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  if (term->className() == SigmoidDifference().className())                   {
    const SigmoidDifference * x                                               =
      dynamic_cast<const SigmoidDifference *> (term)                          ;
    double params[] = { x->getLeft   () , x->getRising()                      ,
                        x->getFalling() , x->getRight ()                    } ;
    R += Operation::str( 4 , params , " , " , 3 )                             ;
    R += " )"                                                                 ;
    return R                                                                  ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  if (term->className() == SigmoidProduct().className())                      {
    const SigmoidProduct * x                                                  =
      dynamic_cast<const SigmoidProduct *>(term)                              ;
    double params[] = { x->getLeft   () , x->getRising()                      ,
                        x->getFalling() , x->getRight ()                    } ;
    R += Operation::str( 4 , params , " , " , 3 )                             ;
    R += " )"                                                                 ;
    return R                                                                  ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  if (term->className() == Trapezoid().className())                           {
    const Trapezoid * x = dynamic_cast<const Trapezoid *>(term)               ;
    double params[] = { x->getA() , x->getB() , x->getC() , x->getD() }       ;
    R += Operation::str( 4 , params , " , " , 3 )                             ;
    R += " )"                                                                 ;
    return R                                                                  ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  if (term->className() == Triangle().className())                            {
    const Triangle * x = dynamic_cast<const Triangle *> (term)                ;
    double params[] = { x->getA() , x->getB() , x->getC() }                   ;
    R += Operation::str( 3 , params , " , " , 3 )                             ;
    R += " )"                                                                 ;
    return R                                                                  ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  if (term->className() == ZShape().className())                              {
    const ZShape * x = dynamic_cast<const ZShape *>(term)                     ;
    double params[] = { x->getStart() , x->getEnd() }                         ;
    R += Operation::str( 2 , params , " , " , 3 )                             ;
    R += " )"                                                                 ;
    return R                                                                  ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
//    ss << "[exporter error] term of class <" << term->className() << "> not supported";
  return ""                                                                   ;
}

QString N::Fuzzy::CppExporter::toCpp(const Hedge * hedge) const
{
  nKickOut ( IsNull(hedge) , "" ) ;
  #define FHN(CN) if (hedge->name() == CN().name()) return QString("new %1()").arg(#CN)
  FHN      ( Any       ) ;
  FHN      ( Extremely ) ;
  FHN      ( Not       ) ;
  FHN      ( Seldom    ) ;
  FHN      ( Somewhat  ) ;
  FHN      ( Very      ) ;
  #undef  FHN
  return QString("new %1()").arg(hedge->name()) ;
}

QString N::Fuzzy::CppExporter::toCpp(const Operator * op) const
{
  if (IsNull(op)) return "NULL"                    ;
  return QString("new %1() ").arg(op->className()) ;
}

QString N::Fuzzy::CppExporter::toCpp(const Defuzzifier * defuzzifier) const
{
  if (IsNull(defuzzifier)) return "NULL"      ;
  return QString ( "new %1(%2)"             )
         .arg    ( defuzzifier->className() )
         .arg    ( defuzzifier->Divisions   ) ;
}
