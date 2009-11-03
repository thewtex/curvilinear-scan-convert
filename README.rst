=======================================================================
                      curvilinear-scan-convert
=======================================================================
An ITK based scan conversion filter for an ultrasound curvilinear array
=======================================================================


Requires that the MetaDataDictionary contains entries for:

  Radius
    The distance from the center of rotation to the first sample.

  Theta
    A vector containing the angles in radians of each scan line.  The length of
    this vector should be the same as the extent in the first dimension.
