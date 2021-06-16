#include <qtfuzzy.h>

N::Fuzzy::FclImporter:: FclImporter (void)
                      : Importer    (    )
{
}

N::Fuzzy::FclImporter::~FclImporter (void)
{
}

QString N::Fuzzy::FclImporter::name(void) const
{
  return "N::Fuzzy::FclImporter" ;
}

N::Fuzzy::Engine * N::Fuzzy::FclImporter::fromString(const QString & fcl) const
{
#ifdef XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
  nFuzzy * engine = new Engine;
    engine->addHedge(new Any);
    engine->addHedge(new Extremely);
    engine->addHedge(new Not);
    engine->addHedge(new Seldom);
    engine->addHedge(new Somewhat);
    engine->addHedge(new Very);

    std::map<std::string, std::string> tags;
    tags["VAR_INPUT"] = "END_VAR";
    tags["VAR_OUTPUT"] = "END_VAR";
    tags["FUZZIFY"] = "END_FUZZIFY";
    tags["DEFUZZIFY"] = "END_DEFUZZIFY";
    tags["RULEBLOCK"] = "END_RULEBLOCK";
    std::map<std::string, std::string>::const_iterator tagFinder;

    std::string currentTag = "", closingTag = "";
    std::ostringstream block;
    std::istringstream fclReader(fcl);
    std::string line;
    int lineNumber = 0;
    try {
        while (std::getline(fclReader, line)) {
            ++lineNumber;
            line = Op::trim(line);
            if (line.empty() or line.at(0) == '#')
                continue;

            std::istringstream tokenizer(line);
            std::string firstToken;
            tokenizer >> firstToken;

            if (firstToken == "FUNCTION_BLOCK") {
                if (tokenizer.rdbuf()->in_avail() > 0) {
                    std::string name;
                    tokenizer >> name;
                    engine->setName(name);
                }
                continue;
            }
            if (firstToken == "END_FUNCTION_BLOCK") {
                break;
            }

            if (currentTag.empty()) {
                tagFinder = tags.find(firstToken);
                if (tagFinder == tags.end()) {
                    std::ostringstream ex;
                    ex << "[syntax error] unknown block definition <" << firstToken
                            << "> " << " in line " << lineNumber << ": " << line;
                    throw fl::Exception(ex.str(), FL_AT);
                }
                currentTag = tagFinder->first;
                closingTag = tagFinder->second;
                block.clear();
                block.str("");
                block << line << "\n";
                continue;
            }

            if (not currentTag.empty()) {
                if (firstToken == closingTag) {
                    processBlock(currentTag, block.str(), engine);
                    currentTag = "";
                    closingTag = "";
                } else if (tags.find(firstToken) != tags.end()) {
                    //if opening new block without closing the previous one
                    std::ostringstream ex;
                    ex << "[syntax error] expected <" << closingTag << "> before <"
                            << firstToken << "> in line: " << line;
                    throw fl::Exception(ex.str(), FL_AT);
                } else {
                    block << line << "\n";
                }
                continue;
            }
        }

        if (not currentTag.empty()) {
            std::ostringstream ex;
            ex << "[syntax error] ";
            if (block.rdbuf()->in_avail() > 0) {
                ex << "expected <" << closingTag << "> for block:\n" << block.str();
            } else {
                ex << "expected <" << closingTag << ">, but not found";
            }
            throw fl::Exception(ex.str(), FL_AT);
        }
        if (engine->numberOfInputVariables() == 0
                and engine->numberOfOutputVariables() == 0
                and (engine->numberOfRuleBlocks() == 0
                or engine->getRuleBlock(0)->numberOfRules() == 0)) {
            std::ostringstream ex;
            ex << "[importer error] the FCL code introduced produces an empty engine";
            throw fl::Exception(ex.str(), FL_AT);
        }
    } catch (fl::Exception& ex) {
        delete engine;
        throw ex;
    }
    return engine;
#endif
  return NULL ;
}

