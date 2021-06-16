#include <qtfuzzy.h>

N::Fuzzy::FisImporter:: FisImporter (void)
                      : Importer    (    )
{
}

N::Fuzzy::FisImporter::~FisImporter (void)
{
}

QString N::Fuzzy::FisImporter::name(void) const
{
  return "N::Fuzzy::FisImporter" ;
}

N::Fuzzy::Engine * N::Fuzzy::FisImporter::fromString(const QString & fis) const
{
  Engine * engine = new Engine()                                             ;
  ////////////////////////////////////////////////////////////////////////////
  engine->addHedge( new Any       () )                                       ;
  engine->addHedge( new Extremely () )                                       ;
  engine->addHedge( new Not       () )                                       ;
  engine->addHedge( new Seldom    () )                                       ;
  engine->addHedge( new Somewhat  () )                                       ;
  engine->addHedge( new Very      () )                                       ;
#ifdef XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    std::istringstream fisReader(fis);
    std::string line;
    int lineNumber = 0;

    std::vector<std::string> sections;
    while (std::getline(fisReader, line)) {
        ++lineNumber;
        line = Op::trim(line);
        line = fl::Op::findReplace(line, "'", "");
        if (line.empty() or line.at(0) == '#' or line.at(0) == '%')
            continue;

        if ("[System]" == line.substr(0, std::string("[System]").size())
                or "[Input" == line.substr(0, std::string("[Input").size())
                or "[Output" == line.substr(0, std::string("[Output").size())
                or "[Rules]" == line.substr(0, std::string("[Rules]").size())) {
            sections.push_back(line);
        } else {
            if (sections.size() == 0) {
                FL_LOG("[importer warning] ignoring line because it does not "
                        "belong to any section: " << line);
            } else {
                sections.at(sections.size() - 1) += "\n" + line;
            }
        }
    }
    std::string andMethod, orMethod, impMethod, aggMethod, defuzzMethod;
    try {
        for (std::size_t i = 0; i < sections.size(); ++i) {
            if ("[System]" == sections.at(i).substr(0, std::string("[System]").size()))
                importSystem(sections.at(i), engine,
                    andMethod, orMethod, impMethod, aggMethod, defuzzMethod);
            else if ("[Input" == sections.at(i).substr(0, std::string("[Input").size()))
                importInput(sections.at(i), engine);
            else if ("[Output" == sections.at(i).substr(0, std::string("[Output").size()))
                importOutput(sections.at(i), engine);
            else if ("[Rules]" == sections.at(i).substr(0, std::string("[Rules]").size()))
                importRules(sections.at(i), engine);
            else
                throw fl::Exception("[importer error] unable to parse section: "
                    + sections.at(i), FL_AT);
        }
        if (engine->numberOfInputVariables() == 0
                and engine->numberOfOutputVariables() == 0
                and (engine->numberOfRuleBlocks() == 0
                or engine->getRuleBlock(0)->numberOfRules() == 0)) {
            std::ostringstream ex;
            ex << "[importer error] the FIS code introduced produces an empty engine";
            throw fl::Exception(ex.str(), FL_AT);
        }
        engine->configure(flTnorm(andMethod), flSnorm(orMethod),
                flTnorm(impMethod), flSnorm(aggMethod),
                flDefuzzifier(defuzzMethod));
    } catch (fl::Exception& ex) {
        delete engine;
        throw ex;
    }

#endif
  return engine                                                              ;
}

