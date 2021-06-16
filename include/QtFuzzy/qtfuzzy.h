/****************************************************************************
 *                                                                          *
 * Copyright (C) 2001 ~ 2016 Neutrino International Inc.                    *
 *                                                                          *
 * Author : Brian Lin <lin.foxman@gmail.com>, Skype: wolfram_lin            *
 *                                                                          *
 ****************************************************************************/

#ifndef QT_FUZZY_H
#define QT_FUZZY_H

#include <QtCore>

#ifdef QT_QTCUDA_LIB
#include <QtCUDA>
#endif

#ifdef QT_ESSENTIALS_LIB
#include <Essentials>
#endif

#ifdef QT_QTGMP_LIB
#include <QtGMP>
#endif

#ifdef QT_QTGSL_LIB
#include <QtGSL>
#endif

#ifdef QT_QTALGEBRA_LIB
#include <QtAlgebra>
#endif

#ifdef QT_QTDISCRETE_LIB
#include <QtDiscrete>
#endif

#ifdef QT_QTFFT_LIB
#include <QtFFT>
#endif

#ifdef QT_QTDAI_LIB
#include <QtDAI>
#endif

#ifdef QT_MATHEMATICS_LIB
#include <Mathematics>
#endif

QT_BEGIN_NAMESPACE

#ifndef QT_STATIC
#    if defined(QT_BUILD_QTFUZZY_LIB)
#      define Q_FUZZY_EXPORT Q_DECL_EXPORT
#    else
#      define Q_FUZZY_EXPORT Q_DECL_IMPORT
#    endif
#else
#      define Q_FUZZY_EXPORT
#endif

namespace N                                 {
namespace Fuzzy                             {

class Q_FUZZY_EXPORT Operation              ;
class Q_FUZZY_EXPORT Term                   ;
class Q_FUZZY_EXPORT Operator               ;
class Q_FUZZY_EXPORT SNorm                  ;
class Q_FUZZY_EXPORT TNorm                  ;
class Q_FUZZY_EXPORT Antecedent             ;
class Q_FUZZY_EXPORT Consequent             ;
class Q_FUZZY_EXPORT Defuzzifier            ;
class Q_FUZZY_EXPORT Hedge                  ;
class Q_FUZZY_EXPORT Maximum                ;
class Q_FUZZY_EXPORT AlgebraicSum           ;
class Q_FUZZY_EXPORT BoundedSum             ;
class Q_FUZZY_EXPORT NormalizedSum          ;
class Q_FUZZY_EXPORT DrasticSum             ;
class Q_FUZZY_EXPORT EinsteinSum            ;
class Q_FUZZY_EXPORT HamacherSum            ;
class Q_FUZZY_EXPORT Minimum                ;
class Q_FUZZY_EXPORT AlgebraicProduct       ;
class Q_FUZZY_EXPORT BoundedDifference      ;
class Q_FUZZY_EXPORT DrasticProduct         ;
class Q_FUZZY_EXPORT EinsteinProduct        ;
class Q_FUZZY_EXPORT HamacherProduct        ;
class Q_FUZZY_EXPORT Any                    ;
class Q_FUZZY_EXPORT Extremely              ;
class Q_FUZZY_EXPORT Not                    ;
class Q_FUZZY_EXPORT Seldom                 ;
class Q_FUZZY_EXPORT Somewhat               ;
class Q_FUZZY_EXPORT Very                   ;
class Q_FUZZY_EXPORT Accumulated            ;
class Q_FUZZY_EXPORT Bell                   ;
class Q_FUZZY_EXPORT Discrete               ;
class Q_FUZZY_EXPORT Gaussian               ;
class Q_FUZZY_EXPORT GaussianProduct        ;
class Q_FUZZY_EXPORT PiShape                ;
class Q_FUZZY_EXPORT Ramp                   ;
class Q_FUZZY_EXPORT Rectangle              ;
class Q_FUZZY_EXPORT SShape                 ;
class Q_FUZZY_EXPORT Sigmoid                ;
class Q_FUZZY_EXPORT SigmoidDifference      ;
class Q_FUZZY_EXPORT SigmoidProduct         ;
class Q_FUZZY_EXPORT Thresholded            ;
class Q_FUZZY_EXPORT Trapezoid              ;
class Q_FUZZY_EXPORT Triangle               ;
class Q_FUZZY_EXPORT ZShape                 ;
class Q_FUZZY_EXPORT Centroid               ;
class Q_FUZZY_EXPORT MaximumDefuzzifier     ;
class Q_FUZZY_EXPORT MeanOfMaximum          ;
class Q_FUZZY_EXPORT SmallestOfMaximum      ;
class Q_FUZZY_EXPORT LargestOfMaximum       ;
class Q_FUZZY_EXPORT Variable               ;
class Q_FUZZY_EXPORT InputVariable          ;
class Q_FUZZY_EXPORT OutputVariable         ;
class Q_FUZZY_EXPORT GenericOperator        ;
class Q_FUZZY_EXPORT GenericFunction        ;
class Q_FUZZY_EXPORT Infix                  ;
class Q_FUZZY_EXPORT Rule                   ;
class Q_FUZZY_EXPORT RuleBlock              ;

class Q_FUZZY_EXPORT TermFactory            ;
class Q_FUZZY_EXPORT HedgeFactory           ;
class Q_FUZZY_EXPORT SNormFactory           ;
class Q_FUZZY_EXPORT TNormFactory           ;
class Q_FUZZY_EXPORT DefuzzifierFactory     ;
class Q_FUZZY_EXPORT Factory                ;
class Q_FUZZY_EXPORT Engine                 ;

class Q_FUZZY_EXPORT MamdaniExpression      ;
class Q_FUZZY_EXPORT MamdaniProposition     ;
class Q_FUZZY_EXPORT MamdaniOperator        ;
class Q_FUZZY_EXPORT MamdaniAntecedent      ;
class Q_FUZZY_EXPORT MamdaniConsequent      ;
class Q_FUZZY_EXPORT MamdaniRule            ;

class Q_FUZZY_EXPORT Importer               ;
class Q_FUZZY_EXPORT Exporter               ;
class Q_FUZZY_EXPORT CppExporter            ;
class Q_FUZZY_EXPORT FclImporter            ;
class Q_FUZZY_EXPORT FclExporter            ;
class Q_FUZZY_EXPORT FisImporter            ;
class Q_FUZZY_EXPORT FisExporter            ;

/*****************************************************************************
 *                                                                           *
 *                                 Vague system                              *
 *                                                                           *
 *****************************************************************************/

/*****************************************************************************
 *                                                                           *
 *                  Fuzzy logic control and inference system                 *
 *                                                                           *
 *****************************************************************************/

#define FUZZY_FLOAT_TOLERANCE 0.00001

class Q_FUZZY_EXPORT Operation
{
  public:

    explicit Operation  (void) ;
    virtual ~Operation  (void) ;

    static double Min   (double a, double b) ;
    static double Max   (double a, double b) ;
    static bool   isInf (double x) ;
    static bool   isNan (double x) ;
    static bool   isLt  (double a, double b, double tolerance = FUZZY_FLOAT_TOLERANCE) ;
    static bool   isLE  (double a, double b, double tolerance = FUZZY_FLOAT_TOLERANCE) ;
    static bool   isEq  (double a, double b, double tolerance = FUZZY_FLOAT_TOLERANCE) ;
    static bool   isGt  (double a, double b, double tolerance = FUZZY_FLOAT_TOLERANCE) ;
    static bool   isGE  (double a, double b, double tolerance = FUZZY_FLOAT_TOLERANCE) ;
    static double scale (double x, double fromMin, double fromMax, double toMin, double toMax) ;

    static QString leftTrim  (const QString & text) ;
    static QString rightTrim (const QString & text) ;
    static QString trim      (const QString & text) ;

    static QString findReplace               (
                     const QString & str     ,
                     const QString & find    ,
                     const QString & replace ,
                     bool replaceAll = true
                   )                         ;

    static QVector<QString> split                        (
                         const QString & str             ,
                         const QString & delimiter = " " ,
                         bool ignoreEmpty = true
                       )                                 ;

    static double toScalar               (
                    const  QString& x    ,
                    bool   quiet = false ,
                    double alternative = std::numeric_limits<double>::quiet_NaN()
                  )                      ;

