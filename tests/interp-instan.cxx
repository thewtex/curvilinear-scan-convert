#include "itkNearestNeighborInterpolateImageFunction.h"

#include "itkImage.h"

typedef unsigned short OutputPixelType;
const unsigned int Dimension = 3;
typedef itk::Image< OutputPixelType, Dimension > OutputImageType;

template class itk::NearestNeighborInterpolateImageFunction< OutputImageType, double >;
