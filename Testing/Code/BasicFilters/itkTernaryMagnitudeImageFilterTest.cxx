/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkTernaryMagnitudeImageFilterTest.cxx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) 2000 National Library of Medicine
  All rights reserved.

  See COPYRIGHT.txt for copyright details.

=========================================================================*/



#include <itkImage.h>
#include <itkTernaryMagnitudeImageFilter.h>
#include <itkSimpleImageRegionIterator.h>


int main() 
{

  // Define the dimension of the images
  const unsigned int myDimension = 3;

  // Declare the types of the images
  typedef itk::Image<float, myDimension>  myImageType1;
  typedef itk::Image<float, myDimension>  myImageType2;
  typedef itk::Image<float, myDimension>  myImageType3;
  typedef itk::Image<float, myDimension>  myImageType4;

  // Declare the type of the index to access images
  typedef itk::Index<myDimension>         myIndexType;

  // Declare the type of the size 
  typedef itk::Size<myDimension>          mySizeType;

  // Declare the type of the Region
  typedef itk::ImageRegion<myDimension>        myRegionType;

  // Create two images
  myImageType1::Pointer inputImageA  = myImageType1::New();
  myImageType2::Pointer inputImageB  = myImageType2::New();
  myImageType3::Pointer inputImageC  = myImageType3::New();
  
  // Define their size, and start index
  mySizeType size;
  size[0] = 2;
  size[1] = 2;
  size[2] = 2;

  myIndexType start;
  start[0] = 0;
  start[1] = 0;
  start[2] = 0;

  myRegionType region;
  region.SetIndex( start );
  region.SetSize( size );

  // Initialize Image A
  inputImageA->SetLargestPossibleRegion( region );
  inputImageA->SetBufferedRegion( region );
  inputImageA->SetRequestedRegion( region );
  inputImageA->Allocate();

  // Initialize Image B
  inputImageB->SetLargestPossibleRegion( region );
  inputImageB->SetBufferedRegion( region );
  inputImageB->SetRequestedRegion( region );
  inputImageB->Allocate();

  // Initialize Image C
  inputImageC->SetLargestPossibleRegion( region );
  inputImageC->SetBufferedRegion( region );
  inputImageC->SetRequestedRegion( region );
  inputImageC->Allocate();

  // Declare Iterator types apropriated for each image 
  typedef itk::SimpleImageRegionIterator<myImageType1>  myIteratorType1;
  typedef itk::SimpleImageRegionIterator<myImageType2>  myIteratorType2;
  typedef itk::SimpleImageRegionIterator<myImageType3>  myIteratorType3;
  typedef itk::SimpleImageRegionIterator<myImageType4>  myIteratorType4;

  // Create one iterator for Image A (this is a light object)
  myIteratorType1 it1( inputImageA, inputImageA->GetBufferedRegion() );

  // Initialize the content of Image A
  std::cout << "First operand " << std::endl;
  it1.Begin();
  while( !it1.IsAtEnd() ) 
  {
    it1.Set( 2.0 );
    std::cout << it1.Get() << std::endl;
    ++it1;
  }

  // Create one iterator for Image B (this is a light object)
  myIteratorType2 it2( inputImageB, inputImageB->GetBufferedRegion() );

  // Initialize the content of Image B
  std::cout << "Second operand " << std::endl;
  it2.Begin();
  while( !it2.IsAtEnd() ) 
  {
    it2.Set( 3.0 );
    std::cout << it2.Get() << std::endl;
    ++it2;
  }

  // Create one iterator for Image C (this is a light object)
  myIteratorType3 it3( inputImageC, inputImageC->GetBufferedRegion() );

  // Initialize the content of Image C
  std::cout << "Third operand " << std::endl;
  it3.Begin();
  while( !it3.IsAtEnd() ) 
  {
    it3.Set( 4.0 );
    std::cout << it3.Get() << std::endl;
    ++it3;
  }


  // Declare the type for the Magnitude Filter
  typedef itk::TernaryMagnitudeImageFilter<
                                myImageType1,
                                myImageType2,
                                myImageType3,
                                myImageType4  >       myFilterType;
            

  // Create a MagnitudeImageFilter 
  myFilterType::Pointer filter = myFilterType::New();


  // Connect the input images
  filter->SetInput1( inputImageA ); 
  filter->SetInput2( inputImageB );
  filter->SetInput3( inputImageB );

  // Get the Smart Pointer to the Filter Output 
  myImageType4::Pointer outputImage = filter->GetOutput();

  
  // Execute the filter
  filter->Update();

  // Create an iterator for going through the image output
  myIteratorType4 it4(outputImage, outputImage->GetBufferedRegion());
  
  //  Print the content of the result image
  std::cout << " Result " << std::endl;
  it4.Begin();
  while( !it4.IsAtEnd() ) 
  {
    std::cout << it4.Get() << std::endl;
    ++it4;
  }


  // All objects should be automatically destroyed at this point
  return 0;

}




