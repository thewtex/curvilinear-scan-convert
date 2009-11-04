#ifndef __itkRThetaTransform_txx
#define __itkRThetaTransform_txx

#include "itkRThetaTransform.h"

#include "itkMetaDataDictionary.h"
#include "itkMetaDataObject.h"

namespace itk
{

template < class TScalarType, class TOutputImage >
RThetaTransform< TInputImage, TOutputImage >
::RThetaTransform():
  Superclass( SpaceDimension, 5 ),
  m_SpacingTheta( 0.0 )
{
}


}

#endif // __itkRThetaTransform_txx
