/**
 * @file curvilinear-b-mode.cxx
 * @brief Test VisualSonics scan conversion by making a B-Mode.
 * @author Matthew McCormick (thewtex) <matt@mmmccormick.com>
 * @date 2009-11-03
 */

#include <iostream>
using namespace std;

#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

#include "itkBModeImageFilter.h"
#include "itkVisualSonicsImageIOFactory.h"

#include "itkCurvilinearScanConvertImageFilter.h"

int main( int argc, char* argv[] )
{
  // usage: vs-convert-b-mode input.rdi output.mhd
  if( argc != 3 )
    return EXIT_FAILURE;

  itk::VisualSonicsImageIOFactory::RegisterOneFactory();

  typedef signed short InputPixelType;
  typedef unsigned short OutputPixelType;
  typedef itk::Image< InputPixelType, 3 > InputImageType;
  typedef itk::Image< OutputPixelType, 3 > OutputImageType;

  typedef itk::ImageFileReader< InputImageType > ReaderType;
  typedef itk::BModeImageFilter< InputImageType, OutputImageType > BModeType;
  typedef itk::CurvilinearScanConvertImageFilter< OutputImageType, OutputImageType > ScanConvertType;
  typedef itk::ImageFileWriter< OutputImageType > WriterType;

  ReaderType::Pointer reader = ReaderType::New();
  BModeType::Pointer  bmode  = BModeType::New();
  ScanConvertType::Pointer scanConvert = ScanConvertType::New();
  WriterType::Pointer writer = WriterType::New();

  reader->SetFileName( argv[1] );
  writer->SetFileName( argv[2] );

  bmode->SetInput( reader->GetOutput() );
  scanConvert->SetInput( bmode->GetOutput() );
  // for now
    reader->UpdateOutputInformation();
    scanConvert->SetMetaDataDictionary( reader->GetMetaDataDictionary() );
    scanConvert->UpdateOutputInformation();
    return EXIT_SUCCESS;
  writer->SetInput( scanConvert->GetOutput() );
  try
    {
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
