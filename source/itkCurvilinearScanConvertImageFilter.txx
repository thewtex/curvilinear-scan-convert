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
  m_Direction(0)
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
  const MetaDataDictionary& dict = this->GetMetaDataDictionary();
  if( !dict.HasKey( "Radius" ) )
    {
    itkExceptionMacro( "Could not find 'Radius' MetaDataDictionary entry." );
    }
  typedef itk::MetaDataObject< double > MetaDataDoubleType;
  const MetaDataObjectBase* radiusPtr = dict["Radius"];
  const double radius = (*( dynamic_cast< const MetaDataDoubleType* >( radiusPtr ))).GetMetaDataObjectValue();
  std::cout << "The radius is : " << radius << std::endl;
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
