#ifndef __itkResampleRThetaToCartesianImageFilter_txx
#define __itkResampleRThetaToCartesianImageFilter_txx

#include "itkResampleRThetaToCartesianImageFilter.h"

#include "itkMetaDataObject.h"

#include "vnl/vnl_math.h"

namespace itk
{

template < class TInputImage, class TOutputImage, class TInterpolatorPrecision >
ResampleRThetaToCartesianImageFilter< TInputImage, TOutputImage, TInterpolatorPrecision >
::ResampleRThetaToCartesianImageFilter()
{
  m_ResamplingFilter = ResampleType::New();
  m_Transform = TransformType::New();
  m_ResamplingFilter->SetTransform( m_Transform );
}

template < class TInputImage, class TOutputImage, class TInterpolatorPrecision >
void
ResampleRThetaToCartesianImageFilter< TInputImage, TOutputImage, TInterpolatorPrecision >
::GenerateOutputInformation()
{
  typename InputImageType::ConstPointer  inputPtr  = this->GetInput();
  typename OutputImageType::Pointer      outputPtr = this->GetOutput();

  const unsigned int rDirection = m_Transform->GetRDirection();
  const unsigned int thetaDirection = m_Transform->GetThetaDirection();

  if ( !inputPtr || !outputPtr )
    {
    return;
    }

  typename InputImageType::SizeType size = inputPtr->GetLargestPossibleRegion().GetSize();
  typename InputImageType::SpacingType spacing = inputPtr->GetSpacing();

  // Rmin.
  const itk::MetaDataDictionary& dict = inputPtr->GetMetaDataDictionary();
  typedef const itk::MetaDataObject< std::string >* MetaStringType;
  typedef const itk::MetaDataObject< double >* MetaDoubleType;
  double Rmin;
  MetaDoubleType r = dynamic_cast< MetaDoubleType >( dict["Radius"] );
  MetaStringType rString = dynamic_cast< MetaStringType >( dict["RadiusString"] );
  if( r != NULL )
    {
    Rmin = r->GetMetaDataObjectValue();
    m_Transform->SetRmin( Rmin );
    }
  else if( rString != NULL )
    {
    istringstream iss( rString->GetMetaDataObjectValue() );
    iss >> Rmin;
    m_Transform->SetRmin( Rmin );
    }
  else
    {
    itkExceptionMacro( "Could not find Radius MetaDataDictionary value to perform RTheta transform." );
    }

  // Rmax.
  const double Rmax = Rmin + size[rDirection] * spacing[rDirection]; 
  m_Transform->SetRmax( Rmax );

  double spacingTheta = m_Transform->GetSpacingTheta();
  if( spacingTheta == 0.0 ) // has not been initialized
    {
    m_Transform->SetSpacingTheta( spacing[thetaDirection] );
    }
  else
    {
    spacing[thetaDirection] = spacingTheta;
    }

  // Theta.
  typedef const itk::MetaDataObject< itk::Array< double > >* MetaArrayType;
  MetaArrayType thetaArray = dynamic_cast< MetaArrayType >( dict["Theta"] );
  MetaStringType thetaArrayString = dynamic_cast< MetaStringType >( dict["ThetaString"] );
  if( thetaArray != NULL )
    {
    m_Transform->SetThetaArray( thetaArray->GetMetaDataObjectValue() );
    }
  else if( thetaArrayString != NULL ) 
    {
    std::string thetaString = thetaArrayString->GetMetaDataObjectValue() ;
    unsigned int alines = std::count( thetaString.begin(), thetaString.end(), ' ' );
    typedef itk::Array< double > ArrayType;
    double theta;
    ArrayType thetaArray( alines );
    istringstream iss;
    iss.str( thetaString );
    for( unsigned int i = 0; i < alines; i++ )
      {
      iss >> theta;
      thetaArray[i] = theta;
      }
    m_Transform->SetThetaArray( thetaArray );
    }
  else
    {
    itkExceptionMacro( "Could not find 'Theta' MetaDataDictionary entry to perform RTheta transform." );
    }

  typename OutputImageType::PointType origin;
  origin.Fill( 0.0 );
  origin[rDirection] = m_Transform->GetRmincosMaxAbsTheta();
  origin[thetaDirection] =  m_Transform->GetRmaxsinThetamin();
  m_ResamplingFilter->SetOutputOrigin( origin );

  m_ResamplingFilter->SetOutputSpacing( spacing );

  size[rDirection] = static_cast< unsigned int >( vcl_ceil ( ( Rmax - m_Transform->GetRmincosMaxAbsTheta() ) / spacing[rDirection] ) );
  size[thetaDirection] = static_cast< unsigned int >( vcl_ceil( vcl_abs(2.0 * m_Transform->GetRmaxsinThetamin() / spacing[thetaDirection]) ) );
  m_ResamplingFilter->SetSize( size );

  m_ResamplingFilter->SetInput( inputPtr );
  m_ResamplingFilter->UpdateOutputInformation();
  outputPtr->CopyInformation( m_ResamplingFilter->GetOutput() );
}

template < class TInputImage, class TOutputImage, class TInterpolatorPrecision >
void
ResampleRThetaToCartesianImageFilter< TInputImage, TOutputImage, TInterpolatorPrecision >
::GenerateInputRequestedRegion()
{
  this->m_ResamplingFilter->SetInput( this->GetInput() );
  this->m_ResamplingFilter->GenerateInputRequestedRegion();
}

template < class TInputImage, class TOutputImage, class TInterpolatorPrecision >
void
ResampleRThetaToCartesianImageFilter< TInputImage, TOutputImage, TInterpolatorPrecision >
::GenerateData()
{
  typename InputImageType::ConstPointer  inputPtr  = this->GetInput();
  typename OutputImageType::Pointer      outputPtr = this->GetOutput();

  if ( !inputPtr || !outputPtr )
    {
    return;
    }

  m_ResamplingFilter->SetInput( inputPtr );
  m_ResamplingFilter->GraftOutput( outputPtr );
  m_ResamplingFilter->GetOutput()->UpdateOutputData();
  this->GraftOutput( m_ResamplingFilter->GetOutput() );
}

} // namespace itk

#endif // __itkResampleRThetaToCartesianImageFilter_txx