void N::Fuzzy::FisImporter::importSystem (
       const QString & section           ,
       Engine        * engine            ,
       QString       & andMethod         ,
       QString       & orMethod          ,
       QString       & impMethod         ,
       QString       & aggMethod         ,
       QString       & defuzzMethod      ) const
{
#ifdef XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    std::istringstream reader(section);
    std::string line;
    std::getline(reader, line); //ignore first line [System]
    while (std::getline(reader, line)) {
        std::vector<std::string> keyValue = fl::Op::split(line, "=");
        if (keyValue.size() != 2)
            throw fl::Exception("[syntax error] expected a property of type "
                "'key=value', but found < " + line + ">", FL_AT);
        std::string key = fl::Op::trim(keyValue.at(0));
        std::string value = fl::Op::trim(keyValue.at(1));

        if (key == "Name") engine->setName(value);
        else if (key == "Type") {
            if (value != "mamdani")
                throw fl::Exception("[importer error] fuzzylite supports only mamdani-type "
                    "engines at the moment", FL_AT);

        } else if (key == "AndMethod") andMethod = value;
        else if (key == "OrMethod") orMethod = value;
        else if (key == "ImpMethod") impMethod = value;
        else if (key == "AggMethod") aggMethod = value;
        else if (key == "DefuzzMethod") defuzzMethod = value;
        else FL_LOG("[info] ignoring redundant or non-relevant information "
                "from line: " << line);
    }
#endif
}

void N::Fuzzy::FisImporter::importInput(const QString & section,Engine * engine) const
{
#ifdef XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    std::istringstream reader(section);
    std::string line;
    std::getline(reader, line); //ignore first line [Input#]

    InputVariable* input = new InputVariable;
    engine->addInputVariable(input);

    while (std::getline(reader, line)) {
        std::vector<std::string> keyValue = fl::Op::split(line, "=");
        if (keyValue.size() != 2)
            throw fl::Exception("[syntax error] expected a property of type "
                "'key=value', but found < " + line + ">", FL_AT);
        std::string key = fl::Op::trim(keyValue.at(0));
        std::string value = fl::Op::trim(keyValue.at(1));

        if (key == "Name") input->setName(value);
        else if (key == "Range") {
            scalar minimum, maximum;
            extractRange(value, minimum, maximum);
            input->setMinimum(minimum);
            input->setMaximum(maximum);
        } else if (key.substr(0, 2) == "MF") {
            input->addTerm(extractTerm(value));
        } else {
            FL_LOG("[info] ignoring redundant or non-relevant information from line: " << line);
        }
    }
#endif
}

void N::Fuzzy::FisImporter::importOutput(const QString & section,Engine * engine) const
{
#ifdef XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    std::istringstream reader(section);
    std::string line;
    std::getline(reader, line); //ignore first line [Output#]

    OutputVariable* output = new OutputVariable;
    engine->addOutputVariable(output);


    while (std::getline(reader, line)) {
        std::vector<std::string> keyValue = fl::Op::split(line, "=");
        if (keyValue.size() != 2)
            throw fl::Exception("[syntax error] expected a property of type "
                "'key=value', but found < " + line + ">", FL_AT);
        std::string key = fl::Op::trim(keyValue.at(0));
        std::string value = fl::Op::trim(keyValue.at(1));

        if (key == "Name") output->setName(value);
        else if (key == "Range") {
            scalar minimum, maximum;
            extractRange(value, minimum, maximum);
            output->setMinimum(minimum);
            output->setMaximum(maximum);
        } else if (key.substr(0, 2) == "MF") {
            output->addTerm(extractTerm(value));
        } else if (key == "Default") {
            output->setDefaultValue(fl::Op::toScalar(value));
        } else if (key == "Lock") {
            output->setLockDefuzzifiedValue((int) fl::Op::toScalar(value) == 1);
        } else {
            FL_LOG("[info] ignoring redundant or non-relevant information from line: " << line);
        }
    }
#endif
}

