#include <qtfuzzy.h>

N::Fuzzy::Centroid:: Centroid    (int divisions)
                   : Defuzzifier (    divisions)
{
}

N::Fuzzy::Centroid:: Centroid    (const Centroid & centroid)
                   : Defuzzifier (centroid.Divisions       )
{
}

N::Fuzzy::Centroid::~Centroid (void)
{
}

QString N::Fuzzy::Centroid::Name(void) const
{
  return QObject::tr("Centroid defuzzifier") ;
}

QString N::Fuzzy::Centroid::className(void) const
{
  return "N::Fuzzy::Centroid" ;
}

double N::Fuzzy::Centroid::defuzzify (
         const Term * term           ,
         double       minimum        ,
         double       maximum        ) const
{
  nKickOut ( (maximum - minimum > Divisions) , 0 )      ;
  ///////////////////////////////////////////////////////
  double dx        = ( maximum - minimum ) / Divisions  ;
  double area      = 0                                  ;
  double xcentroid = 0                                  ;
  double ycentroid = 0                                  ;
  double x                                              ;
  double y                                              ;
  ///////////////////////////////////////////////////////
  nFullLoop (i,Divisions)                               {
    x = minimum + (i + 0.5) * dx                        ;
    y = term->membership(x)                             ;
    xcentroid += ( y * x )                              ;
    ycentroid += ( y * y )                              ;
    area      +=   y                                    ;
  }                                                     ;
  ///////////////////////////////////////////////////////
  xcentroid /=     area                                 ;
  ycentroid /= 2 * area                                 ;
  area      *=     dx                                   ;
  ///////////////////////////////////////////////////////
  return xcentroid                                      ;
}
