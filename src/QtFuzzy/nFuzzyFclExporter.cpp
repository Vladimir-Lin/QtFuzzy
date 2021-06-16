#include <qtfuzzy.h>

N::Fuzzy::FclExporter:: FclExporter (void)
                      : Exporter    (    )
{
}

N::Fuzzy::FclExporter::~FclExporter (void)
{
}

QString N::Fuzzy::FclExporter::name(void) const
{
  return "N::Fuzzy::FclExporter" ;
}

QString N::Fuzzy::FclExporter::toString(const Engine * engine) const
{
  QString R = ""                                                              ;
  /////////////////////////////////////////////////////////////////////////////
  R += QString("FUNCTION_BLOCK %1\n\n").arg(engine->getName())                ;
  R += "VAR_INPUT\n"                                                          ;
  nFullLoop ( i , engine->numberOfInputVariables() )                          {
    R += QString("%1 : REAL;\n").arg(engine->getInputVariable(i)->getName())  ;
  }                                                                           ;
  R += "END_VAR\n\n"                                                          ;
  /////////////////////////////////////////////////////////////////////////////
  R += "VAR_OUTPUT\n"                                                         ;
  nFullLoop ( i ,engine->numberOfOutputVariables() )                          {
    R += QString("%1 : REAL;\n").arg(engine->getOutputVariable(i)->getName()) ;
  }                                                                           ;
  R += "END_VAR\n\n"                                                          ;
  /////////////////////////////////////////////////////////////////////////////
  nFullLoop ( i , engine->numberOfInputVariables() )                          {
    InputVariable * inputVariable = engine->getInputVariable(i)               ;
    R += QString("FUZZIFY %1\n").arg(inputVariable->getName())                ;
    double range[] = { inputVariable->getMinimum()                            ,
                       inputVariable->getMaximum()                          } ;
    R += QString("RANGE := ( %1 );\n")
         .arg(Operation::str(2,range," .. ",3))                               ;
    nFullLoop ( t , inputVariable->numberOfTerms() )                          {
      Term * term = inputVariable->getTerm(t)                                 ;
      R += QString("%1 := %2;\n")
           .arg(term->Name)
           .arg(toFcl(term))                                                  ;
    }                                                                         ;
    R += "END_FUZZIFY\n\n"                                                    ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  nFullLoop ( i , engine->numberOfOutputVariables() )                         {
    OutputVariable * outputVariable = engine->getOutputVariable(i)            ;
    R += QString("DEFUZZIFY %1\n").arg(outputVariable->getName())             ;
    double range[] = {outputVariable->getMinimum()                            ,
                      outputVariable->getMaximum()                          } ;
    R += QString("RANGE := ( %1 );\n")
         .arg(Operation::str(2,range," .. ",3))                               ;
    nFullLoop ( t , outputVariable->numberOfTerms() )                         {
      Term * term = outputVariable->getTerm(t)                                ;
      R += QString("TERM %1 := %2;\n").arg(term->Name).arg(toFcl(term))       ;
    }                                                                         ;
    R += "\n"                                                                 ;
    R += QString("METHOD : %1;\n")
         .arg(toFcl(outputVariable->getDefuzzifier()))                        ;
    R += QString("ACCU : %1;\n")
         .arg(toFcl(outputVariable->output()->getAccumulation()))             ;
    R += QString("DEFAULT := %1")
         .arg(Operation::str(outputVariable->getDefaultValue(),3))            ;
    if (outputVariable->lockDefuzzifiedValue())                               {
      R += " | NC"                                                            ;
    }                                                                         ;
    R += ";\n"                                                                ;
    R += "END_DEFUZZIFY\n\n"                                                  ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  nFullLoop ( i , engine->numberOfRuleBlocks() )                              {
    RuleBlock * ruleblock = engine->getRuleBlock(i)                           ;
    R += QString("RULEBLOCK %1\n").arg(      ruleblock->getName      () )     ;
    R += QString("AND : %1;\n"   ).arg(toFcl(ruleblock->getTnorm     ()))     ;
    R += QString("OR : %1;\n"    ).arg(toFcl(ruleblock->getSnorm     ()))     ;
    R += QString("ACT : %1;\n"   ).arg(toFcl(ruleblock->getActivation()))     ;
    R += "\n"                                                                 ;
    nFullLoop ( r , ruleblock->numberOfRules() )                              {
      R += QString("RULE %1 : %2\n")
           .arg(r + 1)
           .arg(ruleblock->getRule(r)->getUnparsedRule())                     ;
    }                                                                         ;
    R += "END_RULEBLOCK\n\n"                                                  ;
  }                                                                           ;
  /////////////////////////////////////////////////////////////////////////////
  R += "END_FUNCTION_BLOCK\n"                                                 ;
  return R                                                                    ;
}

QString N::Fuzzy::FclExporter::toFcl(const TNorm * tnorm) const
{
  if (IsNull(tnorm)) return ""               ;
  QString name = tnorm->className()          ;
  #define FMAP(A,B) if (name == A().className()) return B
  FMAP ( Minimum           , "MIN"   ) ;
  FMAP ( AlgebraicProduct  , "PROD"  ) ;
  FMAP ( BoundedDifference , "BDIF"  ) ;
  FMAP ( DrasticProduct    , "DPROD" ) ;
  FMAP ( EinsteinProduct   , "EPROD" ) ;
  FMAP ( HamacherProduct   , "HPROD" ) ;
  #undef  FMAP
  return name                          ;
}

QString N::Fuzzy::FclExporter::toFcl(const SNorm * snorm) const
{
  if (IsNull(snorm)) return ""          ;
  QString name = snorm->className()     ;
  #define FMAP(A,B) if (name == A().className()) return B
  FMAP ( Maximum       , "MAX"  ) ;
  FMAP ( AlgebraicSum  , "ASUM" ) ;
  FMAP ( NormalizedSum , "NSUM" ) ;
  FMAP ( BoundedSum    , "BSUM" ) ;
  FMAP ( DrasticSum    , "DSUM" ) ;
  FMAP ( EinsteinSum   , "ESUM" ) ;
  FMAP ( HamacherSum   , "HSUM" ) ;
  #undef  FMAP
  return name                     ;
}

QString N::Fuzzy::FclExporter::toFcl(const Defuzzifier * defuzzifier) const
{
  if (IsNull(defuzzifier)) return "" ;
  #define FMAP(A,B) if (defuzzifier->className() == A().className()) return B
  FMAP ( Centroid          , "COG" ) ;
  FMAP ( SmallestOfMaximum , "SOM" ) ;
  FMAP ( LargestOfMaximum  , "LOM" ) ;
  FMAP ( MeanOfMaximum     , "MOM" ) ;
  #undef  FMAP
  return defuzzifier->className()    ;
}

QString N::Fuzzy::FclExporter::toFcl(const Term * term) const
{
  if (term->className() == Discrete().className())   {
    const Discrete * discrete                        =
      dynamic_cast<const Discrete *> (term)          ;
    QStringList R                                    ;
    nFullLoop ( i  , discrete->x.size() )            {
      R << QString ( "( %1 , %2 )"                   )
           .arg(Operation::str(discrete->x.at(i),3)  )
           .arg(Operation::str(discrete->y.at(i),3)) ;
    }                                                ;
    return R.join(" ")                               ;
  }                                                  ;
  return term->toString()                            ;
}
