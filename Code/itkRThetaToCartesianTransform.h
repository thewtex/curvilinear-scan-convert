/** 
 * @file itkRThetaToCartesianTransform.h
 * @brief Scan convert an ultrasound image from a curvilinear array.
 * @author Matthew McCormick (thewtex) <matt@mmmccormick.com>
 * @date 2009-11-03
 */

#ifndef __itkRThetaToCartesianTransform_h
#define __itkRThetaToCartesianTransform_h

#include "itkTransform.h"

namespace itk
{

/** @brief Transform to R-Theta space (radius-angle) into Cartesian Space.
 * E.g., scan convert an ultrasound image from a curvilinear array.
 * 
 *  Valid values of theta can range from -pi/2 to pi/2.
 *
 *  Properties:
 *  RDirection
 *    The direction in the input image assumed to correspond to the radial
 *    component.
 *
 *  ThetaDirection
 *    The direction in the input image assumed to correspond to the angular
 *    component.
 *
 *  Rmin
 *    The distance from the center of rotation to the first sample in the
 *    RDirection. type: double
 *
 *  Theta
 *    A list of angles that every sample in the theta direction was collected
 *    at.  Should be equally spaced and in radians.
 *
 */

template < class TScalarType, unsigned int NDimensions=3 >
class ITK_EXPORT RThetaToCartesianTransform :
  public Transform< TScalarType, NDimensions, NDimensions >
{
public:
  /** Standard "Self" typedef.   */
  typedef RThetaToCartesianTransform Self;

  /** Standard super class typedef support. */
  typedef Transform< TScalarType, NDimensions, NDimensions > Superclass;

  /** Smart pointer typedef support  */
  typedef SmartPointer< Self > Pointer;
  typedef SmartPointer< const Self > ConstPointer;

  /** Run-time type information (and related methods) */
  itkTypeMacro( RThetaToCartesianTransform, Transform );
  
  /** Method for creation through the object factory. */
  itkNewMacro( Self );

  /** Dimension of the domain space. */
  itkStaticConstMacro(SpaceDimension, unsigned int, NDimensions);

  /** Type of the input parameters. */
  typedef  TScalarType     ScalarType;

  /** Standard parameters container. */
  typedef typename Superclass::ParametersType ParametersType;

  /** Standard coordinate point type for this class */
  typedef Point<TScalarType,
                itkGetStaticConstMacro(SpaceDimension)> InputPointType;
  typedef Point<TScalarType,
                itkGetStaticConstMacro(SpaceDimension)> OutputPointType;

  /** Standard vector type for this class. */
  typedef Vector<TScalarType,
                 itkGetStaticConstMacro(SpaceDimension)> InputVectorType;
  typedef Vector<TScalarType,
                 itkGetStaticConstMacro(SpaceDimension)> OutputVectorType;

  /** Standard covariant vector type for this class. */
  typedef CovariantVector<TScalarType,
             itkGetStaticConstMacro(SpaceDimension)> InputCovariantVectorType;
  typedef CovariantVector<TScalarType,
            itkGetStaticConstMacro(SpaceDimension)> OutputCovariantVectorType;
  
  /** Standard vnl_vector type for this class. */
  typedef vnl_vector_fixed<TScalarType,
                   itkGetStaticConstMacro(SpaceDimension)> InputVnlVectorType;
  typedef vnl_vector_fixed<TScalarType,
                  itkGetStaticConstMacro(SpaceDimension)> OutputVnlVectorType;
  
  /**  Method to transform a point. */
  virtual OutputPointType TransformPoint(const InputPointType  &point ) const;

  /** Method to transform a vector - 
   *  not applicable for this type of transform. */
  virtual OutputVectorType TransformVector(const InputVectorType &) const
    { 
    itkExceptionMacro(<< "Method not applicable for deformable transform." );
    return OutputVectorType(); 
    }

  /** Method to transform a vnl_vector - 
   *  not applicable for this type of transform */
  virtual OutputVnlVectorType TransformVector(const InputVnlVectorType &) const
    { 
    itkExceptionMacro(<< "Method not applicable for deformable transform. ");
    return OutputVnlVectorType(); 
    }

  /** Method to transform a CovariantVector - 
   *  not applicable for this type of transform */
  virtual OutputCovariantVectorType TransformCovariantVector(
    const InputCovariantVectorType &) const
    { 
    itkExceptionMacro(<< "Method not applicable for deformable transfrom. ");
    return OutputCovariantVectorType(); 
    } 

  /** Indicates that this transform is linear. That is, given two
   * points P and Q, and scalar coefficients a and b, then
   *
   *           T( a*P + b*Q ) = a * T(P) + b * T(Q)
   */
  virtual bool IsLinear() const { return false; }

   /** Base inverse transform type. This type should not be changed to the
    * concrete inverse transform type or inheritance would be lost.*/
  typedef typename Superclass::InverseTransformBaseType InverseTransformBaseType;
  typedef typename InverseTransformBaseType::Pointer    InverseTransformBasePointer;

  /** Return an inverse of this transform. */
  virtual InverseTransformBasePointer GetInverseTransform() const; 

  /** The direction in the input image that corresponds to the radial component.
   * */
  itkSetMacro( RDirection, unsigned int );
  itkGetConstMacro( RDirection, unsigned int );

  /** The direction in the input image that corresponds to the angular (theta)
   * component. */
  itkSetMacro( ThetaDirection, unsigned int );
  itkGetConstMacro( ThetaDirection, unsigned int );

 /**  Rmin
 *    The distance from the center of rotation to the first sample in the
 *    RDirection. type: double */
  virtual void SetRmin( const double& Rmin )
    { 
    this->m_Parameters[0] = Rmin;
    this->Modified();
    }

 /**  Rmax
 *    Distance in physical units to the last point in the RDirection.  Rmin +
 *    size[RDirection] * spacing[RDirection] */
  virtual void SetRmax( const double& Rmax )
    {
    this->m_Parameters[1] = Rmax;
    this->Modified();
    }

  /** SpacingTheta
   *	The assumed spacing in the ThetaDirection.  This must be set before ThetaArray.  Note that this value does not have a meaningful physical interpretation.
   *	*/
  itkSetMacro( SpacingTheta, double );
  itkGetConstMacro( SpacingTheta, double );

  /** ThetaArray
   *	An itk::Array<double> who elements correspond to the angle in radians of
   *	each element in the ThetaDirection.  ThetaArray.size() should be the
   *	same as the size of the image in the ThetaDirection.  The MaxAbsTheta,
   *	Thetamin, and SpacingThetaOverDeltaTheta Parameters are defined after
   *	calling this method.  SetSpacingTheta() and SetRmin() SetRmax() must be called before this. */
  virtual void SetThetaArray( const itk::Array< double >& theta );

protected:
  RThetaToCartesianTransform();
  ~RThetaToCartesianTransform() {}

  unsigned int m_RDirection;
  unsigned int m_ThetaDirection;
  double m_SpacingTheta;

  ScalarType m_RmaxsinThetamin;
  ScalarType m_RmincosMaxAbsTheta;

private:
  RThetaToCartesianTransform( const Self& ); // purposely not implemented
  void operator=( const Self& ); // purposely not implemented

};

} // end namesplace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkRThetaToCartesianTransform.txx"
#endif

#endif // __itkRThetaToCartesianTransform_h
