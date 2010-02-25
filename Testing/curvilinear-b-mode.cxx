/**
 * @file curvilinear-b-mode.cxx
 * @brief Test VisualSonics scan conversion by making a B-Mode.
 * @author Matthew McCormick (thewtex) <matt@mmmccormick.com>
 * @date 2009-11-03
 */

#include <iostream>
using namespace std;

#include "itkArray.h"
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkMetaDataDictionary.h"
#include "itkMetaDataObject.h"
#include "itkNearestNeighborInterpolateImageFunction.h"
#include "itkResampleImageFilter.h"


#include "itkBModeImageFilter.h"
#include "itkVisualSonicsImageIOFactory.h"

#include "itkRThetaTransform.h"

int main( int argc, char* argv[] )
{
  // usage: vs-convert-b-mode input.rdi output.mhd
  if( argc != 3 )
    return EXIT_FAILURE;

  itk::VisualSonicsImageIOFactory::RegisterOneFactory();

  typedef signed short InputPixelType;
  typedef unsigned short OutputPixelType;
  const unsigned int Dimension = 3;
  typedef itk::Image< InputPixelType, Dimension > InputImageType;
  typedef itk::Image< OutputPixelType, Dimension > OutputImageType;

  typedef itk::ImageFileReader< InputImageType > ReaderType;
  typedef itk::BModeImageFilter< InputImageType, OutputImageType > BModeType;
  typedef itk::ResampleImageFilter< OutputImageType, OutputImageType > ResampleType;
  typedef itk::RThetaTransform< double, Dimension > ScanConvertType;
  typedef itk::NearestNeighborInterpolateImageFunction< OutputImageType, double >  InterpType;
  typedef itk::ImageFileWriter< OutputImageType > WriterType;

  try
    {
    ReaderType::Pointer reader = ReaderType::New();
    BModeType::Pointer  bmode  = BModeType::New();
    ResampleType::Pointer resample = ResampleType::New();
    ScanConvertType::Pointer scanConvert = ScanConvertType::New();
    InterpType::Pointer interp = InterpType::New();
    WriterType::Pointer writer = WriterType::New();

    bmode->SetInput( reader->GetOutput() );
    resample->SetInput( bmode->GetOutput() );
    resample->SetNumberOfThreads( 1 );

    reader->SetFileName( argv[1] );
    writer->SetFileName( argv[2] );

    reader->UpdateOutputInformation();
    reader->GetOutput()->Print(cout);

    const itk::MetaDataDictionary& dict = reader->GetMetaDataDictionary();

    typedef const itk::MetaDataObject< double >* MetaDoubleType;
    MetaDoubleType r = dynamic_cast< MetaDoubleType >( dict["Radius"] );
    if( r == NULL )
      {
      cerr << "Could not find 'Radius' MetaDataDictionary entry." << std::endl;
      return EXIT_FAILURE;
      }
    scanConvert->SetRmin( r->GetMetaDataObjectValue() );

    const unsigned int RDirection = 0;
    scanConvert->SetRDirection( RDirection );

    const unsigned int ThetaDirection = 1;
    scanConvert->SetThetaDirection( ThetaDirection );

    InputImageType::SpacingType spacing = reader->GetOutput()->GetSpacing();
    InputImageType::SizeType size = reader->GetOutput()->GetLargestPossibleRegion().GetSize();

    const double Rmax = r->GetMetaDataObjectValue() + size[RDirection] * spacing[RDirection]; 
    scanConvert->SetRmax( Rmax );

    scanConvert->SetSpacingTheta( spacing[ThetaDirection] );

    typedef const itk::MetaDataObject< itk::Array< double > >* MetaArrayType;
    MetaArrayType thetaArray = dynamic_cast< MetaArrayType >( dict["Theta"] );
    if( thetaArray == NULL )
      {
      cerr << "Could not find 'Theta' MetaDataDictionary entry." << std::endl;
      return EXIT_FAILURE;
      }
    scanConvert->SetThetaArray( thetaArray->GetMetaDataObjectValue() );

    resample->SetTransform( scanConvert );
    resample->SetInterpolator( interp );
    resample->SetDefaultPixelValue( 0 );

    OutputImageType::PointType origin;
    origin[RDirection] = scanConvert->GetRmincosMaxAbsTheta();
    origin[ThetaDirection] =  scanConvert->GetRmaxsinThetamin();
    origin[2] = 0.0;
    resample->SetOutputOrigin( origin );

    spacing[RDirection] = spacing[ThetaDirection];
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