void N::Fuzzy::FclImporter::processBlock (
       const QString & tag           ,
       const QString & block         ,
       Engine        * engine        ) const
{
#ifdef XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    if (tag == "VAR_INPUT" or tag == "VAR_OUTPUT") {
        processVar(tag, block, engine);
    } else if (tag == "FUZZIFY") {
        processFuzzify(block, engine);
    } else if (tag == "DEFUZZIFY") {
        processDefuzzify(block, engine);
    } else if (tag == "RULEBLOCK") {
        processRuleBlock(block, engine);
    } else {
        std::ostringstream ex;
        ex << "[syntax error] unexpected tag <" << tag << "> for block:\n" << block;
        throw fl::Exception(ex.str(), FL_AT);
    }
#endif
}

void N::Fuzzy::FclImporter::processVar (
       const QString & tag         ,
       const QString & block       ,
       Engine        * engine      ) const
{
#ifdef XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    std::istringstream blockReader(block);
    std::string line;

    std::getline(blockReader, line); //discard first line as it is VAR_INPUT
    while (getline(blockReader, line)) {
        std::vector<std::string> token = Op::split(line, ":");
        if (token.size() != 2) {
            std::ostringstream ex;
            ex << "[syntax error] expected property of type (key : value) in line: " << line;
            throw fl::Exception(ex.str(), FL_AT);
        }
        std::string name = Op::trim(token.at(0));
        if (tag == "VAR_INPUT")
            engine->addInputVariable(new InputVariable(name));
        else if (tag == "VAR_OUTPUT")
            engine->addOutputVariable(new OutputVariable(name));
        else {
            std::ostringstream ex;
            ex << "[syntax error] unexpected tag <" << tag << "> in line: " << line;
            throw fl::Exception(ex.str(), FL_AT);
        }
    }
#endif
}

void N::Fuzzy::FclImporter::processFuzzify(const QString & block,Engine * engine) const
{
#ifdef XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    std::istringstream blockReader(block);
    std::string line;

    std::getline(blockReader, line);
    std::string name;
    std::size_t index = line.find_first_of(' ');
    if (index != std::string::npos) {
        name = line.substr(index + 1);
    } else {
        std::ostringstream ex;
        ex << "[syntax error] expected an input variable name in line: " << line;
        throw fl::Exception(ex.str(), FL_AT);
    }
    if (not engine->hasInputVariable(name)) {
        std::ostringstream ex;
        ex << "[syntax error] input variable <" << name
                << "> not registered in engine. "
                << "Line: " << line;
        throw fl::Exception(ex.str(), FL_AT);
    }

    InputVariable* inputVariable = engine->getInputVariable(name);
    while (std::getline(blockReader, line)) {
        std::istringstream ss(line);
        std::string firstToken;
        ss >> firstToken;
        try {
            if (firstToken == "RANGE") {
                scalar minimum, maximum;
                extractRange(line, minimum, maximum);
                inputVariable->setMinimum(minimum);
                inputVariable->setMaximum(maximum);
            } else if (firstToken == "TERM") {
                inputVariable->addTerm(extractTerm(line));
            } else throw fl::Exception("[syntax error] token <" + firstToken + " not recognized", FL_AT);
        } catch (fl::Exception& ex) {
            ex.append("At line: <" + line + ">");
            throw ex;
        }
    }
#endif
}

