/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkTransform.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) 2000 National Library of Medicine
  All rights reserved.

  See COPYRIGHT.txt for copyright details.

=========================================================================*/
#ifndef __itkTransform_h
#define __itkTransform_h

#include "itkObject.h"
#include "itkObjectFactory.h"

namespace itk
{
  
/** \class Transform
 * \brief Generic concept of transformation for a registration method
 *
 * This Class define the generic interface for a transformation that
 * is use in a registration method.  It defines a type of parameters
 * that uniquely defines the transformation. These parameters will
 * be supplied to the optimization method as the search space in 
 * which an optimum value should be found.
 *
 */

template <class TParameters>
class ITK_EXPORT  Transform : public Object

{
public:
  /**
   * Standard "Self" typedef.
   */
  typedef Transform  Self;

  /**
   * Standard "Superclass" typedef.
   */
  typedef Object  Superclass;


  /** 
   * Smart pointer typedef support 
   */
  typedef SmartPointer<Self>   Pointer;
  typedef SmartPointer<const Self>  ConstPointer;


  /** 
   * Type of the input parameters
   */
  typedef    TParameters      ParametersType;


 /** 
   * Pointer Type to input parameters
   */
  typedef    typename ParametersType::Pointer  ParametersPointer;


 /** 
   * Run-time type information (and related methods).
   */
  itkTypeMacro(Transform, Object);


  /**
   * Method for creation through the object factory.
   */
  itkNewMacro(Self);
  

  /**
   * Get Parameters
   */
  itkGetMacro( Parameters, ParametersPointer );
 

  /**
   * Set Parameters
   */
  virtual void SetParameters( const ParametersType * ) = 0;
 

  
protected:

  Transform();
  virtual ~Transform() {};
  Transform(const Self&);
  const Self & operator=(const Self&);


private:

  ParametersPointer    m_Parameters;

};

} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkTransform.txx"
#endif

#endif



