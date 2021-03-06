#ifndef FINALPROJECT_DICOMSERIES_H 
#define FINALPROJECT_DICOMSERIES_H

// TODO: Is storing these header files here best practice?

#include "itkImage.h"
#include "itkGDCMImageIO.h"
#include "itkGDCMSeriesFileNames.h"
#include "itkImageSeriesReader.h"
#include "itkConnectedThresholdImageFilter.h"
#include "itkMaskImageFilter.h"


class dicomSeries{
	// Using allows us to define new types.

	// DICOMs use floats to represent pixels
	using DicomPixelType = float;
	
	// Used later to set the reader's filenames
	using DicomNamesGeneratorType = itk::GDCMSeriesFileNames;

	// Used to hold the names of files before passing them to reader
	using FileNamesContainer = std::vector< std::string >;

	// Used later to set the reader's IO
	using ImageIOType = itk::GDCMImageIO;

public:

	// **VARIABLES AND TYPEDEFS** 

	// We are reading in a 3D image represented with floats
	const static unsigned int Dimension = 3;
	using DicomImage = itk::Image<DicomPixelType, Dimension>;

	// Reader is an ITK image series reader
	using ReaderType = itk::ImageSeriesReader< DicomImage >;

	// Mask allows us to retrieve houndsfield intensity values after 
	// performing connected component region growing
	using MaskImageFilter = itk::MaskImageFilter<DicomImage, DicomImage>;

	// 	**CONSTRUCTORS**

	// Default Constructor
	dicomSeries();

	// Constructor given a filepath
	dicomSeries(char*);

	// **OTHER FUNCTIONS**
	DicomImage::Pointer GetOutput();
	// Void because it will modify private variables, not return a value
	DicomImage::Pointer RegionGrow();

private:
	char* dirName;
  	DicomNamesGeneratorType::Pointer nameGenerator;
  	FileNamesContainer fileNames;
  	ImageIOType::Pointer dicomIO;
  	ReaderType::Pointer reader;
};

#endif