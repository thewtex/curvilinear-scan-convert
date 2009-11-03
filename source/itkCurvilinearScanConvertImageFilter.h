/** 
 * @file itkCurvilinearScanConvertImageFilter.h
 * @brief Scan convert an ultrasound image from a curvilinear array.
 * @author Matthew McCormick (thewtex) <matt@mmmccormick.com>
 * @date 2009-11-03
 */

#ifndef __itkCurvilinearScanConvertImageFilter_h
#define __itkCurvilinearScanConvertImageFilter_h

#include "itkImageToImageFilter.h"

namespace itk
{

/** @brief Scan convert an ultrasound image from a curvilinear array.
 * 
 *Requires that the MetaDataDictionary contains entries for:
 *
 *  Radius
 *    The distance from the center of rotation to the first sample. type: double
 *
 *  Theta
 *    A vector containing the angles in radians of each scan line.  The length of
 *    this vector should be the same as the extent in the Direction property.
 *    type: std::vector< double >
 */

template < class TInputImage, class TOutputImage >
class ITK_EXPORT CurvilinearScanConvertImageFilter :
  public ImageToImageFilter< TInputImage, TOutputImage >
{
public:
  /** Standard "Self" typedef.   */
  typedef CurvilinearScanConvertImageFilter Self;

  /** The type of input image.   */
  typedef TInputImage InputImageType;

  /** Dimension of the input and output images. */
  itkStaticConstMacro ( ImageDimension, unsigned int,
                       TInputImage::ImageDimension );
  
  /** Typedef support for the input image scalar value type. */
  typedef typename InputImageType::PixelType InputPixelType;

  /** The type of output image.   */
  typedef TOutputImage OutputImageType;

  /** Typedef support for the output image scalar value type. */
  typedef typename OutputImageType::PixelType OutputPixelType;

  /** Other convenient typedefs   */
  typedef typename InputImageType::RegionType InputRegionType;
  typedef typename InputImageType::SizeType   InputSizeType;
  typedef typename InputImageType::IndexType  InputIndexType;
  
  /** Standard super class typedef support. */
  typedef ImageToImageFilter< InputImageType, OutputImageType > Superclass;


  /** Smart pointer typedef support  */
  typedef SmartPointer< Self > Pointer;
  typedef SmartPointer< const Self > ConstPointer;

  /** Run-time type information (and related methods) */
  itkTypeMacro( CurvilinearScanConvertImageFilter, ImageToImageFilter );
  
  /** Method for creation through the object factory. */
  itkNewMacro( Self );

  /** Get the direction in which the filter is to be applied. */
  itkGetMacro(Direction, unsigned int);

  /** Set the direction in which the filter is to be applied. */
  itkSetMacro(Direction, unsigned int);

protected:
  CurvilinearScanConvertImageFilter();
  ~CurvilinearScanConvertImageFilter() {}

  void PrintSelf( std::ostream& os, Indent indent ) const;

  /** Standard process object method. */
  virtual void GenerateOutputInformation(void);

  /** Standard process object method. */
  virtual void GenerateInputRequestedRegion();

  /** Standard process object method. */
  virtual void GenerateData();

  /** Direction in which the filter is to be applied.
   * This should be in the range [0,ImageDimension-1]. */
  unsigned int m_Direction;

private:
  CurvilinearScanConvertImageFilter( const Self& ); // purposely not implemented
  void operator=( const Self& ); // purposely not implemented


};
} // end namesplace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkCurvilinearScanConvertImageFilter.txx"
#endif

#endif // __itkCurvilinearScanConvertImageFilter_h
