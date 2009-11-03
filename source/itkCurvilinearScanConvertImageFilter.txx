#ifndef __itkCurvilinearScanConvertImageFilter_txx
#define __itkCurvilinearScanConvertImageFilter_txx

#include "itkCurvilinearScanConvertImageFilter.h"

#include "itkMetaDataDictionary.h"
#include "itkMetaDataObject.h"

namespace itk
{

template < class TInputImage, class TOutputImage >
CurvilinearScanConvertImageFilter< TInputImage, TOutputImage >
::CurvilinearScanConvertImageFilter():
  m_Direction(1)
{
}


template < class TInputImage, class TOutputImage >
void
CurvilinearScanConvertImageFilter< TInputImage, TOutputImage >
::PrintSelf( std::ostream& os, Indent indent ) const
{
  //! @todo define me
}


template < class TInputImage, class TOutputImage >
void
CurvilinearScanConvertImageFilter< TInputImage, TOutputImage >
::GenerateOutputInformation()
{
  this->Superclass::GenerateOutputInformation();

  const MetaDataDictionary& dict = this->GetMetaDataDictionary();
  if( !dict.HasKey( "Radius" ) )
    {
    itkExceptionMacro( "Could not find 'Radius' MetaDataDictionary entry." );
    }
  const double radius = (*( dynamic_cast< const itk::MetaDataObject< double >* >( dict["Radius"] ))).GetMetaDataObjectValue();

  if( !dict.HasKey( "Theta" ) )
    {
    itkExceptionMacro( "Could not find 'Theta' MetaDataDictionary entry." );
    }
  const std::vector< double >& theta = (*( dynamic_cast< const itk::MetaDataObject< std::vector< double > >* >( dict["Theta"] ))).GetMetaDataObjectValue();
  
  unsigned int numLines = this->GetInput()->GetLargestPossibleRegion().GetSize()[this->m_Direction];
  for( unsigned int i = 0; i < numLines; i++ )
    std::cout << theta[i] << std::endl;
  
  //! @todo define me
}


template < class TInputImage, class TOutputImage >
void
CurvilinearScanConvertImageFilter< TInputImage, TOutputImage >
::GenerateInputRequestedRegion()
{
  //! @todo define me
}

template < class TInputImage, class TOutputImage >
void
CurvilinearScanConvertImageFilter< TInputImage, TOutputImage >
::GenerateData()
{
  //! @todo define me
}

}

#endif // __itkCurvilinearScanConvertImageFilter_txx
