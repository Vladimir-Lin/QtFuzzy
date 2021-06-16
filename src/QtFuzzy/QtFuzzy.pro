NAME         = QtFuzzy
TARGET       = $${NAME}

QT           = core
QT          -= gui
QT          += network
QT          += sql
QT          += script
QT          += QtCUDA
QT          += Essentials
QT          += QtGMP
QT          += QtGSL
QT          += QtAlgebra
QT          += QtDiscrete
QT          += QtFFT
QT          += QtDAI
QT          += Mathematics

load(qt_build_config)
load(qt_module)

INCLUDEPATH += $${PWD}/../../include/$${NAME}

HEADERS     += $${PWD}/../../include/$${NAME}/qtfuzzy.h

SOURCES     += $${PWD}/nFuzzyOperation.cpp
SOURCES     += $${PWD}/nFuzzyTerm.cpp
SOURCES     += $${PWD}/nFuzzyOperator.cpp
SOURCES     += $${PWD}/nFuzzySNorm.cpp
SOURCES     += $${PWD}/nFuzzyTNorm.cpp
SOURCES     += $${PWD}/nFuzzyAntecedent.cpp
SOURCES     += $${PWD}/nFuzzyConsequent.cpp
SOURCES     += $${PWD}/nDefuzzifier.cpp
SOURCES     += $${PWD}/nFuzzyHedge.cpp
SOURCES     += $${PWD}/nFuzzyMaximum.cpp
SOURCES     += $${PWD}/nFuzzyAlgebraicSum.cpp
SOURCES     += $${PWD}/nFuzzyBoundedSum.cpp
SOURCES     += $${PWD}/nFuzzyNormalizedSum.cpp
SOURCES     += $${PWD}/nFuzzyDrasticSum.cpp
SOURCES     += $${PWD}/nFuzzyEinsteinSum.cpp
SOURCES     += $${PWD}/nFuzzyHamacherSum.cpp
SOURCES     += $${PWD}/nFuzzyMinimum.cpp
SOURCES     += $${PWD}/nFuzzyAlgebraicProduct.cpp
SOURCES     += $${PWD}/nFuzzyBoundedDifference.cpp
SOURCES     += $${PWD}/nFuzzyDrasticProduct.cpp
SOURCES     += $${PWD}/nFuzzyEinsteinProduct.cpp
SOURCES     += $${PWD}/nFuzzyHamacherProduct.cpp
SOURCES     += $${PWD}/nFuzzyAny.cpp
SOURCES     += $${PWD}/nFuzzyExtremely.cpp
SOURCES     += $${PWD}/nFuzzyNot.cpp
SOURCES     += $${PWD}/nFuzzySeldom.cpp
SOURCES     += $${PWD}/nFuzzySomewhat.cpp
SOURCES     += $${PWD}/nFuzzyVery.cpp
SOURCES     += $${PWD}/nFuzzyAccumulated.cpp
SOURCES     += $${PWD}/nFuzzyBell.cpp
SOURCES     += $${PWD}/nFuzzyDiscrete.cpp
SOURCES     += $${PWD}/nFuzzyGaussian.cpp
SOURCES     += $${PWD}/nFuzzyGaussianProduct.cpp
SOURCES     += $${PWD}/nFuzzyPiShape.cpp
SOURCES     += $${PWD}/nFuzzyRamp.cpp
SOURCES     += $${PWD}/nFuzzyRectangle.cpp
SOURCES     += $${PWD}/nFuzzySShape.cpp
SOURCES     += $${PWD}/nFuzzySigmoid.cpp
SOURCES     += $${PWD}/nFuzzySigmoidDifference.cpp
SOURCES     += $${PWD}/nFuzzySigmoidProduct.cpp
SOURCES     += $${PWD}/nFuzzyThresholded.cpp
SOURCES     += $${PWD}/nFuzzyTrapezoid.cpp
SOURCES     += $${PWD}/nFuzzyTriangle.cpp
SOURCES     += $${PWD}/nFuzzyZShape.cpp
SOURCES     += $${PWD}/nFuzzyCentroid.cpp
SOURCES     += $${PWD}/nMaximumDefuzzifier.cpp
SOURCES     += $${PWD}/nMeanOfMaximumDefuzzifier.cpp
SOURCES     += $${PWD}/nLargestOfMaximumDefuzzifier.cpp
SOURCES     += $${PWD}/nSmallestOfMaximumDefuzzifier.cpp
SOURCES     += $${PWD}/nFuzzyVariable.cpp
SOURCES     += $${PWD}/nFuzzyInputVariable.cpp
SOURCES     += $${PWD}/nFuzzyOutputVariable.cpp
SOURCES     += $${PWD}/nFuzzyGenericOperator.cpp
SOURCES     += $${PWD}/nFuzzyGenericFunction.cpp
SOURCES     += $${PWD}/nFuzzyInfix.cpp
SOURCES     += $${PWD}/nFuzzyRule.cpp
SOURCES     += $${PWD}/nFuzzyRuleBlock.cpp
SOURCES     += $${PWD}/nFuzzyTermFactory.cpp
SOURCES     += $${PWD}/nFuzzyHedgeFactory.cpp
SOURCES     += $${PWD}/nFuzzySNormFactory.cpp
SOURCES     += $${PWD}/nFuzzyTNormFactory.cpp
SOURCES     += $${PWD}/nDefuzzifierFactory.cpp
SOURCES     += $${PWD}/nFuzzyFactory.cpp
SOURCES     += $${PWD}/nFuzzy.cpp
SOURCES     += $${PWD}/nFuzzyMamdaniExpression.cpp
SOURCES     += $${PWD}/nFuzzyMamdaniProposition.cpp
SOURCES     += $${PWD}/nFuzzyMamdaniOperator.cpp
SOURCES     += $${PWD}/nFuzzyMamdaniAntecedent.cpp
SOURCES     += $${PWD}/nFuzzyMamdaniConsequent.cpp
SOURCES     += $${PWD}/nFuzzyMamdaniRule.cpp
SOURCES     += $${PWD}/nFuzzyImporter.cpp
SOURCES     += $${PWD}/nFuzzyExporter.cpp
SOURCES     += $${PWD}/nFuzzyCppExporter.cpp
SOURCES     += $${PWD}/nFuzzyFclImporter.cpp
SOURCES     += $${PWD}/nFuzzyFclExporter.cpp
SOURCES     += $${PWD}/nFuzzyFisImporter.cpp
SOURCES     += $${PWD}/nFuzzyFisExporter.cpp

OTHER_FILES += $${PWD}/../../include/$${NAME}/headers.pri

include ($${PWD}/../../doc/Qt/Qt.pri)

TRNAME       = $${NAME}
include ($${PWD}/../../Translations.pri)
