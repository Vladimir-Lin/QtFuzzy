#include <qtfuzzy.h>

N::Fuzzy::Operation:: Operation (void)
{
}

N::Fuzzy::Operation::~Operation (void)
{
}

double N::Fuzzy::Operation::Min(double a, double b)
{
  return ( a < b ) ? a : b ;
}

double N::Fuzzy::Operation::Max(double a, double b)
{
  return ( a > b ) ? a : b ;
}

bool N::Fuzzy::Operation::isInf(double x)
{
  return ::abs(x) == std::numeric_limits<double>::infinity();
}

bool N::Fuzzy::Operation::isNan(double x)
{
  return ! ( x == x ) ;
}

bool N::Fuzzy::Operation::isLt(double a, double b, double tolerance)
{
  return ! isEq(a, b, tolerance) && ( a < b ) ;
}

bool N::Fuzzy::Operation::isLE(double a, double b, double tolerance)
{
  return isEq(a, b, tolerance) || ( a < b ) ;
}

bool N::Fuzzy::Operation::isEq(double a, double b, double tolerance)
{
  return ( 0 == N::Math::compare(a,b,tolerance) );
}

bool N::Fuzzy::Operation::isGt(double a, double b, double tolerance)
{
  return ! isEq(a, b, tolerance) && ( a > b ) ;
}

bool N::Fuzzy::Operation::isGE(double a, double b, double tolerance)
{
  return isEq(a, b, tolerance) || ( a > b ) ;
}

double N::Fuzzy::Operation::scale (
         double x                 ,
         double fromMin           ,
         double fromMax           ,
         double toMin             ,
         double toMax             )
{
  return ( (toMax - toMin) / (fromMax - fromMin) ) * (x - fromMin) + toMin;
}

QString N::Fuzzy::Operation::findReplace (
          const QString & str            ,
          const QString & find           ,
          const QString & replace        ,
          bool  replaceAll               )
{
  QString result                                            ;
  result = str                                              ;
  if (replaceAll)                                           {
    result = result . replace ( find , replace )            ;
  } else                                                    {
    int index = str . indexOf ( find           )            ;
    if (index>=0)                                           {
      result  = result.replace(index,find.length(),replace) ;
    }                                                       ;
  }                                                         ;
  return result ;
}

QVector<QString> N::Fuzzy::Operation::split    (
                   const QString & str         ,
                   const QString & delimiter   ,
                   bool            ignoreEmpty )
{ Q_UNUSED ( ignoreEmpty )             ;
  QVector<QString> result              ;
  if (delimiter.length()<=0)           {
    result << str                      ;
    return result                      ;
  }                                    ;
  QStringList S = str.split(delimiter) ;
  nFullLoop ( i , S.count() )          {
    result << S[i]                     ;
  }                                    ;
  return result                        ;
}

QString N::Fuzzy::Operation::leftTrim(const QString & text)
{
  int index = text.indexOf(" ") ;
  nKickOut ( index < 0 , text ) ;
  if (index != text.length())   {
    return text.mid(index)      ;
  }                             ;
  return text                   ;
}

QString N::Fuzzy::Operation::rightTrim(const QString & text)
{
  int index = text.lastIndexOf(" ") ;
  nKickOut ( index < 0 , text )     ;
  if (index!=text.length())         {
    return text.left(index + 1)     ;
  }                                 ;
  return text                       ;
}

QString N::Fuzzy::Operation::trim(const QString & text)
{
  return rightTrim(leftTrim(text)) ;
}

double N::Fuzzy::Operation::toScalar(const QString & x,bool quiet,double alternative)
{ Q_UNUSED ( quiet )                                      ;
  bool   okay   = false                                   ;
  double result = x.toDouble(&okay)                       ;
  nKickOut ( okay , result )                              ;
  /////////////////////////////////////////////////////////
  double nan  =  std::numeric_limits<double>::quiet_NaN() ;
  double pinf =  std::numeric_limits<double>::infinity () ;
  double ninf = -std::numeric_limits<double>::infinity () ;
  /////////////////////////////////////////////////////////
  QString NANX = QString::number(nan )                    ;
  QString pInf = QString::number(pinf)                    ;
  QString nInf = QString::number(ninf)                    ;
  /////////////////////////////////////////////////////////
  if (x == NANX || x ==  "nan")                           {
    return  std::numeric_limits<double>::quiet_NaN()      ;
  }                                                       ;
  if (x == pInf || x ==  "inf")                           {
    return  std::numeric_limits<double>::infinity ()      ;
  }                                                       ;
  if (x == nInf || x == "-inf")                           {
    return -std::numeric_limits<double>::infinity ()      ;
  }                                                       ;
  return alternative                                      ;
}

QString N::Fuzzy::Operation::str(int x)
{
  return QString :: number ( x ) ;
}

QString N::Fuzzy::Operation::str(double x,int precision)
{
  QString R                                   ;
  if (isNan(x)) R = "nan"                ; else
  if (isInf(x))                               {
    if (x < 0) R = "-inf"                     ;
          else R = "inf"                      ;
  } else R = QString::number(x,'f',precision) ;
  return R                                    ;
}

QString N::Fuzzy::Operation::str    (
          int             items     ,
          double        * x         ,
          const QString & separator ,
          int             precision )
{
  QStringList L              ;
  QString     S              ;
  nFullLoop(i,items)         {
    L << str(x[i],precision) ;
  }                          ;
  S = L . join ( separator ) ;
  return S                   ;
}