void N::Fuzzy::FclImporter::processDefuzzify(const QString & block,Engine * engine) const
{
#ifdef XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    std::istringstream blockReader(block);
    std::string line;

    std::getline(blockReader, line);
    std::string name;
    std::size_t index = line.find_first_of(' ');
    if (index != std::string::npos) {
        name = line.substr(index + 1);
    } else {
        std::ostringstream ex;
        ex << "[syntax error] expected an output variable name in line: " << line;
        throw fl::Exception(ex.str(), FL_AT);
    }
    if (not engine->hasOutputVariable(name)) {
        std::ostringstream ex;
        ex << "[syntax error] output variable <" << name
                << "> not registered in engine. "
                << "Line: " << line;
        throw fl::Exception(ex.str(), FL_AT);
    }

    OutputVariable* outputVariable = engine->getOutputVariable(name);
    while (std::getline(blockReader, line)) {
        std::string firstToken = line.substr(0, line.find_first_of(' '));
        if (firstToken == "TERM") {
            outputVariable->addTerm(extractTerm(line));
        } else if (firstToken == "METHOD") {
            outputVariable->setDefuzzifier(extractDefuzzifier(line));
        } else if (firstToken == "ACCU") {
            outputVariable->output()->setAccumulation(extractSNorm(line));
        } else if (firstToken == "DEFAULT") {
            bool lockDefuzzifiedValue;
            outputVariable->setDefaultValue(extractDefaultValue(line, lockDefuzzifiedValue));
            outputVariable->setLockDefuzzifiedValue(lockDefuzzifiedValue);
        } else if (firstToken == "RANGE") {
            scalar minimum, maximum;
            extractRange(line, minimum, maximum);
            outputVariable->setMinimum(minimum);
            outputVariable->setMaximum(maximum);
        } else {
            std::ostringstream ex;
            ex << "[syntax error] unexpected token <" << firstToken <<
                    "> in line: " << line;
            throw fl::Exception(ex.str(), FL_AT);
        }
    }
#endif
}

void N::Fuzzy::FclImporter::processRuleBlock(const QString & block,Engine * engine) const
{
#ifdef XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    std::istringstream blockReader(block);
    std::string line;

    std::string name;
    std::getline(blockReader, line);
    std::size_t index = line.find_last_of(' ');
    if (index != std::string::npos) name = line.substr(index);
    RuleBlock * ruleblock = new RuleBlock(name);
    engine->addRuleBlock(ruleblock);

    while (getline(blockReader, line)) {
        std::string firstToken = line.substr(0, line.find_first_of(' '));
        if (firstToken == "AND") {
            ruleblock->setTnorm(extractTNorm(line));
        } else if (firstToken == "OR") {
            ruleblock->setSnorm(extractSNorm(line));
        } else if (firstToken == "ACT") {
            ruleblock->setActivation(extractTNorm(line));
        } else if (firstToken == "RULE") {
            std::string rule = line.substr(line.find_first_of(':') + 1);
            rule = fl::Op::trim(rule);
            ruleblock->addRule(MamdaniRule::parse(rule, engine));
        } else {
            std::ostringstream ex;
            ex << "[syntax error] keyword <" << firstToken
                    << "> not recognized in line: " << line;
            throw fl::Exception(ex.str(), FL_AT);
        }

    }
#endif
}

N::Fuzzy::TNorm * N::Fuzzy::FclImporter::extractTNorm(const QString & line) const
{
#ifdef XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    std::vector<std::string> token = Op::split(line, ":");
    if (token.size() != 2) {
        std::ostringstream ex;
        ex << "[syntax error] expected property of type (key : value) in line: "
                << line;
        throw fl::Exception(ex.str(), FL_AT);
    }
    std::string name = Op::findReplace(Op::trim(token.at(1)), ";", "");
    std::string className = name;
    if (name == "MIN") className = Minimum().className();
    else if (name == "PROD") className = AlgebraicProduct().className();
    else if (name == "BDIF") className = BoundedDifference().className();
    else if (name == "DPROD") className = DrasticProduct().className();
    else if (name == "EPROD") className = EinsteinProduct().className();
    else if (name == "HPROD") className = HamacherProduct().className();

    try {
        return Factory::instance()->tnorm()->create(className);
    } catch (fl::Exception& ex) {
        ex.append("[syntax error] T-Norm <" + name + "> not recognized in line:\n"
                + line, FL_AT);
        throw ex;
    }
#endif
  return NULL ;
}