    static QString str(int x) ;
    static QString str(double x, int precision = 3) ;

    static QString str                               (
                     int             items           ,
                     double        * x               ,
                     const QString & separator = "," ,
                     int             precision = 3 ) ;

    template <typename T>
    static QString str                                (
                     QVector<T>    & x                ,
                     const QString & separator = ", " ,
                     int             precision = 3    )
    {
      QString ss                                             ;
      for (int i = 0; i < x.size(); ++i)                     {
          ss << N::Fuzzy::Operation::str(x.at(i), precision) ;
          if (i < x.size() - 1) ss += separator              ;
      }                                                      ;
      return ss                                              ;
    }

};

// Linguistic terms or Fuzzy partitions
class Q_FUZZY_EXPORT Term
{
  public:

    QString                Name      ;
    QList<double        *> Paraments ;
    QStringList            Variables ;
    QMap<QString,double *> Values    ;

    explicit        Term       (QString name = "") ;
    virtual        ~Term       (void) ;

    virtual double  membership (double x         ) const = 0 ;
    virtual QString talk       (void             ) const = 0 ;
    virtual QString className  (void             ) const = 0 ;
    virtual QString toString   (int precision = 3) const = 0 ;
    virtual Term *  copy       (void             ) const = 0 ;

    bool            is         (QString name) ;
    QList<double>   values     (void) const ;
    QString         toString   (int precision,QList<double> & v) const ;

    double          value      (QString name) ;
    double          setValue   (QString name,double value) ;
    int             addMap     (QString name,double * value) ;

  protected:

  private:

};

// Fuzzy operators
class Q_FUZZY_EXPORT Operator
{
  public:

    explicit        Operator  (void) ;
    virtual        ~Operator  (void) ;

    virtual int     typeId    (void) const = 0 ;
    virtual QString className (void) const = 0 ;
    virtual double  compute   (double a,double b) const = 0 ;

  protected:

  private:

};

class Q_FUZZY_EXPORT SNorm : public Operator
{
  public:

    explicit SNorm (void) ;
    virtual ~SNorm (void) ;

  protected:

  private:

};

class Q_FUZZY_EXPORT TNorm : public Operator
{
  public:

    explicit TNorm (void) ;
    virtual ~TNorm (void) ;

  protected:

  private:

};

class Q_FUZZY_EXPORT Antecedent
{
  public:

    explicit        Antecedent     (void) ;
    virtual        ~Antecedent     (void) ;

    virtual double  firingStrength (const TNorm * tnorm,const SNorm * snorm) const = 0 ;
    virtual QString toString       (void) const = 0 ;

  protected:

  private:

};

class Q_FUZZY_EXPORT Consequent
{
  public:

    explicit        Consequent (void) ;
    virtual        ~Consequent (void) ;

    virtual void    fire       (double strength,const TNorm * activation) = 0 ;
    virtual QString toString   (void) const = 0 ;

  protected:

  private:

};

// Defuzzifier
class Q_FUZZY_EXPORT Defuzzifier
{
  public:

    int Divisions ;

    explicit        Defuzzifier (int divisions = 1000) ;
    virtual        ~Defuzzifier (void) ;

    virtual QString Name        (void) const = 0 ;
    virtual QString className   (void) const = 0 ;
    virtual double  defuzzify   (const Term * term,double minimum,double maximum) const = 0 ;

  protected:

  private:

};

// Fuzzy sets and hedges
class Q_FUZZY_EXPORT Hedge
{
  public:

    explicit        Hedge (void) ;
    virtual        ~Hedge (void) ;

    virtual QString talk  (void) const = 0 ;
    virtual QString name  (void) const = 0 ;
    virtual double  hedge (double x) const = 0 ;

  protected:

  private:

};

class Q_FUZZY_EXPORT Maximum : public SNorm
{ // Max ( a , b )
  public:

    explicit        Maximum   (void) ;
    virtual        ~Maximum   (void) ;

    virtual int     typeId    (void) const ;
    virtual QString className (void) const ;
    virtual double  compute   (double a,double b) const ;

  protected:

  private:

};

class Q_FUZZY_EXPORT AlgebraicSum : public SNorm
{ // ( a + b ) - ( a * b )
  public:

    explicit        AlgebraicSum (void) ;
    virtual        ~AlgebraicSum (void) ;

    virtual int     typeId       (void) const ;
    virtual QString className    (void) const ;
    virtual double  compute      (double a,double b) const ;

  protected:

  private:

};

class Q_FUZZY_EXPORT BoundedSum : public SNorm
{ // Min ( 1 , a + b )
  public:

    explicit        BoundedSum (void) ;
    virtual        ~BoundedSum (void) ;

    virtual int     typeId     (void) const ;
    virtual QString className  (void) const ;
    virtual double  compute    (double a,double b) const ;

  protected:

  private:

};

class Q_FUZZY_EXPORT NormalizedSum : public SNorm
{ // a + b / Max ( 1 , Max ( a , b ) ) ;
  public:

    explicit        NormalizedSum (void) ;
    virtual        ~NormalizedSum (void) ;

    virtual int     typeId        (void) const ;
    virtual QString className     (void) const ;
    virtual double  compute       (double a,double b) const ;

  protected:

  private:

};

class Q_FUZZY_EXPORT DrasticSum : public SNorm
{ // Min ( a , b ) == 0 -> Max ( a , b )
  // Otherwise          -> 1.0
  public:

    explicit        DrasticSum (void) ;
    virtual        ~DrasticSum (void) ;

    virtual int     typeId     (void) const ;
    virtual QString className  (void) const ;
    virtual double  compute    (double a,double b) const ;

  protected:

  private:

};

class Q_FUZZY_EXPORT EinsteinSum : public SNorm
{ // ( a + b ) / ( 1 + a * b )
  public:

    explicit        EinsteinSum (void) ;
    virtual        ~EinsteinSum (void) ;

    virtual int     typeId      (void) const ;
    virtual QString className   (void) const ;
    virtual double  compute     (double a,double b) const ;

  protected:

  private:

};

class Q_FUZZY_EXPORT HamacherSum : public SNorm
{ // ( a + b - 2 * a * b ) / ( 1 - a * b )
  public:

    explicit        HamacherSum (void) ;
    virtual        ~HamacherSum (void) ;

    virtual int     typeId      (void) const ;
    virtual QString className   (void) const ;
    virtual double  compute     (double a,double b) const ;

  protected:

  private:

};

class Q_FUZZY_EXPORT Minimum : public TNorm
{ // Min ( a , b )
  public:

    explicit        Minimum   (void) ;
    virtual        ~Minimum   (void) ;

    virtual int     typeId    (void) const ;
    virtual QString className (void) const ;
    virtual double  compute   (double a,double b) const ;

  protected:

  private:

};

class Q_FUZZY_EXPORT AlgebraicProduct : public TNorm
{ // ( a * b )
  public:

    explicit        AlgebraicProduct (void) ;
    virtual        ~AlgebraicProduct (void) ;

    virtual int     typeId           (void) const ;
    virtual QString className        (void) const ;
    virtual double  compute          (double a,double b) const ;

  protected:

  private:

};

class Q_FUZZY_EXPORT BoundedDifference : public TNorm
{ // Max ( 0 , a + b - 1 )
  public:

    explicit        BoundedDifference (void) ;
    virtual        ~BoundedDifference (void) ;

    virtual int     typeId            (void) const ;
    virtual QString className         (void) const ;
    virtual double  compute           (double a,double b) const ;

  protected:

  private:

};

class Q_FUZZY_EXPORT DrasticProduct : public TNorm
{ // Max ( a , b ) == 1.0 -> Min ( a , b )
  // Otherwise            -> 0.0
  public:

    explicit        DrasticProduct (void) ;
    virtual        ~DrasticProduct (void) ;

    virtual int     typeId         (void) const ;
    virtual QString className      (void) const ;
    virtual double  compute        (double a,double b) const ;

  protected:

  private:

};

class Q_FUZZY_EXPORT EinsteinProduct : public TNorm
{ // ( a * b ) / ( 2 - ( a + b - ( a * b ) ) )
  public:

    explicit        EinsteinProduct (void) ;
    virtual        ~EinsteinProduct (void) ;

    virtual int     typeId          (void) const ;
    virtual QString className       (void) const ;
    virtual double  compute         (double a,double b) const ;

