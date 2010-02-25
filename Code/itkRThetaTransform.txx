#ifndef __itkRThetaTransform_txx
#define __itkRThetaTransform_txx

#include "itkRThetaTransform.h"

#include "vnl/vnl_math.h"

namespace itk
{

template < class TScalarType, unsigned int NDimensions >
RThetaTransform< TScalarType, NDimensions >
::RThetaTransform():
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
RThetaTransform< TScalarType, NDimensions >
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
typename RThetaTransform< TScalarType, NDimensions>::OutputPointType
RThetaTransform< TScalarType, NDimensions >
::TransformPoint( const InputPointType& inpoint ) const
{
  OutputPointType outpoint = inpoint;

  ScalarType theta = vcl_atan(
    inpoint[m_ThetaDirection] / 
    inpoint[m_RDirection]
  );

  ScalarType r = vcl_sqrt( 
    vnl_math_sqr( inpoint[m_RDirection] ) +
    vnl_math_sqr( inpoint[m_ThetaDirection] )
  );

  outpoint[m_RDirection] = r - this->m_Parameters[0];
  outpoint[m_ThetaDirection] = ( theta - this->m_Parameters[3] ) * this->m_Parameters[4] ;

  return outpoint;
}


}

#endif // __itkRThetaTransform_txx
