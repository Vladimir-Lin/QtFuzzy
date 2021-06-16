#include <qtfuzzy.h>

N::Fuzzy::Accumulated:: Accumulated                       (
                        const QString & name              ,
                        double          minimum           ,
                        double          maximum           ,
                        const SNorm   * accumulation      )
                      : Term          ( name              )
                      , _minimum      ( minimum           )
                      , _maximum      ( maximum           )
                      , _accumulation ( accumulation      )
{
  addMap( "minimum" , &_minimum ) ;
  addMap( "maximum" , &_maximum ) ;
}

N::Fuzzy::Accumulated::~Accumulated(void)
{
}

QString N::Fuzzy::Accumulated::talk(void) const
{
  return QObject::tr("Accumulated") ;
}

QString N::Fuzzy::Accumulated::className(void) const
{
  return "N::Fuzzy::Accumulated" ;
}

N::Fuzzy::Accumulated * N::Fuzzy::Accumulated::copy(void) const
{
  return new Accumulated ( ME ) ;
}

double N::Fuzzy::Accumulated::membership(double x) const
{
  if ( Operation :: isNan ( x ) )                               {
    return std::numeric_limits<double>::quiet_NaN()             ;
  }                                                             ;
  double mu = 0.0                                               ;
  nFullLoop(i,_terms.size())                                    {
    mu = _accumulation->compute(mu,_terms.at(i)->membership(x)) ;
  }                                                             ;
  return mu                                                     ;
}

QString N::Fuzzy::Accumulated::toString(int precision) const
{
  QString     R                            ;
  QStringList L                            ;
  nFullLoop ( i , _terms.size() )          {
    L << _terms.at(i)->toString(precision) ;
  }                                        ;
  R = QString("%1 ( %2 ) using %3"         )
          .arg(className (     )           )
          .arg(L.join    (" , ")           )
          .arg(_accumulation->className()) ;
  return R                                 ;
}

void N::Fuzzy::Accumulated::setMinimum(double minimum)
{
  _minimum = minimum ;
}

double N::Fuzzy::Accumulated::getMinimum(void) const
{
  return _minimum ;
}

void N::Fuzzy::Accumulated::setMaximum(double maximum)
{
  _maximum = maximum ;
}

double N::Fuzzy::Accumulated::getMaximum(void) const
{
  return _maximum ;
}

void N::Fuzzy::Accumulated::setAccumulation(const SNorm * accumulation)
{
  if (_accumulation) delete _accumulation ;
  _accumulation = accumulation            ;
}

const N::Fuzzy::SNorm * N::Fuzzy::Accumulated::getAccumulation(void) const
{
  return _accumulation ;
}

void N::Fuzzy::Accumulated::addTerm(const Term * term)
{
  _terms . push_back ( term ) ;
}

const N::Fuzzy::Term * N::Fuzzy::Accumulated::removeTerm(int index)
{
  const Term * result = _terms.at(index)      ;
  _terms . erase ( _terms . begin() + index ) ;
  return result                               ;
}

void N::Fuzzy::Accumulated::clear(void)
{
  nFullLoop ( i , _terms.size() ) {
    delete _terms . at ( i )      ;
  }                               ;
  _terms . clear ( )              ;
}

const N::Fuzzy::Term * N::Fuzzy::Accumulated::getTerm(int index) const
{
  return _terms . at (index) ;
}

const QVector<const N::Fuzzy::Term *> & N::Fuzzy::Accumulated::terms(void) const
{
  return _terms ;
}

int N::Fuzzy::Accumulated::numberOfTerms(void) const
{
  return _terms . size ( ) ;
}

bool N::Fuzzy::Accumulated::isEmpty(void) const
{
  return nEqual ( _terms.size() , 0 ) ;
}