  protected:

  private:

};

class Q_FUZZY_EXPORT HamacherProduct : public TNorm
{ // ( a * b ) / ( a + b - ( a * b ) )
  public:

    explicit        HamacherProduct (void) ;
    virtual        ~HamacherProduct (void) ;

    virtual int     typeId          (void) const ;
    virtual QString className       (void) const ;
    virtual double  compute         (double a,double b) const ;

  protected:

  private:

};

class Q_FUZZY_EXPORT Any : public Hedge
{
  public:

    explicit        Any   (void) ;
    virtual        ~Any   (void) ;

    virtual QString talk  (void) const ;
    virtual QString name  (void) const ;
    virtual double  hedge (double x) const ;

  protected:

  private:

};

class Q_FUZZY_EXPORT Extremely : public Hedge
{
  public:

    explicit        Extremely (void) ;
    virtual        ~Extremely (void) ;

    virtual QString talk      (void) const ;
    virtual QString name      (void) const ;
    virtual double  hedge     (double x) const ;

  protected:

  private:

};

class Q_FUZZY_EXPORT Not : public Hedge
{
  public:

    explicit        Not   (void) ;
    virtual        ~Not   (void) ;

    virtual QString talk  (void) const ;
    virtual QString name  (void) const ;
    virtual double  hedge (double x) const ;

  protected:

  private:

};

class Q_FUZZY_EXPORT Seldom : public Hedge
{
  public:

    explicit        Seldom (void) ;
    virtual        ~Seldom (void) ;

    virtual QString talk   (void) const ;
    virtual QString name   (void) const ;
    virtual double  hedge  (double x) const ;

  protected:

  private:

};

class Q_FUZZY_EXPORT Somewhat : public Hedge
{
  public:

    explicit        Somewhat (void) ;
    virtual        ~Somewhat (void) ;

    virtual QString talk     (void) const ;
    virtual QString name     (void) const ;
    virtual double  hedge    (double x) const ;

  protected:

  private:

};

class Q_FUZZY_EXPORT Very : public Hedge
{
  public:

    explicit        Very  (void) ;
    virtual        ~Very  (void) ;

    virtual QString talk  (void) const ;
    virtual QString name  (void) const ;
    virtual double  hedge (double x) const ;

  protected:

  private:

};

class Q_FUZZY_EXPORT Accumulated : public Term
{
  public:

    explicit Accumulated                                                             (
             const QString & name         = ""                                       ,
             double          minimum      = -std::numeric_limits<double>::infinity() ,
             double          maximum      =  std::numeric_limits<double>::infinity() ,
             const SNorm   * accumulation = NULL                                   ) ;
    virtual ~Accumulated                (void) ;

    QString       talk                  (void) const ;
    QString       className             (void) const ;
    Accumulated * copy                  (void) const ;
    QString       toString              (int precision = 3) const ;
    double        membership            (double x) const;

    void          setMinimum            (double minimum) ;
    double        getMinimum            (void) const ;

    void          setMaximum            (double maximum) ;
    double        getMaximum            (void) const ;

    void          setAccumulation       (const SNorm * accumulation) ;
    const SNorm * getAccumulation       (void) const ;

    void          addTerm               (const Term * term) ;
    const Term  * getTerm               (int index) const ;
    const Term  * removeTerm            (int index) ;
    int           numberOfTerms         (void) const ;
    bool          isEmpty               (void) const ;
    void          clear                 (void) ;

    const QVector<const Term *> & terms (void) const ;

  protected:

    QVector<const Term *> _terms        ;
    double                _minimum      ;
    double                _maximum      ;
    const SNorm *         _accumulation ;

  private:

};

class Q_FUZZY_EXPORT Bell : public Term
{
  public:

    explicit Bell                                                              (
             const QString & name   = ""                                       ,
             double          center = std::numeric_limits<double>::quiet_NaN() ,
             double          width  = std::numeric_limits<double>::quiet_NaN() ,
             double          slope  = std::numeric_limits<double>::quiet_NaN()
             )                                                                 ;
    virtual ~Bell       (void) ;

    QString  talk       (void) const ;
    QString  className  (void) const ;
    Bell   * copy       (void) const ;
    QString  toString   (int precision = 3) const ;
    double   membership (double x) const ;

    void     setCenter  (double center) ;
    double   getCenter  (void) const ;

    void     setWidth   (double width) ;
    double   getWidth   (void) const ;

    void     setSlope   (double slope) ;
    double   getSlope   (void) const ;

  protected:

    double _center ;
    double _width  ;
    double _slope  ;

  private:

};

class Q_FUZZY_EXPORT Discrete : public Term
{
  public:

    typedef QPair<double,double> DoublePair ;

    QVector<double> x ;
    QVector<double> y ;

    explicit   Discrete   (const QString         & name = "") ;
    explicit   Discrete   (const QString         & name, int argc, ...) ;
    explicit   Discrete   (const QString         & name ,
                           const QVector<double> & x    ,
                           const QVector<double> & y  ) ;
    explicit   Discrete   (const QString         & name ,
                           const QVector<DoublePair> & xy) ;
    virtual   ~Discrete   (void) ;

    QString    talk       (void) const ;
    QString    className  (void) const ;
    Discrete * copy       (void) const ;
    double     membership (double x) const ;
    QString    toString   (int precision = 3) const ;

  protected:

  private:

};

class Q_FUZZY_EXPORT Gaussian : public Term
{
  public:

    explicit   Gaussian                                                          (
               const QString & name  = ""                                        ,
               double          mean  =  std::numeric_limits<double>::quiet_NaN() ,
               double          sigma = -std::numeric_limits<double>::quiet_NaN()
               )                                                                 ;
    virtual   ~Gaussian           (void) ;

    QString    talk             (void) const ;
    QString    className        (void) const ;
    Gaussian * copy             (void) const ;

    double     membership       (double x) const ;
    QString    toString         (int precision = 3) const ;

    void       setMean          (double c) ;
    double     getMean          (void) const ;

    void   setStandardDeviation (double sigma) ;
    double getStandardDeviation (void) const ;

  protected:

    double _mean              ;
    double _standardDeviation ;

  private:

};

class Q_FUZZY_EXPORT GaussianProduct : public Term
{
  public:

    explicit GaussianProduct                                                   (
             const QString & name   = ""                                       ,
             double          meanA  = std::numeric_limits<double>::quiet_NaN() ,
             double          sigmaA = std::numeric_limits<double>::quiet_NaN() ,
             double          meanB  = std::numeric_limits<double>::quiet_NaN() ,
             double          sigmaB = std::numeric_limits<double>::quiet_NaN()
             )                                                                 ;
    virtual ~GaussianProduct     (void) ;

    QString           talk       (void) const ;
    QString           className  (void) const ;
    GaussianProduct * copy       (void) const ;
    double            membership (double x) const ;
    QString           toString   (int precision = 3) const ;

    void              setMeanA   (double meanA) ;
    double            getMeanA   (void) const ;

    void   setStandardDeviationA (double sigmaA) ;
    double getStandardDeviationA (void) const ;

    void   setMeanB              (double meanB) ;
    double getMeanB              (void) const ;

    void   setStandardDeviationB (double sigmaB) ;
    double getStandardDeviationB (void) const ;

  protected:

    double _meanA              ;
    double _standardDeviationA ;
    double _meanB              ;
    double _standardDeviationB ;

  private:

};

class Q_FUZZY_EXPORT PiShape : public Term
{
  public:

    explicit  PiShape                                                                (
              const QString & name        = ""                                       ,
              double          bottomLeft  = std::numeric_limits<double>::quiet_NaN() ,
              double          topLeft     = std::numeric_limits<double>::quiet_NaN() ,
              double          topRight    = std::numeric_limits<double>::quiet_NaN() ,
              double          bottomRight = std::numeric_limits<double>::quiet_NaN()
              )                                                                      ;
    virtual  ~PiShape        (void) ;

    QString   talk           (void) const ;
    QString   className      (void) const ;
    PiShape * copy           (void) const ;
    double    membership     (double x) const ;
    QString   toString       (int precision = 3) const ;

    void      setBottomLeft  (double a) ;
    double    getBottomLeft  (void) const ;

    void      setTopLeft     (double b) ;
    double    getTopLeft     (void) const ;

