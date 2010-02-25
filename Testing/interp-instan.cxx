#include "itkNearestNeighborInterpolateImageFunction.h"

#include "itkImage.h"

#include "itkFixedArray.h"
#include "itkMatrix.h"

typedef unsigned short OutputPixelType;
const unsigned int Dimension = 3;
typedef itk::Image< OutputPixelType, Dimension > OutputImageType;

template class itk::NearestNeighborInterpolateImageFunction< OutputImageType, double >;

template class itk::FixedArray< double, Dimension >;
template class itk::Matrix< double, Dimension, Dimension >;
