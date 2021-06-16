#include <qtfuzzy.h>

N::Fuzzy::Term:: Term (QString name)
               : Name (        name)
{
}

N::Fuzzy::Term::~Term (void)
{
}

int N::Fuzzy::Term::addMap(QString name,double * value)
{
  nKickOut ( name.length() <= 0 , Paraments.count() ) ;
  nKickOut ( IsNull(value)      , Paraments.count() ) ;
  Paraments    << value                               ;
  Variables    << name                                ;
  Values[name]  = value                               ;
  return Paraments.count()                            ;
}

double N::Fuzzy::Term::value(QString name)
{
  int index = Variables.indexOf(name) ;
  nKickOut ( index < 0 , 0 )          ;
  return *(Values[name])              ;
}

double N::Fuzzy::Term::setValue(QString name,double v)
{
  int index = Variables.indexOf(name) ;
  nKickOut ( index < 0 , 0 )          ;
  *(Values[name]) = v                 ;
  return *(Values[name])              ;
}

bool N::Fuzzy::Term::is(QString name)
{
  return ( Name == name ) ;
}

QList<double> N::Fuzzy::Term::values(void) const
{
  QList<double> V                     ;
  nFullLoop ( i , Paraments.count() ) {
    V << (*(Paraments[i]))            ;
  }                                   ;
  return V                            ;
}

QString N::Fuzzy::Term::toString(int precision,QList<double> & v) const
{
  QString     R                         ;
  QStringList L                         ;
  nFullLoop ( i , v.count() )           {
    L << Operation::str(v[i],precision) ;
  }                                     ;
  R = QString("%1 ( %2 )"  )
      .arg ( Name          )
      .arg ( L.join(" , ") )            ;
  return R                              ;
}