    void      setTopRight    (double d) ;
    double    getTopRight    (void) const ;

    void      setBottomRight (double c) ;
    double    getBottomRight (void) const ;

  protected:

    double _bottomLeft  ;
    double _topLeft     ;
    double _topRight    ;
    double _bottomRight ;

  private:

};

class Q_FUZZY_EXPORT Ramp : public Term
{
  public:

    explicit Ramp                                                             (
             const QString & name  = ""                                       ,
             double          start = -std::numeric_limits<double>::infinity() ,
             double          end   =  std::numeric_limits<double>::infinity()
             )                                                                ;
    virtual ~Ramp       (void) ;

    QString  talk       (void) const ;
    QString  className  (void) const ;
    Ramp  *  copy       (void) const ;
    double   membership (double x) const ;
    QString  toString   (int precision = 3) const ;

    void     setStart   (double start) ;
    double   getStart   (void) const ;

    void     setEnd     (double end) ;
    double   getEnd     (void) const ;

  protected:

    double _start ;
    double _end   ;

  private:

};

class Q_FUZZY_EXPORT Rectangle : public Term
{
  public:

    explicit       Rectangle                                                          (
                   const QString & name    = ""                                       ,
                   double          minimum = -std::numeric_limits<double>::infinity() ,
                   double          maximum =  std::numeric_limits<double>::infinity()
                   )                                                                  ;
    virtual       ~Rectangle  (void) ;

    QString        talk       (void) const ;
    QString        className  (void) const ;
    Rectangle *    copy       (void) const ;

    double         membership (double x) const ;
    QString        toString   (int precision = 3) const ;

    virtual void   setMinimum (double minimum) ;
    virtual double getMinimum (void) const ;

    virtual void   setMaximum (double maximum) ;
    virtual double getMaximum (void) const ;

  protected:

    double _minimum ;
    double _maximum ;

  private:

};

class Q_FUZZY_EXPORT SShape : public Term
{
  public:

    explicit SShape                                                            (
             const QString & name   = ""                                       ,
             double          _start = -std::numeric_limits<double>::infinity() ,
             double          _end   =  std::numeric_limits<double>::infinity()
             )                                                                 ;
    virtual ~SShape     (void) ;

    QString  talk       (void) const ;
    QString  className  (void) const ;
    SShape * copy       (void) const ;
    double   membership (double x) const ;
    QString  toString   (int precision = 3) const ;

    void     setStart   (double start) ;
    double   getStart   (void) const ;

    void     setEnd     (double end) ;
    double   getEnd     (void) const ;

  protected:

    double _start ;
    double _end   ;

  private:

};

class Q_FUZZY_EXPORT Sigmoid : public Term
{
  public:

    explicit  Sigmoid                                                               (
              const QString & name       = ""                                       ,
              double          inflection = std::numeric_limits<double>::quiet_NaN() ,
              double          slope      = std::numeric_limits<double>::quiet_NaN()
              )                                                                     ;
    virtual  ~Sigmoid       (void) ;

    QString   talk          (void) const ;
    QString   className     (void) const ;
    Sigmoid * copy          (void) const ;
    double    membership    (double x) const ;
    QString   toString      (int precision = 3) const ;

    void      setInflection (double inflection) ;
    double    getInflection (void) const ;

    void      setSlope      (double slope) ;
    double    getSlope      (void) const ;

  protected:

    double _inflection ;
    double _slope      ;

  private:

};

class Q_FUZZY_EXPORT SigmoidDifference : public Term
{
  public:

    explicit SigmoidDifference                                                  (
             const QString & name    = ""                                       ,
             double          left    = std::numeric_limits<double>::quiet_NaN() ,
             double          rising  = std::numeric_limits<double>::quiet_NaN() ,
             double          falling = std::numeric_limits<double>::quiet_NaN() ,
             double          right   = std::numeric_limits<double>::quiet_NaN()
             )                                                                  ;
    virtual ~SigmoidDifference     (void) ;

    QString             talk       (void) const ;
    QString             className  (void) const ;
    SigmoidDifference * copy       (void) const ;
    double              membership (double x) const ;
    QString             toString   (int precision = 3) const ;

    void                setLeft    (double leftInflection) ;
    double              getLeft    (void) const ;

    void                setRising  (double risingSlope) ;
    double              getRising  (void) const ;

    void                setFalling (double fallingSlope) ;
    double              getFalling (void) const ;

    void                setRight   (double rightInflection) ;
    double              getRight   (void) const ;

  protected:

    double _left    ;
    double _rising  ;
    double _falling ;
    double _right   ;

  private:

};

class Q_FUZZY_EXPORT SigmoidProduct : public Term
{
  public:

    explicit SigmoidProduct                                                     (
             const QString & name    = ""                                       ,
             double          left    = std::numeric_limits<double>::quiet_NaN() ,
             double          rising  = std::numeric_limits<double>::quiet_NaN() ,
             double          falling = std::numeric_limits<double>::quiet_NaN() ,
             double          right   = std::numeric_limits<double>::quiet_NaN()
             )                                                                  ;
    virtual ~SigmoidProduct     (void) ;

    QString          talk       (void) const ;
    QString          className  (void) const ;
    SigmoidProduct * copy       (void) const ;
    double           membership (double x) const ;
    QString          toString   (int precision = 3) const ;

    void             setLeft    (double leftInflection) ;
    double           getLeft    (void) const ;

    void             setRising  (double risingSlope) ;
    double           getRising  (void) const ;

    void             setFalling (double fallingSlope) ;
    double           getFalling (void) const ;

    void             setRight   (double rightInflection) ;
    double           getRight   (void) const ;

  protected:

    double _left    ;
    double _rising  ;
    double _falling ;
    double _right   ;

  private:

};

class Q_FUZZY_EXPORT Thresholded : public Term
{
  public:

    explicit      Thresholded                               (
                  const Term  * term               = NULL   ,
                  double        threshold          = 1.0    ,
                  const TNorm * activationOperator = NULL ) ;
    virtual      ~Thresholded   (void) ;

    QString       talk          (void) const ;
    QString       className     (void) const ;
    Thresholded * copy          (void) const ;
    double        membership    (double x) const ;

    void          setTerm       (const Term * term) ;
    const Term  * getTerm       (void) const ;

    void          setThreshold  (double threshold) ;
    double        getThreshold  (void) const ;

    void          setActivation (const TNorm * activation) ;
    const TNorm * getActivation (void) const ;

    QString       toString      (int precision = 3) const ;

  protected:

    const Term  * _term       ;
    double        _threshold  ;
    const TNorm * _activation ;

  private:

};

class Q_FUZZY_EXPORT Trapezoid : public Term
{
  public:

    explicit    Trapezoid                                                        (
                const QString & name = ""                                        ,
                double          a    = -std::numeric_limits<double>::infinity () ,
                double          b    =  std::numeric_limits<double>::quiet_NaN() ,
                double          c    =  std::numeric_limits<double>::quiet_NaN() ,
                double          d    =  std::numeric_limits<double>::infinity ()
                )                                                                ;
    virtual    ~Trapezoid  (void) ;

    QString     talk       (void) const ;
    QString     className  (void) const ;
    Trapezoid * copy       (void) const ;
    double      membership (double x) const ;
    QString     toString   (int precision = 3) const ;

    void        setA       (double a) ;
    double      getA       (void) const ;

    void        setB       (double b) ;
    double      getB       (void) const ;

    void        setC       (double c) ;
    double      getC       (void) const ;

    void        setD       (double d) ;
    double      getD       (void) const ;

  protected:

    double _a ;
    double _b ;
    double _c ;
    double _d ;

  private:

};

class Q_FUZZY_EXPORT Triangle : public Term
{
  public:

    explicit   Triangle                                                         (
               const QString & name = ""                                        ,
               double          a    = -std::numeric_limits<double>::infinity () ,
               double          b    =  std::numeric_limits<double>::quiet_NaN() ,
               double          c    =  std::numeric_limits<double>::infinity ()
               )                                                                ;
    virtual   ~Triangle   (void) ;

    QString    talk       (void) const ;
    QString    className  (void) const ;
    Triangle * copy       (void) const ;
    double     membership (double x) const ;
    QString    toString   (int precision = 3) const ;

    void       setA       (double a) ;
    double     getA       (void) const ;

