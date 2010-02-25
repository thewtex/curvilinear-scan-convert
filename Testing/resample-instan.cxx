#include "itkResampleImageFilter.txx"

typedef unsigned short OutputPixelType;
const unsigned int Dimension = 3;
typedef itk::Image< OutputPixelType, Dimension > OutputImageType;

template class itk::ResampleImageFilter< OutputImageType, OutputImageType >;
