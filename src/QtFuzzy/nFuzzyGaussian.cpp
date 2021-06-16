#include <qtfuzzy.h>

N::Fuzzy::Gaussian:: Gaussian                  (
                     const  QString & name     ,
                     double           mean     ,
                     double           sigma    )
                   : Term              ( name  )
                   , _mean             ( mean  )
                   , _standardDeviation( sigma )
{
  addMap ( "mean"              , &_mean              ) ;
  addMap ( "standardDeviation" , &_standardDeviation ) ;
}

N::Fuzzy::Gaussian::~Gaussian(void)
{
}

QString N::Fuzzy::Gaussian::talk(void) const
{
  return QObject::tr("Gaussian") ;
}

QString N::Fuzzy::Gaussian::className(void) const
{
  return "N::Fuzzy::Gaussian" ;
}

N::Fuzzy::Gaussian * N::Fuzzy::Gaussian::copy(void) const
{
  return new Gaussian(ME) ;
}

double N::Fuzzy::Gaussian::membership(double x) const
{
  if ( Operation :: isNan ( x ) )                        {
    return std::numeric_limits<double>::quiet_NaN()      ;
  }                                                      ;
  return ::exp((-(x - _mean) * (x - _mean))              /
         (2 * _standardDeviation * _standardDeviation) ) ;
}

QString N::Fuzzy::Gaussian::toString(int precision) const
{
  QList<double> Vs = Term::values()   ;
  return Term::toString(precision,Vs) ;
}

void N::Fuzzy::Gaussian::setMean(double c)
{
  _mean = c ;
}

double N::Fuzzy::Gaussian::getMean(void) const
{
  return _mean ;
}

void N::Fuzzy::Gaussian::setStandardDeviation(double sigma)
{
  _standardDeviation = sigma ;
}

double N::Fuzzy::Gaussian::getStandardDeviation(void) const
{
  return _standardDeviation ;
}