void N::Fuzzy::FisImporter::importRules(const QString & section,Engine * engine) const
{
#ifdef XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    std::istringstream reader(section);
    std::string line;
    std::getline(reader, line); //ignore first line [Rules]

    RuleBlock* ruleblock = new RuleBlock;
    engine->addRuleBlock(ruleblock);

    while (std::getline(reader, line)) {
        std::vector<std::string> inputsAndRest = fl::Op::split(line, ",");
        if (inputsAndRest.size() != 2)
            throw fl::Exception("[syntax error] expected rule to match pattern "
                "<'i '+, 'o '+ (w) : '1|2'>, but found instead <" + line + ">", FL_AT);

        std::vector <std::string> outputsAndRest = fl::Op::split(inputsAndRest.at(1), ":");
        if (outputsAndRest.size() != 2)
            throw fl::Exception("[syntax error] expected rule to match pattern "
                "<'i '+, 'o '+ (w) : '1|2'>, but found instead <" + line + ">", FL_AT);

        std::vector<std::string> inputs = fl::Op::split(inputsAndRest.at(0), " ");
        std::vector<std::string> outputs = fl::Op::split(outputsAndRest.at(0), " ");
        std::string weightInParenthesis = outputs.at(outputs.size() - 1);
        outputs.erase(outputs.begin() + outputs.size() - 1);
        std::string connector = fl::Op::trim(outputsAndRest.at(1));

        if ((int) inputs.size() != engine->numberOfInputVariables())
            throw fl::Exception("[syntax error] missing input variables in rule <"
                + line + ">", FL_AT);

        if ((int) outputs.size() != engine->numberOfOutputVariables())
            throw fl::Exception("[syntax error] missing output variables in rule <"
                + line + ">", FL_AT);

        std::vector<std::string> antecedent, consequent;

        for (std::size_t i = 0; i < inputs.size(); ++i) {
            std::ostringstream ss;
            scalar inputCode = fl::Op::toScalar(inputs.at(i));
            if (fl::Op::isEq(inputCode, 0.0)) continue;
            ss << engine->getInputVariable(i)->getName() << " "
                    << fl::Rule::FL_IS << " "
                    << translateProposition(inputCode, engine->getInputVariable(i));
            antecedent.push_back(ss.str());
        }

        for (std::size_t i = 0; i < outputs.size(); ++i) {
            std::ostringstream ss;
            scalar outputCode = fl::Op::toScalar(outputs.at(i));
            if (fl::Op::isEq(outputCode, 0.0)) continue;
            ss << engine->getOutputVariable(i)->getName() << " "
                    << fl::Rule::FL_IS << " "
                    << translateProposition(outputCode, engine->getOutputVariable(i));
            consequent.push_back(ss.str());
        }

        std::ostringstream rule;

        rule << fl::Rule::FL_IF << " ";
        for (std::size_t i = 0; i < antecedent.size(); ++i) {
            rule << antecedent.at(i);
            if (i < antecedent.size() - 1) {
                rule << " ";
                if (connector == "1") rule << fl::Rule::FL_AND << " ";
                else if (connector == "2") rule << fl::Rule::FL_OR << " ";
                else throw fl::Exception("[syntax error] connector <"
                        + connector + "> not recognized", FL_AT);
            }
        }

        rule << " " << fl::Rule::FL_THEN << " ";
        for (std::size_t i = 0; i < consequent.size(); ++i) {
            rule << consequent.at(i);
            if (i < consequent.size() - 1) {
                rule << " " << fl::Rule::FL_AND << " ";
            }
        }

        std::ostringstream ss;
        for (std::size_t i = 0; i < weightInParenthesis.size(); ++i) {
            if (weightInParenthesis.at(i) == '('
                    or weightInParenthesis.at(i) == ')'
                    or weightInParenthesis.at(i) == ' ') continue;
            ss << weightInParenthesis.at(i);
        }

        scalar weight = fl::Op::toScalar(ss.str());
        if (not fl::Op::isEq(weight, 1.0))
            rule << " " << fl::Rule::FL_WITH << " " << weight;

        ruleblock->addRule(fl::MamdaniRule::parse(rule.str(), engine));
    }
#endif
}

