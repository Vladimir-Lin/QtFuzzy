#include <qtfuzzy.h>

N::Fuzzy::Variable:: Variable                 (
                     const QString & name     ,
                     double          minimum  ,
                     double          maximum  )
                   : Object        ( 0 , None )
                   , _name         ( name     )
                   , _minimum      ( minimum  )
                   , _maximum      ( maximum  )
                   , Name          ( ""       )
{
}

N::Fuzzy::Variable::Variable(const Variable & copy)
{
  uuid = copy.uuid                       ;
  type = copy.type                       ;
  Name = copy.Name                       ;
  nFullLoop ( i , copy.numberOfTerms() ) {
    addTerm ( copy.getTerm(i)->copy()  ) ;
  }                                      ;
}

N::Fuzzy::Variable::~Variable(void)
{
  nFullLoop ( i , _terms . size () ) {
    delete _terms.at(i)              ;
  }                                  ;
}

void N::Fuzzy::Variable::setName(const QString & n)
{
  _name = n ;
}

QString N::Fuzzy::Variable::getName(void) const
{
  return _name ;
}

void N::Fuzzy::Variable::setRange(double minimum,double maximum)
{
  _minimum = minimum ;
  _maximum = maximum ;
}

void N::Fuzzy::Variable::setMinimum(double minimum)
{
  _minimum = minimum ;
}

double N::Fuzzy::Variable::getMinimum(void) const
{
  return _minimum ;
}

void N::Fuzzy::Variable::setMaximum(double maximum)
{
  _maximum = maximum ;
}

double N::Fuzzy::Variable::getMaximum(void) const
{
  return _maximum ;
}

QString N::Fuzzy::Variable::fuzzify(double x) const
{
  QString     R                                             ;
  QString     M                                             ;
  QStringList L                                             ;
  nFullLoop ( i , _terms.size() )                           {
    M  = Operation :: str ( _terms . at(i)->membership(x) ) ;
    R  = QString("%1 / %2").arg(M).arg(_terms.at(i)->Name ) ;
    L << R                                                  ;
  }                                                         ;
  R = ""                                                    ;
  if (L.count()>0) R = L . join (" + ")                     ;
  return R                                                  ;
}

N::Fuzzy::Term * N::Fuzzy::Variable::highestMembership(double x,double * yhighest) const
{
  Term * result = NULL                     ;
  double ymax   = 0                        ;
  nFullLoop ( i , _terms.size() )          {
    double y = _terms.at(i)->membership(x) ;
    if ( Operation :: isGt ( y , ymax ) )  {
      ymax   = y                           ;
      result = _terms.at(i)                ;
    }                                      ;
  }                                        ;
  if (yhighest) (*yhighest) = ymax         ;
  return result                            ;
}

QString N::Fuzzy::Variable::toString(void) const
{
  QString     R                   ;
  QStringList L                   ;
  nFullLoop ( i , _terms.size() ) {
    L << _terms.at(i)->toString() ;
  }                               ;
  R = QString( "%1 [ %2 ]"  )
      .arg   ( getName()    )
      .arg   ( L.join(", ") )     ;
  return R                        ;
}

void N::Fuzzy::Variable::sort(void)
{
  SortByCoG criterion                              ;
  criterion.minimum = _minimum                     ;
  criterion.maximum = _maximum                     ;
  std::sort(_terms.begin(),_terms.end(),criterion) ;
}

void N::Fuzzy::Variable::addTerm(Term * term)
{
  _terms . push_back ( term ) ;
}

void N::Fuzzy::Variable::insertTerm(Term * term,int index)
{
  _terms . insert ( index , term ) ;
}

N::Fuzzy::Term * N::Fuzzy::Variable::getTerm(int index) const
{
  return _terms . at ( index ) ;
}

N::Fuzzy::Term * N::Fuzzy::Variable::getTerm(const QString & name) const
{
  nFullLoop ( i , _terms.size() ) {
    if (_terms.at(i)->is(name))   {
      return _terms.at(i)         ;
    }                             ;
  }                               ;
  return NULL                     ;
}

bool N::Fuzzy::Variable::hasTerm(const QString & name) const
{
  return NotNull( getTerm(name) ) ;
}

N::Fuzzy::Term * N::Fuzzy::Variable::removeTerm(int index)
{
  Term   * result           ;
  result = _terms.at(index) ;
  _terms . remove   (index) ;
  return result             ;
}

int N::Fuzzy::Variable::numberOfTerms(void) const
{
  return _terms.size() ;
}

const QVector<N::Fuzzy::Term *> & N::Fuzzy::Variable::terms(void) const
{
  return _terms ;
}
