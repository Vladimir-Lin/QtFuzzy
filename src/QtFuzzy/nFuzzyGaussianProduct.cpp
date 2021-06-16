#include <qtfuzzy.h>

N::Fuzzy::GaussianProduct:: GaussianProduct              (
                            const QString &       name   ,
                            double                meanA  ,
                            double                sigmaA ,
                            double                meanB  ,
                            double                sigmaB )
                          : Term                ( name   )
                          , _meanA              ( meanA  )
                          , _standardDeviationA ( sigmaA )
                          , _meanB              ( meanB  )
                          , _standardDeviationB ( sigmaB )
{
  addMap ( "meanA"              , &_meanA              ) ;
  addMap ( "standardDeviationA" , &_standardDeviationA ) ;
  addMap ( "meanB"              , &_meanB              ) ;
  addMap ( "standardDeviationB" , &_standardDeviationB ) ;
}

N::Fuzzy::GaussianProduct::~GaussianProduct(void)
{
}

QString N::Fuzzy::GaussianProduct::talk(void) const
{
  return QObject::tr("Gaussian Product") ;
}

QString N::Fuzzy::GaussianProduct::className(void) const
{
  return "N::Fuzzy::GaussianProduct" ;
}

N::Fuzzy::GaussianProduct * N::Fuzzy::GaussianProduct::copy(void) const
{
  return new GaussianProduct ( ME ) ;
}

double N::Fuzzy::GaussianProduct::membership(double x) const
{
  if ( Operation :: isNan ( x ) )                                  {
    return std::numeric_limits<double>::quiet_NaN()                ;
  }                                                                ;
  bool xLEa = Operation :: isLE ( x , _meanA )                     ;
  double  a = ::exp((-(x - _meanA) * (x - _meanA))                 /
                    (2 * _standardDeviationA * _standardDeviationA))
              * xLEa + (1 - xLEa)                                  ;
  bool xGEb = Operation :: isGE ( x , _meanB )                     ;
  double b  = ::exp((-(x - _meanB) * (x - _meanB))                 /
                    (2 * _standardDeviationB * _standardDeviationB))
              * xGEb + (1 - xGEb)                                  ;
  return ( a * b )                                                 ;
}

QString N::Fuzzy::GaussianProduct::toString(int precision) const
{
  QList<double> Vs = Term::values()          ;
  return Term :: toString ( precision , Vs ) ;
}

void N::Fuzzy::GaussianProduct::setMeanA(double meanA)
{
  _meanA = meanA ;
}

double N::Fuzzy::GaussianProduct::getMeanA(void) const
{
  return _meanA ;
}

void N::Fuzzy::GaussianProduct::setStandardDeviationA(double sigmaA)
{
  _standardDeviationA = sigmaA ;
}

double N::Fuzzy::GaussianProduct::getStandardDeviationA(void) const
{
  return _standardDeviationA ;
}

void N::Fuzzy::GaussianProduct::setMeanB(double meanB)
{
  _meanB = meanB ;
}

double N::Fuzzy::GaussianProduct::getMeanB(void) const
{
  return _meanB ;
}

void N::Fuzzy::GaussianProduct::setStandardDeviationB(double sigmaB)
{
  _standardDeviationB = sigmaB ;
}

double N::Fuzzy::GaussianProduct::getStandardDeviationB(void) const
{
  return _standardDeviationB ;
}
