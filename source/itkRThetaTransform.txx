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
  m_SpacingTheta( 0.0 ),
  m_RmaxsinMaxAbsTheta( -1.0 ),
  m_RmincosMaxAbsTheta( -1.0 )
{
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

  if( m_RmincosMaxAbsTheta < 0.0 )
    {
    itkExceptionMacro( "SetRmin() must be called before SetThetaArray()." );
    }
  m_RmincosMaxAbsTheta = this->m_Parameters[1] * vcl_sin( this->m_Parameters[2] ); 

  if( m_RmaxsinMaxAbsTheta < 0.0 )
    {
    itkExceptionMacro( "SetRmax() must be called before SetThetaArray()." );
    }
  m_RmaxsinMaxAbsTheta = this->m_Parameters[0] * vcl_cos( this->m_Parameters[2] );

  if( m_SpacingTheta == 0.0 )
    {
    itkExceptionMacro( "SetSpacingTheta() must be called before SetThetaArray." );
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
    ( inpoint[m_RDirection] - m_RmaxsinMaxAbsTheta ) / 
    ( inpoint[m_RDirection] + m_RmincosMaxAbsTheta )
  );

  ScalarType r = vcl_sqrt( 
    vnl_math_sqr( m_RmincosMaxAbsTheta + inpoint[m_RDirection] ) +
    vnl_math_sqr( inpoint[m_RDirection] - m_RmaxsinMaxAbsTheta )
  );

  outpoint[m_RDirection] = r - this->m_Parameters[0];
  outpoint[m_ThetaDirection] = ( theta - this->m_Parameters[3] ) * this->m_Parameters[4] ;

  return outpoint;
}


}

#endif // __itkRThetaTransform_txx