    void       setB       (double b) ;
    double     getB       (void) const ;

    void       setC       (double c) ;
    double     getC       (void) const ;

  protected:

    double _a ;
    double _b ;
    double _c ;

  private:

};

class Q_FUZZY_EXPORT ZShape : public Term
{
  public:

    explicit ZShape                                                              (
               const QString & name   = ""                                       ,
               double          _start = -std::numeric_limits<double>::infinity() ,
               double          _end   =  std::numeric_limits<double>::infinity()
             )                                                                   ;
    virtual ~ZShape     (void) ;

    QString  talk       (void) const ;
    QString  className  (void) const ;
    ZShape * copy       (void) const ;
    double   membership (double x) const ;
    QString  toString   (int precision = 3) const ;

    void     setStart   (double start) ;
    double   getStart   (void) const ;

    void     setEnd     (double end) ;
    double   getEnd     (void) const ;

  protected:

    double _start ;
    double _end   ;

  private:

};

class Q_FUZZY_EXPORT Centroid : public Defuzzifier
{
  public:

    explicit        Centroid  (int divisions = 1000) ;
                    Centroid  (const Centroid & centroid) ;
    virtual        ~Centroid  (void) ;

    virtual QString Name      (void) const ;
    virtual QString className (void) const ;
    virtual double  defuzzify (const Term * term,double minimum,double maximum) const ;

  protected:

  private:

};

class Q_FUZZY_EXPORT MaximumDefuzzifier : public Defuzzifier
{
  public:

    enum FmdTypes {
      SMALLEST    ,
      LARGEST     ,
      MEAN
    }             ;

    explicit MaximumDefuzzifier     (enum FmdTypes type,int divisions = 1000) ;
             MaximumDefuzzifier     (const MaximumDefuzzifier & md) ;
    virtual ~MaximumDefuzzifier     (void);

    virtual QString       Name      (void) const ;
    virtual QString       className (void) const ;
    virtual double        defuzzify (const Term * term,double minimum,double maximum) const ;

    virtual void          setType   (enum FmdTypes type) ;
    virtual enum FmdTypes getType   (void) const ;

  protected:

    FmdTypes _type ;

  private:

};

class Q_FUZZY_EXPORT MeanOfMaximum : public MaximumDefuzzifier
{
  public:

    explicit MeanOfMaximum (int divisions = 1000) ;
             MeanOfMaximum (const MeanOfMaximum & mom) ;
    virtual ~MeanOfMaximum (void) ;

    virtual QString Name   (void) const ;

  protected:

  private:

};

class Q_FUZZY_EXPORT SmallestOfMaximum : public MaximumDefuzzifier
{
  public:

    explicit SmallestOfMaximum (int divisions = 1000) ;
             SmallestOfMaximum (const SmallestOfMaximum & som) ;
    virtual ~SmallestOfMaximum (void) ;

    virtual QString Name       (void) const ;

  protected:

  private:

};

class Q_FUZZY_EXPORT LargestOfMaximum : public MaximumDefuzzifier
{
  public:

    explicit LargestOfMaximum (int divisions = 1000) ;
             LargestOfMaximum (const LargestOfMaximum & lom) ;
    virtual ~LargestOfMaximum (void) ;

    virtual QString Name      (void) const ;

  protected:

  private:

};

class Q_FUZZY_EXPORT Variable : public Object
{
  public:

    QString Name ;

    explicit Variable                                                             (
               const QString & name    = ""                                       ,
               double          minimum = -std::numeric_limits<double>::infinity() ,
               double          maximum =  std::numeric_limits<double>::infinity()
             )                                                                    ;
                         Variable          (const Variable & copy) ;
    virtual             ~Variable          (void) ;

    virtual void         setName           (const QString & name) ;
    virtual QString      getName           (void) const ;

    virtual void         setRange          (double minimum,double maximum) ;

    virtual void         setMinimum        (double minimum) ;
    virtual double       getMinimum        (void) const ;

    virtual void         setMaximum        (double maximum) ;
    virtual double       getMaximum        (void) const ;

    virtual QString      fuzzify           (double x) const ;
    virtual Term       * highestMembership (double x,double * yhighest = NULL) const ;

    virtual QString      toString          (void) const ;

    virtual void         sort              (void) ;
    virtual void         addTerm           (Term * term) ;
    virtual void         insertTerm        (Term * term,int index) ;
    virtual Term       * getTerm           (int index) const ;
    virtual Term       * getTerm           (const QString & name) const ;
    virtual bool         hasTerm           (const QString & name) const ;
    virtual Term       * removeTerm        (int index) ;
    virtual int          numberOfTerms     (void) const ;

    virtual const QVector<Term *> & terms (void) const ;

  protected:

    QString         _name    ;
    QVector<Term *> _terms   ;
    double          _minimum ;
    double          _maximum ;

    struct SortByCoG
    {
        double minimum, maximum;
        Centroid cog;

        bool operator() (const Term * a,const Term * b)
        {
            return Operation :: isLt                            (
                    cog . defuzzify ( a , minimum , maximum )   ,
                    cog . defuzzify ( b , minimum , maximum ) ) ;
        }
    };

  private:

};

class Q_FUZZY_EXPORT InputVariable : public Variable
{
  public:

    explicit InputVariable                                                  (
               const QString & name    = ""                                       ,
               double          minimum = -std::numeric_limits<double>::infinity() ,
               double          maximum =  std::numeric_limits<double>::infinity()
             )                                                                    ;
    virtual ~InputVariable  (void) ;

    virtual void   setInput (double input) ;
    virtual double getInput (void) const ;

  protected:

    double _input ;

  private:

};

class Q_FUZZY_EXPORT OutputVariable : public Variable
{
  public:

    explicit OutputVariable                                                       (
               const QString & name    = ""                                       ,
               double          minimum = -std::numeric_limits<double>::infinity() ,
               double          maximum =  std::numeric_limits<double>::infinity()
             )                                                                    ;
    virtual ~OutputVariable                (void) ;

    virtual Accumulated * output           (void) const ;

    virtual void   setMinimum              (double minimum) ;
    virtual void   setMaximum              (double maximum) ;

    virtual void   setDefuzzifier          (Defuzzifier * defuzzifier) ;
    virtual Defuzzifier * getDefuzzifier   (void) const;

    virtual void   setDefaultValue         (double defaultValue) ;
    virtual double getDefaultValue         (void) const ;

    virtual void   setDefuzzifiedValue     (double defuzzifiedValue) ;
    virtual double getDefuzzifiedValue     (void) const ;

    virtual void   setLockDefuzzifiedValue (bool lock) ;
    virtual bool   lockDefuzzifiedValue    (void) const ;

    virtual double defuzzify               (void) ;
    virtual double defuzzifyIgnoreLock     (void) const ;

  protected:

    Accumulated * _output               ;
    Defuzzifier * _defuzzifier          ;
    double        _defaultValue         ;
    double        _defuzzifiedValue     ;
    bool          _lockDefuzzifiedValue ;

  private:

};

class Q_FUZZY_EXPORT GenericOperator
{
  public:

    QString name          ;
    short   precedence    ;
    short   arity         ;
    short   associativity ;

    explicit GenericOperator                        (
               const QString & name                 ,
               short           precedence           ,
               short           arity         =  2   ,
               short           associativity = -1 ) ;
    virtual ~GenericOperator (void) ;

    QString toString(void) const ;

  protected:

  private:

};

class Q_FUZZY_EXPORT GenericFunction
{
  public:

    QString        name           ;
    short          arity          ;
    short          associativity  ;
    OneArgFunction oneArgFunction ;
    TwoArgFunction twoArgFunction ;

    explicit GenericFunction (const QString & name,short arity = 1 ) ;
    explicit GenericFunction (const QString & name,OneArgFunction oneArgFunction) ;
    explicit GenericFunction (const QString & name,TwoArgFunction twoArgFunction) ;
    virtual ~GenericFunction (void) ;

    QString toString(void) const ;

  protected:

  private:

};

class Q_FUZZY_EXPORT Infix
{
  public:

    explicit Infix       (void) ;
    virtual ~Infix       (void) ;

    virtual QString toPostfix  (const QString & infixString) ;

    virtual bool    isOperand  (const QString & token) const ;
    virtual bool    isOperator (const QString & token) const ;
    virtual bool    isFunction (const QString & token) const ;

