#ifndef __itkCurvilinearScanConvertImageFilter_txx
#define __itkCurvilinearScanConvertImageFilter_txx

#include "itkCurvilinearScanConvertImageFilter.h"

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