N::Fuzzy::SNorm * N::Fuzzy::FclImporter::extractSNorm(const QString & line) const
{
#ifdef XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    std::vector<std::string> token = Op::split(line, ":");
    if (token.size() != 2) {
        std::ostringstream ex;
        ex << "[syntax error] expected property of type (key : value) in line: "
                << line;
        throw fl::Exception(ex.str(), FL_AT);
    }
    std::string name = Op::findReplace(Op::trim(token.at(1)), ";", "");
    std::string className = name;
    if (name == "MAX") className = Maximum().className();
    else if (name == "ASUM") className = AlgebraicSum().className();
    else if (name == "BSUM") className = BoundedSum().className();
    else if (name == "NSUM") className = NormalizedSum().className();
    else if (name == "DSUM") className = DrasticSum().className();
    else if (name == "ESUM") className = EinsteinSum().className();
    else if (name == "HSUM") className = HamacherSum().className();

    try {
        return Factory::instance()->snorm()->create(className);
    } catch (fl::Exception& ex) {
        ex.append("[syntax error] S-Norm <" + name + "> not recognized in line:\n"
                + line, FL_AT);
        throw ex;
    }
#endif
  return NULL ;
}

N::Fuzzy::Term * N::Fuzzy::FclImporter::extractTerm(const QString & line) const
{
#ifdef XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    std::ostringstream spacer;
    for (std::size_t i = 0; i < line.size(); ++i) {
        if (line.at(i) == '(' or line.at(i) == ')' or line.at(i) == ',') {
            spacer << " " << line.at(i) << " ";
        } else if (line.at(i) == ':') {
            spacer << " :";
        } else if (line.at(i) == '=') {
            spacer << "= ";
        } else
            spacer << line.at(i);
    }
    std::string spacedLine = spacer.str();

    enum FSM {
        S_KWTERM, S_NAME, S_ASSIGN, S_TERMCLASS, S_PARAMETERS
    };
    FSM state = S_KWTERM;
    std::istringstream tokenizer(spacedLine);
    std::string token;
    std::string name, termClass;
    std::vector<scalar> parameters;
    while (tokenizer >> token) {
        if (state == S_KWTERM and token == "TERM") {
            state = S_NAME;
            continue;
        }
        if (state == S_NAME) {
            name = token;
            state = S_ASSIGN;
            continue;
        }
        if (state == S_ASSIGN and token == ":=") {
            state = S_TERMCLASS;
            continue;
        }
        if (state == S_TERMCLASS) {
            if (token != "(") termClass = token;
            state = S_PARAMETERS;
            continue;
        }
        if (state == S_PARAMETERS) {
            if (token == "(" or token == ")" or token == ",")
                continue;
            if (token == ";") break;
            scalar parameter;
            try {
                parameter = Op::toScalar(token);
            } catch (...) {
                std::ostringstream ex;
                ex << "[syntax error] expected numeric value, but found <"
                        << token << "> in line: " << line;
                throw fl::Exception(ex.str(), FL_AT);
            }
            parameters.push_back(parameter);
        }
    }
    if (state <= S_ASSIGN)
        throw fl::Exception("[syntax error] malformed term in line: " + line, FL_AT);
    try {
        if (termClass.empty()) termClass = Discrete().className();
        Term * result = Factory::instance()->term()->create(termClass, parameters);
        result->setName(name);
        return result;
    } catch (fl::Exception& ex) {
        ex.append(FL_AT);
        throw ex;
    }
#endif
  return NULL ;
}

N::Fuzzy::Term  * N::Fuzzy::FclImporter::createInstance (
                    const QString         & termClass   ,
                    const QString         & name        ,
                    const QVector<double> & params      ) const
{
  return NULL ;
}