    virtual void addGenericOperator(GenericOperator * genericOperator) ;
    virtual GenericOperator * removeGenericOperator (const QString & key) ;
    virtual GenericOperator * getGenericOperator    (const QString & key) const ;
    virtual const QMap<QString,GenericOperator *> & genericOperators(void) const;

    virtual void addGenericFunction(GenericFunction * genericFunction) ;
    virtual GenericFunction * removeGenericFunction (const QString & key) ;
    virtual GenericFunction * getGenericFunction    (const QString & key) const ;
    virtual const QMap<QString,GenericFunction *> & genericFunctions(void) const;

  protected:

    QMap<QString,GenericOperator *> _genericOperators ;
    QMap<QString,GenericFunction *> _genericFunctions ;

    virtual void loadGenericOperators (void) ;
    virtual void loadGenericFunctions (void) ;

};

class Q_FUZZY_EXPORT Rule
{
  public:

    explicit Rule (void) ;
    virtual ~Rule (void) ;

    virtual Antecedent * getAntecedent (void) const = 0 ;
    virtual Consequent * getConsequent (void) const = 0 ;

    virtual double  firingStrength  (const TNorm * tnorm,const SNorm * snorm) const ;
    virtual void    fire            (double strength,const TNorm * activation) const ;

    virtual void    setWeight       (double weight) ;
    virtual double  getWeight       (void) const ;

    virtual QString getUnparsedRule (void) const ;
    virtual QString toString        (void) const ;
            QString errorString     (void) const ;
            void    setError        (QString errString) ;
            QString logString       (void) const ;
            void    log             (QString text,bool clearIt = false) ;

    static  QString FuzzyIF   ;
    static  QString FuzzyIS   ;
    static  QString FuzzyTHEN ;
    static  QString FuzzyAND  ;
    static  QString FuzzyOR   ;
    static  QString FuzzyWITH ;

    static QString ifKeyword   (void) ;
    static QString isKeyword   (void) ;
    static QString thenKeyword (void) ;
    static QString andKeyword  (void) ;
    static QString orKeyword   (void) ;
    static QString withKeyword (void) ;

  protected:

    double  _weight       ;
    QString _unparsedRule ;
    QString _errorString  ;
    QString _logString    ;

    virtual void setUnparsedRule (const QString & unparsedRule) ;

  private:

};

class Q_FUZZY_EXPORT RuleBlock
{
  public:

    explicit RuleBlock                    (const QString & name = "") ;
    virtual ~RuleBlock                    (void) ;

    virtual void          fireRules       (void) ;

    virtual void          setName         (QString name) ;
    virtual QString       getName         (void) const ;

    virtual void          setTnorm        (const TNorm * tnorm) ;
    virtual const TNorm * getTnorm        (void) const ;

    virtual void          setSnorm        (const SNorm * snorm) ;
    virtual const SNorm * getSnorm        (void) const ;

    virtual void          setActivation   (const TNorm * activation) ;
    virtual const TNorm * getActivation   (void) const ;

    virtual QString       toString        (void) const ;

    virtual void          addRule         (Rule * rule) ;
    virtual void          insertRule      (Rule * rule, int index) ;
    virtual Rule *        getRule         (int index) const ;
    virtual Rule *        removeRule      (int index) ;
    virtual int           numberOfRules   (void) const ;

    virtual const QVector<Rule *> & rules (void) const ;

  protected:

    QVector<Rule *> _rules      ;
    QString         _name       ;
    const TNorm  *  _tnorm      ;
    const SNorm  *  _snorm      ;
    const TNorm  *  _activation ;

  private:

};

class Q_FUZZY_EXPORT TermFactory
{
  public:

    explicit TermFactory (void) ;
    virtual ~TermFactory (void) ;

    virtual Term           * create    (const QString & className,const QVector<double> & params) const ;
    virtual QVector<QString> available (void) const ;

  protected:

  private:

};

class Q_FUZZY_EXPORT HedgeFactory
{
  public:

    explicit HedgeFactory              (void) ;
    virtual ~HedgeFactory              (void) ;

    virtual Hedge          * create    (const QString & name) const ;
    virtual QVector<QString> available (void) const ;

  protected:

  private:

};

class Q_FUZZY_EXPORT SNormFactory
{
  public:

    explicit SNormFactory              (void) ;
    virtual ~SNormFactory              (void) ;

    virtual SNorm          * create    (const QString & className) const ;
    virtual QVector<QString> available (void) const ;

  protected:

  private:

};

class Q_FUZZY_EXPORT TNormFactory
{
  public:

    explicit TNormFactory              (void) ;
    virtual ~TNormFactory              (void) ;

    virtual TNorm          * create    (const QString & className) const ;
    virtual QVector<QString> available (void) const ;

  protected:

  private:

};

class Q_FUZZY_EXPORT DefuzzifierFactory
{
  public:

    explicit DefuzzifierFactory        (void) ;
    virtual ~DefuzzifierFactory        (void) ;

    virtual Defuzzifier    * create    (const QString & className,int divisions = 1000) ;
    virtual QVector<QString> available (void) const ;

  protected:

  private:

};

class Q_FUZZY_EXPORT Factory
{
  public:

    explicit Factory(void) ;
    virtual ~Factory(void) ;

    static Factory             * instance       (void) ;

    virtual void                 setTnorm       (TNormFactory * tnorm) ;
    virtual TNormFactory       * tnorm          (void) const ;

    virtual void                 setSnorm       (SNormFactory * snorm) ;
    virtual SNormFactory       * snorm          (void) const ;

    virtual void                 setDefuzzifier (DefuzzifierFactory * defuzzifier) ;
    virtual DefuzzifierFactory * defuzzifier    (void) const ;

    virtual void                 setTerm        (TermFactory * term) ;
    virtual TermFactory        * term           (void) const ;

    virtual void                 setHedge       (HedgeFactory * hedge) ;
    virtual HedgeFactory       * hedge          (void) const ;

  protected:

    static Factory     * _instance    ;

    TNormFactory       * _tnorm       ;
    SNormFactory       * _snorm       ;
    DefuzzifierFactory * _defuzzifier ;
    TermFactory        * _term        ;
    HedgeFactory       * _hedge       ;

  private:

};

// Fuzzy Engine
class Q_FUZZY_EXPORT Engine : public Object
{
  public:

    QString              Name        ;
    QMap<QString,double> ioVariables ;

    explicit       Engine   (const QString & name = "") ;
    virtual       ~Engine   (void) ;

    virtual void configure                                                  (
                   const QString & tnorm             = "N::Fuzzy::Minimum"  ,
                   const QString & snorm             = "N::Fuzzy::Maximum"  ,
                   const QString & activationTnorm   = "N::Fuzzy::Minimum"  ,
                   const QString & accumulationSnorm = "N::Fuzzy::Maximum"  ,
                   const QString & defuzzifier       = "N::Fuzzy::Centroid" ,
                   int             divisions         = 1000               ) ;

    virtual void process(void) ;
    virtual void processVariables(void) ;

    virtual void setName(const QString & name) ;
    virtual QString getName(void) const ;

    virtual InputVariable * getInputVariable    (int index) const ;
    virtual InputVariable * getInputVariable    (const QString & name) const ;
    virtual InputVariable * removeInputVariable (int index) ;
    virtual InputVariable * removeInputVariable (const QString & name) ;

    virtual const QVector<InputVariable *> & inputVariables(void) const ;

    virtual void addInputVariable       (InputVariable * inputVariable);
    virtual void insertInputVariable    (InputVariable * inputVariable,int index);

    virtual bool hasInputVariable       (const QString & name) const ;
    virtual int  numberOfInputVariables (void) const ;

    virtual OutputVariable * getOutputVariable    (int index) const;
    virtual OutputVariable * getOutputVariable    (const QString & name) const;
    virtual OutputVariable * removeOutputVariable (int index);
    virtual OutputVariable * removeOutputVariable (const QString & name);

    virtual const QVector<OutputVariable *> & outputVariables(void) const ;

    virtual void addOutputVariable      (OutputVariable * outputVariable);
    virtual void insertOutputVariable   (OutputVariable * outputVariable, int index);

    virtual bool hasOutputVariable      (const QString & name) const;
    virtual int  numberOfOutputVariables(void) const ;

