#ifndef __itkRThetaToCartesianTransform_txx
#define __itkRThetaToCartesianTransform_txx

#include "itkRThetaToCartesianTransform.h"

#include "itkCartesianToRThetaTransform.h"

#include "vnl/vnl_math.h"

namespace itk
{

template < class TScalarType, unsigned int NDimensions >
RThetaToCartesianTransform< TScalarType, NDimensions >
::RThetaToCartesianTransform():
  Superclass( SpaceDimension, 5 ),
  m_RDirection( 0 ),
  m_ThetaDirection( 1 ),
  m_SpacingTheta( 0.0 )
{
  // Rmin invalid value to make sure it gets set
  this->m_Parameters[0] = -1.0;
  // Rmax invalid value to make suer it gets set
  this->m_Parameters[1] = -1.0;
}


template < class TScalarType, unsigned int NDimensions >
void
RThetaToCartesianTransform< TScalarType, NDimensions >
::SetThetaArray( const itk::Array< double >& thetaArray )
{
  // MaxAbsTheta
  this->m_Parameters[2] = thetaArray.inf_norm();

  // Thetamin
  this->m_Parameters[3] = thetaArray.min_value();

  if( this->m_Parameters[0] < 0.0 )
    {
    itkExceptionMacro( "SetRmin() must be called before SetThetaArray()." );
    }
  m_RmincosMaxAbsTheta = this->m_Parameters[0] * vcl_cos( this->m_Parameters[2] ); 

  if( this->m_Parameters[1] < 0.0 )
    {
    itkExceptionMacro( "SetRmax() must be called before SetThetaArray()." );
    }
  m_RmaxsinThetamin = this->m_Parameters[1] * vcl_sin( this->m_Parameters[3] );

  if( m_SpacingTheta == 0.0 )
    {
    itkExceptionMacro( "SetSpacingTheta() must be called before SetThetaArray()." );
    }

  // SpacingThetaOverDeltaTheta
  this->m_Parameters[4] = m_SpacingTheta / ( thetaArray[1] - thetaArray[0] ) ;
}


template < class TScalarType, unsigned int NDimensions >
typename RThetaToCartesianTransform< TScalarType, NDimensions>::OutputPointType
RThetaToCartesianTransform< TScalarType, NDimensions >
::TransformPoint( const InputPointType& inpoint ) const
{
  OutputPointType outpoint = inpoint;

  ScalarType theta = this->m_Parameters[3] + inpoint[m_ThetaDirection] / this->m_Parameters[4];
  ScalarType r     = this->m_Parameters[0] + inpoint[m_RDirection];

  outpoint[m_RDirection] = r * vcl_cos( theta );
  outpoint[m_ThetaDirection] = r * vcl_sin( theta );

  return outpoint;
}


template < class TScalarType, unsigned int NDimensions >
typename RThetaToCartesianTransform< TScalarType, NDimensions>::InverseTransformBasePointer
RThetaToCartesianTransform< TScalarType, NDimensions >
::GetInverseTransform() const
{
  typedef itk::CartesianToRThetaTransform< TScalarType, NDimensions > InverseType;
  typename InverseType::Pointer inverse = InverseType::New();

  inverse->SetRDirection( m_RDirection );
  inverse->SetThetaDirection( m_ThetaDirection );
  inverse->SetSpacingTheta( m_SpacingTheta );
  inverse->SetParameters( this->GetParameters() );

  return inverse.GetPointer();
}


}

#endif // __itkRThetaToCartesianTransform_txx