QString N::Fuzzy::FisImporter::translateProposition(double code,Variable * variable) const
{
#ifdef XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    scalar intPartScalar;
    scalar fracPart = std::abs(std::modf(code, &intPartScalar));
    int intPart = (int) std::abs(intPartScalar) - 1;

    if (intPart < 0 or intPart >= variable->numberOfTerms()) {
        std::ostringstream ex;
        ex << "[syntax error] the code <" << code << "> refers to a term "
                "out of range from variable <" << variable->toString() << ">";
        throw fl::Exception(ex.str(), FL_AT);
    }

    std::ostringstream ss;
    if (code < 0) ss << Not().name() << " ";
    if (fl::Op::isEq(fracPart, 0.05)) ss << Somewhat().name() << " ";
    else if (fl::Op::isEq(fracPart, 0.2)) ss << Very().name() << " ";
    else if (fl::Op::isEq(fracPart, 0.3)) ss << Extremely().name() << " ";
    else if (fl::Op::isEq(fracPart, 0.4)) ss << Very().name() << " " << Very().name() << " ";
    else if (not fl::Op::isEq(fracPart, 0))
        throw fl::Exception("[syntax error] no hedge defined in FIS format for <"
            + fl::Op::str(fracPart) + ">", FL_AT);

    ss << variable->getTerm(intPart)->getName();
    return ss.str();
#endif
  return "" ;
}

QString N::Fuzzy::FisImporter::flTnorm(const QString & name) const
{
  QString className = name                             ;
  #define UR(N,C) if (name == N) className = C () . className()
  UR( "min"                , Minimum           ) ; else
  UR( "prod"               , AlgebraicProduct  ) ; else
  UR( "bounded_difference" , BoundedDifference ) ; else
  UR( "drastic_product"    , DrasticProduct    ) ; else
  UR( "einstein_product"   , EinsteinProduct   ) ; else
  UR( "hamacher_product"   , HamacherProduct   ) ;
  #undef  UR
  return className                                     ;
}

QString N::Fuzzy::FisImporter::flSnorm(const QString & name) const
{
  QString className = name                     ;
  #define UR(N,C) if (name == N) className = C () . className()
  UR( "max"            , Maximum       ) ; else
  UR( "sum"            , AlgebraicSum  ) ; else
  UR( "probor"         , AlgebraicSum  ) ; else
  UR( "bounded_sum"    , BoundedSum    ) ; else
  UR( "normalized_sum" , NormalizedSum ) ; else
  UR( "drastic_sum"    , DrasticSum    ) ; else
  UR( "einstein_sum"   , EinsteinSum   ) ; else
  UR( "hamacher_sum"   , HamacherSum   ) ;
  #undef  UR
  return className                             ;
}

QString N::Fuzzy::FisImporter::flDefuzzifier(const QString & name) const
{
  QString className = name                   ;
  #define UR(N,C) if (name == N) className = C () . className()
  UR( "centroid" , Centroid          ) ; else
  UR( "som"      , SmallestOfMaximum ) ; else
  UR( "lom"      , LargestOfMaximum  ) ; else
  UR( "mom"      , MeanOfMaximum     ) ;
  #undef  UR
  return className                           ;
}

N::Fuzzy::Term * N::Fuzzy::FisImporter::extractTerm(const QString & fis) const
{
#ifdef XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    std::ostringstream ss;
    for (std::size_t i = 0; i < fis.size(); ++i) {
        if (not (fis.at(i) == '[' or fis.at(i) == ']')) {
            ss << fis.at(i);
        }
    }
    std::string line = ss.str();

    std::vector<std::string> nameTerm = fl::Op::split(line, ":");
    if (nameTerm.size() != 2) {
        throw fl::Exception("[syntax error] expected term in format 'name':'class',[params], "
                "but found " + line, FL_AT);
    }
    std::vector<std::string> termParams = fl::Op::split(nameTerm.at(1), ",");
    if (termParams.size() != 2) {
        throw fl::Exception("[syntax error] expected term in format 'name':'class',[params], "
                "but found " + line, FL_AT);
    }

    std::vector<std::string> strParams = fl::Op::split(termParams.at(1), " ");
    std::vector<scalar> params;
    for (std::size_t i = 0; i < strParams.size(); ++i) {
        params.push_back(fl::Op::toScalar(strParams.at(i)));
    }

    return createInstance(termParams.at(0), nameTerm.at(0), params);
#endif
  return NULL ;
}