    virtual RuleBlock * getRuleBlock    (int index) const ;
    virtual RuleBlock * getRuleBlock    (const QString & name) const ;
    virtual RuleBlock * removeRuleBlock (int index) ;
    virtual RuleBlock * removeRuleBlock (const QString & name) ;

    virtual void addRuleBlock    (RuleBlock * ruleblock);
    virtual void insertRuleBlock (RuleBlock * ruleblock, int index) ;

    virtual const QVector<RuleBlock *> & ruleBlocks(void) const ;

    virtual bool hasRuleBlock         (const QString & name) const ;
    virtual int  numberOfRuleBlocks   (void) const;

    virtual Hedge * getHedge    (int index) const ;
    virtual Hedge * getHedge    (const QString & name) const ;
    virtual Hedge * removeHedge (int index) ;
    virtual Hedge * removeHedge (const QString & name) ;

    virtual const QVector<Hedge *> & hedges(void) const ;

    Hedge *      chosen              (double x) ;

    virtual void addHedge       (Hedge * hedge) ;
    virtual void insertHedge    (Hedge * hedge, int index) ;

    virtual bool hasHedge       (const QString & name) const ;
    virtual int  numberOfHedges (void) const ;

    bool         isError        (void) ;
    void         setError       (QString errString,bool error = true) ;
    QString      ErrorString    (void) ;

  protected:

    QString                   _name            ;
    QString                   _errorString     ;
    bool                      _error           ;
    QVector<InputVariable  *> _inputVariables  ;
    QVector<OutputVariable *> _outputVariables ;
    QVector<RuleBlock      *> _ruleblocks      ;
    QVector<Hedge          *> _hedges          ;

    virtual TNorm       * createTnorm       (const QString & tnorm      ) const ;
    virtual SNorm       * createSnorm       (const QString & snorm      ) const ;
    virtual Defuzzifier * createDefuzzifier (const QString & defuzzifier) const ;

  private:

};

class Q_FUZZY_EXPORT MamdaniExpression
{
  public:

    const bool isOperator ;

    explicit MamdaniExpression (bool isOperator) ;
    virtual ~MamdaniExpression (void) ;

    virtual QString toString   (void) const = 0 ;

  protected:

  private:

};

class Q_FUZZY_EXPORT MamdaniProposition : public MamdaniExpression
{
  public:

    Variable      *  variable ;
    QVector<Hedge *> hedges   ;
    Term          *  term     ;

    explicit MamdaniProposition(void) ;
    virtual ~MamdaniProposition(void) ;

    QString toString(void) const ;

  protected:

  private:

};

class Q_FUZZY_EXPORT MamdaniOperator : public MamdaniExpression
{
  public:

    QString             name  ;
    MamdaniExpression * left  ;
    MamdaniExpression * right ;

    explicit MamdaniOperator (void) ;
    virtual ~MamdaniOperator (void) ;

    QString toString         (void) const ;

  protected:

  private:

};

class Q_FUZZY_EXPORT MamdaniAntecedent : public Antecedent
{
  public:

    explicit MamdaniAntecedent (void) ;
    virtual ~MamdaniAntecedent (void) ;

    virtual MamdaniExpression * getRoot (void) const ;

    virtual bool    evaluate         (const QString & antecedent,Engine * engine) ;
    virtual void    load             (const QString & antecedent,Engine * engine) ;
    virtual double  firingStrength   (const TNorm   * tnorm,const SNorm * snorm,const MamdaniExpression * node) const ;
    virtual double  firingStrength   (const TNorm   * tnorm,const SNorm * snorm) const ;
    virtual QString toString         (void) const;

    virtual QString toStringPrefix   (const MamdaniExpression * node = NULL) const ;
    virtual QString toStringInfix    (const MamdaniExpression * node = NULL) const ;
    virtual QString toStringPostfix  (const MamdaniExpression * node = NULL) const ;

  protected:

    MamdaniExpression * _root;

  private:

};

class Q_FUZZY_EXPORT MamdaniConsequent : public Consequent
{
  public:

    explicit MamdaniConsequent (void) ;
    virtual ~MamdaniConsequent (void) ;

    virtual QVector<MamdaniProposition *> conclusions(void) const ;

    virtual bool    evaluate (const QString & consequent,Engine * engine) ;
    virtual void    load     (const QString & consequent,Engine * engine) ;
    virtual void    fire     (double strength,const TNorm * activation) ;
    virtual QString toString (void) const ;

  protected:

    QVector<MamdaniProposition *> _conclusions ;

  private:

};

class Q_FUZZY_EXPORT MamdaniRule : public Rule
{
  public:

    explicit            MamdaniRule   (void) ;
    virtual            ~MamdaniRule   (void) ;

    void                setAntecedent (MamdaniAntecedent * antecedent) ;
    MamdaniAntecedent * getAntecedent (void) const ;

    void                setConsequent (MamdaniConsequent * consequent) ;
    MamdaniConsequent * getConsequent (void) const ;

    static MamdaniRule * parse        (const QString & rule,Engine * engine) ;

  protected:

    MamdaniAntecedent * _antecedent;
    MamdaniConsequent * _consequent;

  private:

};

class Q_FUZZY_EXPORT Importer
{
  public:

    explicit Importer           (void) ;
    virtual ~Importer           (void) ;

    virtual QString  name       (void) const = 0 ;
    virtual Engine * fromString (const QString & s) const = 0 ;

  protected:

  private:

};

class Q_FUZZY_EXPORT Exporter
{
  public:

    explicit Exporter        (void) ;
    virtual ~Exporter        (void) ;

    virtual QString name     (void) const = 0 ;
    virtual QString toString (const Engine * engine) const = 0 ;

  protected:

  private:

};

// Export Fuzzy rules into C++ source code
class Q_FUZZY_EXPORT CppExporter : public Exporter
{
  public:

    explicit CppExporter     (void) ;
    virtual ~CppExporter     (void) ;

    virtual QString name     (void) const ;
    virtual QString toString (const Engine * engine) const ;

  protected:

    virtual QString toCpp    (const Hedge       * hedge      ) const ;
    virtual QString toCpp    (const Term        * term       ) const ;
    virtual QString toCpp    (const Operator    * op         ) const ;
    virtual QString toCpp    (const Defuzzifier * defuzzifier) const ;

  private:

};

// Import from Fuzzy Logic Language (FCL)
class Q_FUZZY_EXPORT FclImporter : public Importer
{
  public:

    explicit FclImporter         (void) ;
    virtual ~FclImporter         (void) ;

    virtual QString  name         (void) const ;
    virtual Engine * fromString   (const QString & fcl) const ;

  protected:

    virtual void processBlock     (const QString & tag  ,const QString & block,Engine * engine) const ;
    virtual void processVar       (const QString & var  ,const QString & block,Engine * engine) const ;
    virtual void processFuzzify   (const QString & block,Engine * engine) const ;
    virtual void processDefuzzify (const QString & block,Engine * engine) const ;
    virtual void processRuleBlock (const QString & block,Engine * engine) const ;

    virtual TNorm * extractTNorm  (const QString & line) const ;
    virtual SNorm * extractSNorm  (const QString & line) const ;

    virtual Term  * extractTerm   (const QString & line) const ;
    virtual Term  * createInstance                      (
                      const QString         & termClass ,
                      const QString         & name      ,
                      const QVector<double> & params    ) const ;
    virtual Defuzzifier * extractDefuzzifier(const QString & line) const;
    virtual double extractDefaultValue(const QString & line,bool   & lockDefuzzifiedValue) const ;
    virtual void   extractRange       (const QString & line,double & minimum,double & maximum) const ;

  private:

};

// Export into Fuzzy Logic Language (FCL)
class Q_FUZZY_EXPORT FclExporter : public Exporter
{
  public:

    explicit FclExporter (void) ;
    virtual ~FclExporter (void) ;

    virtual QString name       (void) const ;
    virtual QString toString   (const Engine * engine) const ;

  protected:

    virtual QString toFcl (const TNorm       * tnorm      ) const ;
    virtual QString toFcl (const SNorm       * snorm      ) const ;
    virtual QString toFcl (const Defuzzifier * defuzzifier) const ;
    virtual QString toFcl (const Term        * term       ) const ;

