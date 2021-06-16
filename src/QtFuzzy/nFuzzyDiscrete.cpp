#include <qtfuzzy.h>

N::Fuzzy::Discrete:: Discrete (const QString & name)
                   : Term     (                name)
{
}

N::Fuzzy::Discrete:: Discrete (const QString & name,int argc, ...)
                   : Term     (                name              )
{
  if (argc % 2 != 0) return                      ;
  va_list args                                   ;
  va_start(args, argc)                           ;
  bool xTurn = true                              ;
  for (int i = 0; i < argc; ++i)                 {
    if (xTurn)                                   {
      x.push_back((double) va_arg(args, double)) ;
      addMap(QString("x%1").arg(i),&x[i])        ;
    } else                                       {
      y.push_back((double) va_arg(args, double)) ;
      addMap(QString("y%1").arg(i),&y[i])        ;
    }                                            ;
    xTurn = !xTurn                               ;
  }                                              ;
  va_end(args)                                   ;
}

N::Fuzzy::Discrete:: Discrete                     (
                     const QString         & name ,
                     const QVector<double> & X    ,
                     const QVector<double> & Y    )
                   : Term ( name                  )
                   , x    ( X                     )
                   , y    ( Y                     )
{
  if (x.count()!=y.count())             {
    x.clear()                           ;
    y.clear()                           ;
    return                              ;
  }                                     ;
  nFullLoop( i , x.count() )            {
    addMap(QString("x%1").arg(i),&x[i]) ;
    addMap(QString("y%1").arg(i),&y[i]) ;
  }                                     ;
}

N::Fuzzy::Discrete:: Discrete                       (
                     const QString & name           ,
                     const QVector<DoublePair> & xy )
                   : Term ( name                    )
{
  nFullLoop (i,xy.size())               {
    x.push_back(xy.at(i).first )        ;
    y.push_back(xy.at(i).second)        ;
    addMap(QString("x%1").arg(i),&x[i]) ;
    addMap(QString("y%1").arg(i),&y[i]) ;
  }                                     ;
}

N::Fuzzy::Discrete::~Discrete(void)
{
}

QString N::Fuzzy::Discrete::talk(void) const
{
  return QObject::tr("Discrete") ;
}

QString N::Fuzzy::Discrete::className(void) const
{
  return "N::Fuzzy::Discrete" ;
}

N::Fuzzy::Discrete * N::Fuzzy::Discrete::copy(void) const
{
  return new Discrete ( ME ) ;
}

double N::Fuzzy::Discrete::membership(double _x_) const
{
  if ( Operation :: isNan ( _x_ ) )                 {
    return std::numeric_limits<double>::quiet_NaN() ;
  }                                                 ;
  if (x.empty() || y.empty()) return 0.0            ;
  if (NotEqual ( x.size() , y.size()) )             {
    return 0.0                                      ;
  }                                                 ;
  /*                ______________________
   *               /                      \
   *              /                        \
   * ____________/                          \____________
   *            x[0]                      x[n-1]
   */
  if ( Operation :: isLE ( _x_ , x.at(0           ))) return y.at(0           );
  if ( Operation :: isGE ( _x_ , x.at(x.size() - 1))) return y.at(y.size() - 1);
  //////////////////////////////////////////////////////////////////////////////
  int lower = -1                                              ;
  int upper = -1                                              ;
  nFullLoop (i,x.size())                                      {
    if ( Operation :: isEq ( x.at(i) , _x_ ) ) return y.at(i) ;
    //approximate on the left
    if ( Operation :: isLt ( x.at(i) , _x_ ) ) lower = i      ;
    //get the immediate next one on the right
    if ( Operation :: isGt ( x.at(i) , _x_ ) )                {
      upper = i                                               ;
      break                                                   ;
    }                                                         ;
  }                                                           ;
  /////////////////////////////////////////////////////////////
  if (upper < 0) upper = x.size() - 1                         ;
  if (lower < 0) lower = 0                                    ;
  /////////////////////////////////////////////////////////////
  return Operation :: scale   (
           _x_                ,
           x . at ( lower )   ,
           x . at ( upper )   ,
           y . at ( lower )   ,
           y . at ( upper ) ) ;
}

QString N::Fuzzy::Discrete::toString(int precision) const
{
  QString     R                                            ;
  QStringList L                                            ;
  nFullLoop ( i , x.size() )                               {
    R = QString ( "%1 %2"                                  )
        .arg    ( QString::number(x.at(i),'f',precision)   )
        .arg    ( QString::number(y.at(i),'f',precision) ) ;
    L << R                                                 ;
  }                                                        ;
  R = QString("%1 ( %2 )"                                  )
      .arg(className (     )                               )
      .arg(L.join    (" , ")                             ) ;
  return R                                                 ;
}
