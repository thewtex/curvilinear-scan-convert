/**
 * @file curvilinear-b-mode.cxx
 * @brief Test VisualSonics scan conversion.
 * @author Matthew McCormick (thewtex) <matt@mmmccormick.com>
 * @date 2009-11-03
 */

#include <iostream>
#include <sstream>
using namespace std;

#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

#include "itkResampleRThetaToCartesianImageFilter.h"

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
  typedef itk::ResampleRThetaToCartesianImageFilter< InputImageType, OutputImageType > ResampleType;
  typedef itk::ImageFileWriter< OutputImageType > WriterType;

  try
    {
    ReaderType::Pointer reader = ReaderType::New();
    ResampleType::Pointer resample = ResampleType::New();
    WriterType::Pointer writer = WriterType::New();

    resample->SetInput( reader->GetOutput() );

    reader->SetFileName( argv[1] );
    writer->SetFileName( argv[2] );

    reader->UpdateOutputInformation();

    resample->SetDefaultPixelValue( 0 );

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