  private:

};

// Import from Fuzzy Inference System (FIS)
class Q_FUZZY_EXPORT FisImporter : public Importer
{
  public:

    explicit FisImporter        (void) ;
    virtual ~FisImporter        (void) ;

    virtual QString  name       (void) const ;
    virtual Engine * fromString (const QString & fcl) const ;

  protected:

    virtual void importSystem                   (
                   const QString & section      ,
                   Engine        * engine       ,
                   QString       & andMethod    ,
                   QString       & orMethod     ,
                   QString       & impMethod    ,
                   QString       & aggMethod    ,
                   QString       & defuzzMethod ) const;
    virtual void importInput  (const QString & section,Engine * engine) const ;
    virtual void importOutput (const QString & section,Engine * engine) const ;
    virtual void importRules  (const QString & section,Engine * engine) const ;

    virtual QString translateProposition (double code,Variable * variable) const ;

    virtual QString flTnorm       (const QString & tnorm) const ;
    virtual QString flSnorm       (const QString & tnorm) const ;
    virtual QString flDefuzzifier (const QString & tnorm) const ;

    virtual Term * extractTerm    (const QString & line) const ;
    virtual Term * createInstance                      (
                           const QString         & termClass ,
                           const QString         & name      ,
                           const QVector<double> & params    ) const;
    virtual void extractRange (const QString & range,double & minimum,double & maximum) const ;

  private:

};

// Export into Fuzzy Inference System (FIS)
class Q_FUZZY_EXPORT FisExporter : public Exporter
{
  public:

    explicit FisExporter (void) ;
    virtual ~FisExporter (void) ;

    virtual QString name       (void) const ;
    virtual QString toString   (const Engine * engine) const ;

  protected:

    QString exportSystem  (const Engine * engine) const ;
    QString exportInputs  (const Engine * engine) const ;
    QString exportOutputs (const Engine * engine) const ;
    QString exportRules   (const Engine * engine) const ;
    QString exportRule    (const MamdaniRule * rule,const Engine * engine) const ;
    QString translate     (const QVector<MamdaniProposition *> & propositions ,
                           const QVector<Variable           *>   variables    ) const ;

    QString toFis(const TNorm       * tnorm      ) const ;
    QString toFis(const SNorm       * snorm      ) const ;
    QString toFis(const Defuzzifier * defuzzifier) const ;
    QString toFis(const Term        * term       ) const ;

  private:

};

}
}

Q_DECLARE_METATYPE(N::Fuzzy::Operation)
Q_DECLARE_METATYPE(N::Fuzzy::Maximum)
Q_DECLARE_METATYPE(N::Fuzzy::AlgebraicSum)
Q_DECLARE_METATYPE(N::Fuzzy::BoundedSum)
Q_DECLARE_METATYPE(N::Fuzzy::NormalizedSum)
Q_DECLARE_METATYPE(N::Fuzzy::DrasticSum)
Q_DECLARE_METATYPE(N::Fuzzy::EinsteinSum)
Q_DECLARE_METATYPE(N::Fuzzy::HamacherSum)
Q_DECLARE_METATYPE(N::Fuzzy::Minimum)
Q_DECLARE_METATYPE(N::Fuzzy::AlgebraicProduct)
Q_DECLARE_METATYPE(N::Fuzzy::BoundedDifference)
Q_DECLARE_METATYPE(N::Fuzzy::DrasticProduct)
Q_DECLARE_METATYPE(N::Fuzzy::EinsteinProduct)
Q_DECLARE_METATYPE(N::Fuzzy::HamacherProduct)
Q_DECLARE_METATYPE(N::Fuzzy::Any)
Q_DECLARE_METATYPE(N::Fuzzy::Extremely)
Q_DECLARE_METATYPE(N::Fuzzy::Not)
Q_DECLARE_METATYPE(N::Fuzzy::Seldom)
Q_DECLARE_METATYPE(N::Fuzzy::Somewhat)
Q_DECLARE_METATYPE(N::Fuzzy::Very)
Q_DECLARE_METATYPE(N::Fuzzy::Accumulated)
Q_DECLARE_METATYPE(N::Fuzzy::Bell)
Q_DECLARE_METATYPE(N::Fuzzy::Discrete)
Q_DECLARE_METATYPE(N::Fuzzy::Gaussian)
Q_DECLARE_METATYPE(N::Fuzzy::GaussianProduct)
Q_DECLARE_METATYPE(N::Fuzzy::PiShape)
Q_DECLARE_METATYPE(N::Fuzzy::Ramp)
Q_DECLARE_METATYPE(N::Fuzzy::Rectangle)
Q_DECLARE_METATYPE(N::Fuzzy::SShape)
Q_DECLARE_METATYPE(N::Fuzzy::Sigmoid)
Q_DECLARE_METATYPE(N::Fuzzy::SigmoidDifference)
Q_DECLARE_METATYPE(N::Fuzzy::SigmoidProduct)
Q_DECLARE_METATYPE(N::Fuzzy::Thresholded)
Q_DECLARE_METATYPE(N::Fuzzy::Trapezoid)
Q_DECLARE_METATYPE(N::Fuzzy::Triangle)
Q_DECLARE_METATYPE(N::Fuzzy::ZShape)
Q_DECLARE_METATYPE(N::Fuzzy::Variable)
Q_DECLARE_METATYPE(N::Fuzzy::InputVariable)
Q_DECLARE_METATYPE(N::Fuzzy::OutputVariable)
Q_DECLARE_METATYPE(N::Fuzzy::Infix)
Q_DECLARE_METATYPE(N::Fuzzy::RuleBlock)
Q_DECLARE_METATYPE(N::Fuzzy::TermFactory)
Q_DECLARE_METATYPE(N::Fuzzy::HedgeFactory)
Q_DECLARE_METATYPE(N::Fuzzy::SNormFactory)
Q_DECLARE_METATYPE(N::Fuzzy::TNormFactory)
Q_DECLARE_METATYPE(N::Fuzzy::DefuzzifierFactory)
Q_DECLARE_METATYPE(N::Fuzzy::Factory)
Q_DECLARE_METATYPE(N::Fuzzy::Engine)
Q_DECLARE_METATYPE(N::Fuzzy::MamdaniProposition)
Q_DECLARE_METATYPE(N::Fuzzy::MamdaniOperator)
Q_DECLARE_METATYPE(N::Fuzzy::MamdaniAntecedent)
Q_DECLARE_METATYPE(N::Fuzzy::MamdaniConsequent)
Q_DECLARE_METATYPE(N::Fuzzy::MamdaniRule)
Q_DECLARE_METATYPE(N::Fuzzy::CppExporter)
Q_DECLARE_METATYPE(N::Fuzzy::FclImporter)
Q_DECLARE_METATYPE(N::Fuzzy::FclExporter)
Q_DECLARE_METATYPE(N::Fuzzy::FisImporter)
Q_DECLARE_METATYPE(N::Fuzzy::FisExporter)

Q_DECLARE_INTERFACE(N::Fuzzy::Term,"com.neutrino.fuzzy.term")
Q_DECLARE_INTERFACE(N::Fuzzy::Operator,"com.neutrino.fuzzy.operator")
Q_DECLARE_INTERFACE(N::Fuzzy::SNorm,"com.neutrino.fuzzy.snorm")
Q_DECLARE_INTERFACE(N::Fuzzy::TNorm,"com.neutrino.fuzzy.tnorm")
Q_DECLARE_INTERFACE(N::Fuzzy::Antecedent,"com.neutrino.fuzzy.antecedent")
Q_DECLARE_INTERFACE(N::Fuzzy::Consequent,"com.neutrino.fuzzy.consequent")
Q_DECLARE_INTERFACE(N::Fuzzy::Defuzzifier,"com.neutrino.fuzzy.defuzzifier")
Q_DECLARE_INTERFACE(N::Fuzzy::Hedge,"com.neutrino.fuzzy.hedge")
Q_DECLARE_INTERFACE(N::Fuzzy::MamdaniExpression,"com.neutrino.fuzzy.expression")
Q_DECLARE_INTERFACE(N::Fuzzy::Importer,"com.neutrino.fuzzy.importer")
Q_DECLARE_INTERFACE(N::Fuzzy::Exporter,"com.neutrino.fuzzy.exporter")

QT_END_NAMESPACE

#endif
