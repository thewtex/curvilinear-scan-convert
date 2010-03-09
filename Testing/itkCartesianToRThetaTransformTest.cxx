/**
 * @file curvilinear-b-mode.cxx
 * @brief Test VisualSonics scan conversion by making a B-Mode.
 * @author Matthew McCormick (thewtex) <matt@mmmccormick.com>
 * @date 2009-11-03
 */

#include <iostream>
#include <sstream>
using namespace std;

#include "itkArray.h"
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkMetaDataDictionary.h"
#include "itkMetaDataObject.h"
#include "itkResampleImageFilter.h"

#include "itkCartesianToRThetaTransform.h"

int main( int argc, char* argv[] )
{
  // usage: vs-convert-b-mode input.rdi output.mhd
  if( argc != 3 )
    return EXIT_FAILURE;

  typedef signed short InputPixelType;
  typedef signed short OutputPixelType;
  const unsigned int Dimension = 3;
  typedef itk::Image< InputPixelType, Dimension > InputImageType;
  typedef itk::Image< OutputPixelType, Dimension > OutputImageType;

  typedef itk::ImageFileReader< InputImageType > ReaderType;
  typedef itk::ResampleImageFilter< OutputImageType, OutputImageType, float > ResampleType;
  typedef itk::CartesianToRThetaTransform< float, Dimension > ScanConvertType;
  typedef itk::ImageFileWriter< OutputImageType > WriterType;

  try
    {
    ReaderType::Pointer reader = ReaderType::New();
    ResampleType::Pointer resample = ResampleType::New();
    ScanConvertType::Pointer scanConvert = ScanConvertType::New();
    WriterType::Pointer writer = WriterType::New();

    resample->SetInput( reader->GetOutput() );

    reader->SetFileName( argv[1] );
    writer->SetFileName( argv[2] );

    reader->UpdateOutputInformation();
    reader->GetOutput()->Print(cout);

    const itk::MetaDataDictionary& dict = reader->GetMetaDataDictionary();

    typedef const itk::MetaDataObject< std::string >* MetaStringType;
    MetaStringType r = dynamic_cast< MetaStringType >( dict["RadiusString"] );
    if( r == NULL )
      {
      cerr << "Could not find 'RadiusString' MetaDataDictionary entry." << std::endl;
      return EXIT_FAILURE;
      }
    double rMin;
    istringstream iss( r->GetMetaDataObjectValue() );
    iss >> rMin;
    scanConvert->SetRmin( rMin );

    const unsigned int RDirection = 0;
    scanConvert->SetRDirection( RDirection );

    const unsigned int ThetaDirection = 1;
    scanConvert->SetThetaDirection( ThetaDirection );

    InputImageType::SpacingType spacing = reader->GetOutput()->GetSpacing();
    InputImageType::SizeType size = reader->GetOutput()->GetLargestPossibleRegion().GetSize();

    const double Rmax = rMin + size[RDirection] * spacing[RDirection]; 
    scanConvert->SetRmax( Rmax );

    scanConvert->SetSpacingTheta( spacing[ThetaDirection] );

    MetaStringType thetaArrayMeta = dynamic_cast< MetaStringType >( dict["ThetaString"] );
    if( thetaArrayMeta == NULL )
      {
      cerr << "Could not find 'ThetaString' MetaDataDictionary entry." << std::endl;
      return EXIT_FAILURE;
      }
    std::string thetaString = thetaArrayMeta->GetMetaDataObjectValue() ;
    unsigned int alines = std::count( thetaString.begin(), thetaString.end(), ' ' );
    typedef itk::Array< double > ArrayType;
    double theta;
    ArrayType thetaArray( alines );
    iss.clear();
    iss.str( thetaString );
    for( unsigned int i = 0; i < alines; i++ )
      {
      iss >> theta;
      thetaArray[i] = theta;
      }
    scanConvert->SetThetaArray( thetaArray );

    resample->SetTransform( scanConvert );
    resample->SetDefaultPixelValue( 0 );

    OutputImageType::PointType origin;
    origin[RDirection] = scanConvert->GetRmincosMaxAbsTheta();
    origin[ThetaDirection] =  scanConvert->GetRmaxsinThetamin();
    origin[2] = 0.0;
    resample->SetOutputOrigin( origin );

    resample->SetOutputSpacing( spacing );

    size[RDirection] = static_cast< unsigned int >( vcl_ceil ( ( Rmax - scanConvert->GetRmincosMaxAbsTheta() ) / spacing[RDirection] ) );
    size[ThetaDirection] = static_cast< unsigned int >( vcl_ceil( vcl_abs(2.0 * scanConvert->GetRmaxsinThetamin() / spacing[ThetaDirection]) ) );
    resample->SetSize( size );

    writer->SetInput( resample->GetOutput() );
    writer->SetNumberOfStreamDivisions( 20 );
    writer->Update();
    }
  catch ( itk::ExceptionObject& e )
    {
    cerr << "Error: " << e << endl;
    return EXIT_FAILURE;
    }
  catch (std::exception& e)
    {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
    }
  return EXIT_SUCCESS;
}
