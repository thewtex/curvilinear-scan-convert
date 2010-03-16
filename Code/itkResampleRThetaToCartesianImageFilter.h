#ifndef __itkResampleRThetaToCartesianImageFilter_h
#define __itkResampleRThetaToCartesianImageFilter_h

#include "itkImageToImageFilter.h"

#include "itkCartesianToRThetaTransform.h"
#include "itkStreamingResampleImageFilter.h"

namespace itk
{

/** @brief Transform for an image that was actually acquired in (R, Theta)
 * space.  E.g., scan convert an ultrasound image from a curvilinear array.
 * 
 *  Valid values of theta can range from -pi/2 to pi/2.
 *
 *  Properties:
 *  RDirection
 *    The direction in the input image assumed to correspond to the radial
 *    component.  Use SetRDirection() to specify it.
 *
 *  ThetaDirection
 *    The direction in the input image assumed to correspond to the angular
 *    component.  Use SetThetaDirection() to specify it.
 *
 * The input should have MetaDataDictionary entries for "Radius" and
 * "RadiousString" and "Theta" or "ThetaString".  "Radius" is of type double
 * and contains the distance in the RDirection to the first sample.
 * "RadiusString" is a string representation of the value.  "Theta" is an
 * itk::Array<double> containing the angles for every value in the
 * ThetaDirection in radians.  "ThetaString" is a a string representation of the
 * values containing the floating point value followed by a space for each
 * value.
 */

template < class TInputImage, class TOutputImage, class TInterpolatorPrecision = double >
class ITK_EXPORT ResampleRThetaToCartesianImageFilter :
  public ImageToImageFilter< TInputImage, TOutputImage >
{
public:
  /** Standard "Self" typedef.   */
  typedef ResampleRThetaToCartesianImageFilter Self;

  /** Standard super class typedef support. */
  typedef ImageToImageFilter< TInputImage, TOutputImage > Superclass;

  /** Smart pointer typedef support  */
  typedef SmartPointer< Self > Pointer;
  typedef SmartPointer< const Self > ConstPointer;

  /**Typedefs from the superclass */
  typedef typename Superclass::InputImageType  InputImageType;
  typedef typename Superclass::OutputImageType OutputImageType;

  /** Run-time type information (and related methods) */
  itkTypeMacro( ResampleRThetaToCartesianImageFilter, ImageToImageFilter );
  
  /** Method for creation through the object factory. */
  itkNewMacro( Self );

  /** Dimension of the image. */
  itkStaticConstMacro( ImageDimension, unsigned int, TInputImage::ImageDimension );

  /** The direction in the input image that corresponds to the radial component.
   * */
  virtual void SetRDirection( unsigned int direction )
    {
    m_Transform->SetRDirection( direction );
    this->Modified();
    }

  virtual unsigned int GetRDirection() const
    {
    return m_Transform->GetRDirection();
    }

  /** The direction in the input image that corresponds to the angular (theta)
   * component. */
  virtual void SetThetaDirection( unsigned int direction )
    {
    m_Transform->SetThetaDirection( direction );
    this->Modified();
    }

  virtual unsigned int GetThetaDirection() const
    {
    return m_Transform->GetThetaDirection();
    }

  /** SpacingTheta
   *	The output spacing in the ThetaDirection.  If not set, twice the spacing in the
   *	ThetaDirection from the input is used.
   *	*/
  itkSetMacro( OutputSpacingTheta, double );
  itkGetConstMacro( OutputSpacingTheta, double );

  virtual void SetDefaultPixelValue( typename TOutputImage::PixelType defaultValue )
    {
    m_ResamplingFilter->SetDefaultPixelValue( defaultValue );
    this->Modified();
    }

protected:
  ResampleRThetaToCartesianImageFilter();
  ~ResampleRThetaToCartesianImageFilter() {}

  /** Standard process object method. */
  virtual void GenerateData();
  virtual void GenerateOutputInformation();
  virtual void GenerateInputRequestedRegion();

  /** Component filters. */
  typedef itk::StreamingResampleImageFilter< InputImageType, OutputImageType, TInterpolatorPrecision > ResampleType;
  typedef itk::CartesianToRThetaTransform< TInterpolatorPrecision, ImageDimension > TransformType;

private:
  ResampleRThetaToCartesianImageFilter( const Self& ); // purposely not implemented
  void operator=( const Self& ); // purposely not implemented

  typename ResampleType::Pointer  m_ResamplingFilter;
  typename TransformType::Pointer m_Transform;

  double m_OutputSpacingTheta;
};
} // end namesplace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkResampleRThetaToCartesianImageFilter.txx"
#endif

#endif // __itkResampleRThetaToCartesianImageFilter_h
