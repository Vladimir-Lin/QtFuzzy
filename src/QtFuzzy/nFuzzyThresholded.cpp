#include <qtfuzzy.h>

N::Fuzzy::Thresholded:: Thresholded              (
                        const Term  * term       ,
                        double        threshold  ,
                        const TNorm * activation )
                      : Term        ( ""         )
                      , _term       ( term       )
                      , _threshold  ( threshold  )
                      , _activation ( activation )
{
  if (NotNull(term)) Name = term->Name ;
  addMap ( "threshold" , &_threshold ) ;
}

N::Fuzzy::Thresholded::~Thresholded(void)
{
}

QString N::Fuzzy::Thresholded::talk(void) const
{
  return QObject::tr("Thresholded") ;
}

QString N::Fuzzy::Thresholded::className(void) const
{
  return "N::Fuzzy::Thresholded" ;
}

N::Fuzzy::Thresholded * N::Fuzzy::Thresholded::copy(void) const
{
  return new Thresholded ( ME ) ;
}

double N::Fuzzy::Thresholded::membership(double x) const
{
  if ( Operation :: isNan ( x ) )                              {
    return std::numeric_limits<double>::quiet_NaN()            ;
  }                                                            ;
  return _activation->compute(_term->membership(x),_threshold) ;
}

QString N::Fuzzy::Thresholded::toString(int precision) const
{
  QString R                                                        ;
  R = QString("%1 ( %2 ) thresholded to %3 using < %4 > activation")
          .arg(className              (                           ))
          .arg(_term->toString        (                           ))
          .arg(QString::number        ( _threshold,'f',precision  ))
          .arg(_activation->className (                         )) ;
  return R                                                         ;
}

void N::Fuzzy::Thresholded::setTerm(const Term * term)
{
  _term = term ;
}

const N::Fuzzy::Term * N::Fuzzy::Thresholded::getTerm(void) const
{
  return _term ;
}

void N::Fuzzy::Thresholded::setThreshold(double threshold)
{
   _threshold = threshold ;
}

double N::Fuzzy::Thresholded::getThreshold(void) const
{
  return _threshold ;
}

void N::Fuzzy::Thresholded::setActivation(const TNorm * activation)
{
  _activation = activation ;
}

const N::Fuzzy::TNorm * N::Fuzzy::Thresholded::getActivation(void) const
{
  return _activation ;
}
