/** 
 * @file itkRThetaTransform.h
 * @brief Scan convert an ultrasound image from a curvilinear array.
 * @author Matthew McCormick (thewtex) <matt@mmmccormick.com>
 * @date 2009-11-03
 */

#ifndef __itkRThetaTransform_h
#define __itkRThetaTransform_h

#include "itkTransform.h"

namespace itk
{

/** @brief Transform for an image that was actually acquired in (R, Theta)
 * space.  E.g., scan convert an ultrasound image from a curvilinear array.
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
 * Parameters include:
 *
 *  Rmin
 *    The distance from the center of rotation to the first sample in the
 *    RDirection. type: double
 *
 *  Rmax
 *    Distance in physical units to the last point in the RDirection.  Rmin +
 *    size[RDirection] * spacing[RDirection]
 *
 *  MaxAbsTheta
 *    Maximum absolute value of all angles.  Theta is in radians.
 *
 *  Thetamin
 *    Minimum angle ( angle of the first line );
 *
 *  SpacingThetaOverDeltaTheta
 *    Since the input image was acually in (R,Theta) space, a spacing had to be
 *    assumed in the Theta direction to make the image.  This is that spacing
 *    divided by the step in angle between lines in the theta direction.
 *
 */

template < class TScalarType, unsigned int NDimensions=3 >
class ITK_EXPORT RThetaTransform :
  public Transform< TScalarType, NDimensions, NDimensions >
{
public:
  /** Standard "Self" typedef.   */
  typedef RThetaTransform Self;

  /** Standard super class typedef support. */
  typedef Transform< TScalarType, NDimensions, NDimensions > Superclass;

  /** Smart pointer typedef support  */
  typedef SmartPointer< Self > Pointer;
  typedef SmartPointer< const Self > ConstPointer;

  /** Run-time type information (and related methods) */
  itkTypeMacro( RThetaTransform, Transform );
  
  /** Method for creation through the object factory. */
  itkNewMacro( Self );

  /** Type of the input parameters. */
  typedef  TScalarType     ScalarType;

  /** Standard parameters container. */
  typedef typename Superclass::ParametersType ParametersType;

  /** Standard coordinate point type for this class */
  typedef Point<TScalarType,
                itkGetStaticConstMacro(InputSpaceDimension)> InputPointType;
  typedef Point<TScalarType,
                itkGetStaticConstMacro(OutputSpaceDimension)> OutputPointType;

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

 /**  Rmin
 *    The distance from the center of rotation to the first sample in the
 *    RDirection. type: double */
  virtual void SetRmin( const double& Rmin )
    { 
    m_Parameters[0] = Rmin;
    this->Modified();
    }

 /**  Rmax
 *    Distance in physical units to the last point in the RDirection.  Rmin +
 *    size[RDirection] * spacing[RDirection] */
  virtual void SetRMax( const double& Rmax )
    {
    m_Parameters[1] = Rmax;
    this->Modified();
    }

  /** SpacingTheta
   *	The spacing in the ThetaDirection.  This must be set before ThetaArray.
   *	*/
  itkSetMacro( SpacingTheta, double );

  /** ThetaArray
   *	An itk::Array<double> who elements correspond to the angle in radians of
   *	each element in the ThetaDirection.  ThetaArray.size() should be the
   *	same as the size of the image in the ThetaDirection.  The MaxAbsTheta,
   *	Thetamin, and SpacingThetaOverDeltaTheta Parameters are defined after
   *	calling this method.  SetSpacingTheta() must be called before this. */
  virtual void SetThetaArray( const itk::Array< double >& theta );

protected:
  RThetaTransform();
  ~RThetaTransform() {}

  void PrintSelf( std::ostream& os, Indent indent ) const;

  double m_SpacingTheta;

private:
  RThetaTransform( const Self& ); // purposely not implemented
  void operator=( const Self& ); // purposely not implemented


};
} // end namesplace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkRThetaTransform.txx"
#endif

#endif // __itkRThetaTransform_h
