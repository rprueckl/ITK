/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkEllipseSpatialObject.txx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __EllipseSpatialObject_txx
#define __EllipseSpatialObject_txx

#include "itkEllipseSpatialObject.h" 

namespace itk 
{ 

/** Constructor */
template< unsigned int TDimension >
EllipseSpatialObject< TDimension >
::EllipseSpatialObject()
{
  this->SetTypeName("EllipseSpatialObject");
  m_Radius.Fill(1.0);
  this->SetDimension(TDimension);
} 

/** Destructor */
template< unsigned int TDimension >
EllipseSpatialObject< TDimension >
::~EllipseSpatialObject()  
{
  
}

/** Set all radii to the same radius value */
template< unsigned int TDimension >
void
EllipseSpatialObject< TDimension >
::SetRadius(double radius)
{
  for(unsigned int i=0;i<NumberOfDimension;i++)
    {
    m_Radius[i]=radius;
    }
}

/** Test whether a point is inside or outside the object 
 *  For computational speed purposes, it is faster if the method does not
 *  check the name of the class and the current depth */ 
template< unsigned int TDimension >
bool 
EllipseSpatialObject< TDimension >
::IsInside( const PointType & point) const
{
  if(!this->GetIndexToWorldTransform()->GetInverse(const_cast<TransformType *>(this->GetInternalInverseTransform())))
    {
    return false;
    }

  PointType transformedPoint = this->GetInternalInverseTransform()->TransformPoint(point);  
  double r = 0;
  for(unsigned int i=0;i<TDimension;i++)
    {
    if(m_Radius[i]!=0.0)
      {
      r += (transformedPoint[i]*transformedPoint[i])/(m_Radius[i]*m_Radius[i]);
      }
    else if(transformedPoint[i]>0.0)  // Degenerate ellipse
      {
      r = 2; // Keeps function from returning true here 
     break;
      }
    }
  
  if(r<1)
    {
    return true;
    }
  return false;
}



/** Test if the given point is inside the ellipse */
template< unsigned int TDimension >
bool 
EllipseSpatialObject< TDimension > 
::IsInside( const PointType & point, unsigned int depth, char * name ) const 
{
  itkDebugMacro( "Checking the point [" << point << "] is inside the Ellipse" );
    
  if(name == NULL)
    {
    if(IsInside(point))
      {
      return true;
      }
    }
  else if(strstr(typeid(Self).name(), name))
    {
    if(IsInside(point))
      {
      return true;
      }
    }

  return Superclass::IsInside(point, depth, name);
} 

/** Compute the bounds of the ellipse */
template< unsigned int TDimension >
bool
EllipseSpatialObject< TDimension >
::ComputeLocalBoundingBox() const
{ 
  itkDebugMacro( "Computing ellipse bounding box" );

  if( this->GetBoundingBoxChildrenName().empty() 
      || strstr(typeid(Self).name(), this->GetBoundingBoxChildrenName().c_str()) )
    {
    PointType pnt;
    PointType pnt2;
    for(unsigned int i=0; i<TDimension;i++) 
      {   
      if(m_Radius[i]>0)
        {
        pnt[i]=-m_Radius[i];
        pnt2[i]=m_Radius[i];
        }
      else
        {
        pnt[i]=m_Radius[i];
        pnt2[i]=-m_Radius[i];
        }
      } 
     
      pnt = this->GetIndexToWorldTransform()->TransformPoint(pnt);
      pnt2 = this->GetIndexToWorldTransform()->TransformPoint(pnt2);
         
      const_cast<BoundingBoxType *>(this->GetBounds())->SetMinimum(pnt);
      const_cast<BoundingBoxType *>(this->GetBounds())->SetMaximum(pnt2);
    }
  return true;
} 


/** Returns if the ellipse os evaluable at one point */
template< unsigned int TDimension >
bool
EllipseSpatialObject< TDimension >
::IsEvaluableAt( const PointType & point, unsigned int depth, char * name ) const
{
  itkDebugMacro( "Checking if the ellipse is evaluable at " << point );
  return IsInside(point, depth, name);
}

/** Returns the value at one point */
template< unsigned int TDimension >
bool
EllipseSpatialObject< TDimension >
::ValueAt( const PointType & point, double & value, unsigned int depth,
           char * name ) const
{
  itkDebugMacro( "Getting the value of the ellipse at " << point );
  if( IsInside(point, 0, name) )
    {
    value = 1;
    return true;
    }
  else
    {
    if( Superclass::IsEvaluableAt(point, depth, name) )
      {
      Superclass::ValueAt(point, value, depth, name);
      return true;
      }
    else
      {
      value = 0;
      return false;
      }
    }
  return false;
}

/** Print Self function */
template< unsigned int TDimension >
void 
EllipseSpatialObject< TDimension >
::PrintSelf( std::ostream& os, Indent indent ) const
{

  Superclass::PrintSelf(os, indent);
  os << "Radius: " << m_Radius << std::endl;

}

} // end namespace itk

#endif