N::Fuzzy::Term * N::Fuzzy::FisImporter::createInstance (
                    const QString         & mClass     ,
                    const QString         & name       ,
                    const QVector<double> & params     ) const
{
  QMap<QString,QString> Mappings                                       ;
  Mappings [ "discretemf" ] = Discrete          () . className()       ;
  Mappings [ "gbellmf"    ] = Bell              () . className()       ;
  Mappings [ "gaussmf"    ] = Gaussian          () . className()       ;
  Mappings [ "gauss2mf"   ] = GaussianProduct   () . className()       ;
  Mappings [ "pimf"       ] = PiShape           () . className()       ;
  Mappings [ "rampmf"     ] = Ramp              () . className()       ;
  Mappings [ "rectmf"     ] = Rectangle         () . className()       ;
  Mappings [ "smf"        ] = SShape            () . className()       ;
  Mappings [ "sigmf"      ] = Sigmoid           () . className()       ;
  Mappings [ "dsigmf"     ] = SigmoidDifference () . className()       ;
  Mappings [ "psigmf"     ] = SigmoidProduct    () . className()       ;
  Mappings [ "trapmf"     ] = Trapezoid         () . className()       ;
  Mappings [ "trimf"      ] = Triangle          () . className()       ;
  Mappings [ "zmf"        ] = ZShape            () . className()       ;
  //////////////////////////////////////////////////////////////////////
  QVector<double> sortedParams = params                                ;
  if (mClass == "gbellmf"  && params.size() >= 3)                      {
    sortedParams[0] = params[2]                                        ;
    sortedParams[1] = params[0]                                        ;
    sortedParams[2] = params[1]                                        ;
  } else
  if (mClass == "gaussmf"  && params.size() >= 2)                      {
    sortedParams[0] = params[1]                                        ;
    sortedParams[1] = params[0]                                        ;
  } else
  if (mClass == "gauss2mf" && params.size() >= 4)                      {
    sortedParams[0] = params[1]                                        ;
    sortedParams[1] = params[0]                                        ;
    sortedParams[2] = params[3]                                        ;
    sortedParams[3] = params[2]                                        ;
  } else
  if (mClass == "sigmf"    && params.size() >= 2)                      {
    sortedParams[0] = params[1]                                        ;
    sortedParams[1] = params[0]                                        ;
  } else
  if (mClass == "dsigmf"   && params.size() >= 4)                      {
    sortedParams[0] = params[1]                                        ;
    sortedParams[1] = params[0]                                        ;
    sortedParams[2] = params[2]                                        ;
    sortedParams[3] = params[3]                                        ;
  } else
  if (mClass == "psigmf"   && params.size() >= 4)                      {
    sortedParams[0] = params[1]                                        ;
    sortedParams[1] = params[0]                                        ;
    sortedParams[2] = params[2]                                        ;
    sortedParams[3] = params[3]                                        ;
  }                                                                    ;
  //////////////////////////////////////////////////////////////////////
  QString flClass = mClass                                             ;
  if (Mappings.contains(mClass)) flClass = Mappings[mClass]            ;
  //////////////////////////////////////////////////////////////////////
  Term * result = Factory::instance()->term()->create(flClass,sortedParams) ;
  result->Name = name                                                  ;
  return result                                                        ;
}

void N::Fuzzy::FisImporter::extractRange (
       const QString & range             ,
       double        & minimum           ,
       double        & maximum           ) const
{
  QString     R     = range               ;
  QStringList parts                       ;
  R     = R.replace("[","")               ;
  R     = R.replace("]","")               ;
  parts = R.split  (' '   )               ;
  nDropOut ( parts.count() != 2 )         ;
  /////////////////////////////////////////
  minimum = Operation::toScalar(parts[0]) ;
  maximum = Operation::toScalar(parts[1]) ;
}