N::Fuzzy::Defuzzifier * N::Fuzzy::FclImporter::extractDefuzzifier(const QString & line) const
{
#ifdef XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    std::vector<std::string> token = Op::split(line, ":");
    if (token.size() != 2) {
        std::ostringstream ex;
        ex << "[syntax error] expected property of type (key : value) in "
                << "line: " << line;
        throw fl::Exception(ex.str(), FL_AT);
    }

    std::string name = Op::trim(Op::findReplace(token.at(1), ";", ""));
    std::string className = name;
    if (name == "COG") className = Centroid().className();
    if (name == "SOM") className = SmallestOfMaximum().className();
    if (name == "LOM") className = LargestOfMaximum().className();
    if (name == "MOM") className = MeanOfMaximum().className();

    try {
        return Factory::instance()->defuzzifier()->create(className);
    } catch (fl::Exception& ex) {
        ex.append("[syntax error] defuzzifier <" + name +
                "> not recognized in line:\n" + line, FL_AT);
        throw ex;
    }
#endif
  return NULL ;
}

double N::Fuzzy::FclImporter::extractDefaultValue (
         const QString & line                 ,
         bool          & lockDefuzzifiedValue ) const
{
#ifdef XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    std::vector<std::string> token = Op::split(line, ":=");
    if (token.size() != 2) {
        std::ostringstream ex;
        ex << "[syntax error] expected property of type (key := value) in line: "
                << line;
        throw fl::Exception(ex.str(), FL_AT);
    }

    std::string defaultValue = Op::findReplace(token.at(1), " ", "");
    token = Op::split(defaultValue, "|");

    scalar value;
    try {
        value = Op::toScalar(token.at(0));
    } catch (...) {
        std::ostringstream ex;
        ex << "[syntax error] expected numeric value, "
                << "but found <" << token.at(0) << "> in line: "
                << line;
        throw fl::Exception(ex.str(), FL_AT);
    }

    lockDefuzzifiedValue = false;

    if (token.size() == 2) {
        std::string noChangeFlag = Op::findReplace(Op::trim(token.at(1)), ";", "");
        if (noChangeFlag == "NC")
            lockDefuzzifiedValue = true;
        else {
            std::ostringstream ex;
            ex << "expected keyword <NC>, but found<" << noChangeFlag << "> in "
                    << "line: " << line;
            throw fl::Exception(ex.str(), FL_AT);
        }
    }
    return value;
#endif
  return 0 ;
}

void N::Fuzzy::FclImporter::extractRange (
       const QString & line          ,
       double        & minimum       ,
       double        & maximum       ) const
{
#ifdef XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    std::vector<std::string> token = Op::split(line, ":=");
    if (token.size() != 2) {
        std::ostringstream ex;
        ex << "[syntax error] expected property of type (key := value) in line: "
                << line;
        throw fl::Exception(ex.str(), FL_AT);
    }

    std::string rangeToken = token.at(1);

    std::ostringstream range;
    for (std::size_t i = 0; i < rangeToken.size(); ++i) {
        char character = rangeToken.at(i);
        if (character == '(' or character == ')' or character == ' ' or character == ';')
            continue;
        range << character;
    }
    token = Op::split(range.str(), "..");
    if (token.size() != 2) {
        std::ostringstream ex;
        ex << "[syntax error] expected property of type 'start .. end' in line: "
                << line;
        throw fl::Exception(ex.str(), FL_AT);
    }

    try {
        minimum = Op::toScalar(token.at(0));
    } catch (...) {
        std::ostringstream ex;
        ex << "[syntax error] expected numeric value, but found <" << token.at(0) << "> in "
                << "line: " << line;
        throw fl::Exception(ex.str(), FL_AT);
    }
    try {
        maximum = Op::toScalar(token.at(1));
    } catch (...) {
        std::ostringstream ex;
        ex << "[syntax error] expected numeric value, but found <" << token.at(1) << "> in "
                << "line: " << line;
        throw fl::Exception(ex.str(), FL_AT);
    }
#endif
}
