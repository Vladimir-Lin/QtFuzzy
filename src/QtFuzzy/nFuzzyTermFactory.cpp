#include <qtfuzzy.h>

N::Fuzzy::TermFactory::TermFactory(void)
{
}

N::Fuzzy::TermFactory::~TermFactory(void)
{
}

N::Fuzzy::Term * N::Fuzzy::TermFactory::create       (
                   const QString         & className ,
                   const QVector<double> & params    ) const
{
  int requiredParams = -1;
  if (className == Discrete().className())                                {
    if ((int)params.size() % 2 == 0)                                      {
      Discrete * term = new Discrete()                                    ;
      for (int i = 0; i < (int)params.size() - 1; i += 2)                 {
        term->x.push_back(params.at(i  ))                                 ;
        term->y.push_back(params.at(i+1))                                 ;
      }                                                                   ;
      return term                                                         ;
    } else                                                                {
      return NULL                                                         ;
    }                                                                     ;
  }                                                                       ;
  /////////////////////////////////////////////////////////////////////////
  if (className == Bell().className())                                    {
    if ((int)params.size() >= (requiredParams = 3))                       {
      return new Bell("", params.at(0), params.at(1), params.at(2))       ;
    }                                                                     ;
  }                                                                       ;
  /////////////////////////////////////////////////////////////////////////
  if (className == Gaussian().className())                                {
    if ((int)params.size() >= (requiredParams = 2))                       {
      return new Gaussian("", params.at(0), params.at(1))                 ;
    }                                                                     ;
  }                                                                       ;
  /////////////////////////////////////////////////////////////////////////
  if (className == GaussianProduct().className())                         {
    if ((int)params.size() >= (requiredParams = 4))                       {
      return new GaussianProduct                                          (
                   ""                                                     ,
                   params.at(0)                                           ,
                   params.at(1)                                           ,
                   params.at(2)                                           ,
                   params.at(3)                                         ) ;
    }                                                                     ;
  }                                                                       ;
  /////////////////////////////////////////////////////////////////////////
  if (className == PiShape().className())                                 {
    if ((int)params.size() >= (requiredParams = 4))                       {
      return new PiShape                                                  (
                   ""                                                     ,
                   params.at(0)                                           ,
                   params.at(1)                                           ,
                   params.at(2)                                           ,
                   params.at(3)                                         ) ;
    }                                                                     ;
  }                                                                       ;
  /////////////////////////////////////////////////////////////////////////
  if (className == Ramp().className())                                    {
    if ((int)params.size() >= (requiredParams = 2))                       {
      return new Ramp("", params.at(0), params.at(1))                     ;
    }                                                                     ;
  }                                                                       ;
  /////////////////////////////////////////////////////////////////////////
  if (className == Rectangle().className())                               {
    if ((int)params.size() >= (requiredParams = 2))                       {
      return new Rectangle("", params.at(0), params.at(1))                ;
    }                                                                     ;
  }                                                                       ;
  /////////////////////////////////////////////////////////////////////////
  if (className == SShape().className())                                  {
    if ((int)params.size() >= (requiredParams = 2))                       {
      return new SShape("", params.at(0), params.at(1))                   ;
    }                                                                     ;
  }                                                                       ;
  /////////////////////////////////////////////////////////////////////////
  if (className == Sigmoid().className())                                 {
    if ((int)params.size() >= (requiredParams = 2))                       {
      return new Sigmoid("", params.at(0), params.at(1))                  ;
    }                                                                     ;
  }                                                                       ;
  /////////////////////////////////////////////////////////////////////////
  if (className == SigmoidDifference().className())                       {
    if ((int)params.size() >= (requiredParams = 4))                       {
      return new SigmoidDifference                                        (
                   ""                                                     ,
                   params.at(0)                                           ,
                   params.at(1)                                           ,
                   params.at(2)                                           ,
                   params.at(3)                                         ) ;
    }                                                                     ;
  }                                                                       ;
  /////////////////////////////////////////////////////////////////////////
  if (className == SigmoidProduct().className())                          {
    if ((int)params.size() >= (requiredParams = 4))                       {
      return new SigmoidProduct                                           (
                   ""                                                     ,
                   params.at(0)                                           ,
                   params.at(1)                                           ,
                   params.at(2)                                           ,
                   params.at(3)                                         ) ;
    }                                                                     ;
  }                                                                       ;
  /////////////////////////////////////////////////////////////////////////
  if (className == Trapezoid().className())                               {
    if ((int)params.size() >= (requiredParams = 4))                       {
      return new Trapezoid                                                (
                   ""                                                     ,
                   params.at(0)                                           ,
                   params.at(1)                                           ,
                   params.at(2)                                           ,
                   params.at(3)                                         ) ;
    }                                                                     ;
  }                                                                       ;
  /////////////////////////////////////////////////////////////////////////
  if (className == Triangle().className())                                {
    if ((int)params.size() >= (requiredParams = 3))                       {
      return new Triangle                                                 (
                   ""                                                     ,
                   params.at(0)                                           ,
                   params.at(1)                                           ,
                   params.at(2)                                         ) ;
    }                                                                     ;
  }                                                                       ;
  /////////////////////////////////////////////////////////////////////////
  if (className == ZShape().className())                                  {
    if ((int)params.size() >= (requiredParams = 2))                       {
      return new ZShape("", params.at(0), params.at(1))                   ;
    }                                                                     ;
  }                                                                       ;
  /////////////////////////////////////////////////////////////////////////
  if (requiredParams >= 0)                                                {
    return NULL ;
  }
  return NULL ;
}

QVector<QString> N::Fuzzy::TermFactory::available(void) const
{
  QVector<QString> result                         ;
  #define FTFC(N) result.push_back(N().className())
  FTFC ( Discrete          )                      ;
  FTFC ( Bell              )                      ;
  FTFC ( Gaussian          )                      ;
  FTFC ( GaussianProduct   )                      ;
  FTFC ( PiShape           )                      ;
  FTFC ( Ramp              )                      ;
  FTFC ( Rectangle         )                      ;
  FTFC ( SShape            )                      ;
  FTFC ( Sigmoid           )                      ;
  FTFC ( SigmoidDifference )                      ;
  FTFC ( SigmoidProduct    )                      ;
  FTFC ( Trapezoid         )                      ;
  FTFC ( Triangle          )                      ;
  FTFC ( ZShape            )                      ;
  #undef  FTFC
  return result                                   ;
}
