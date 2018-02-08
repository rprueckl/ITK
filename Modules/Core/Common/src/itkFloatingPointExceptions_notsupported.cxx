/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

//
// This file was designed to be directly included from itkFloatingPointExceptions
// cxx files.
//

namespace itk
{

void FloatingPointExceptions
::Enable()
{
  std::cerr << "FloatingPointExceptions are not supported on this platform." << std::endl;
  if(itk::FloatingPointExceptions::GetExceptionAction() ==
     itk::FloatingPointExceptions::ABORT)
    {
    abort();
    }
  else
    {
    exit(255);
    }
}

void FloatingPointExceptions
::Disable()
{
  std::cerr << "FloatingPointExceptions are not supported on this platform." << std::endl;
  if(itk::FloatingPointExceptions::GetExceptionAction() ==
     itk::FloatingPointExceptions::ABORT)
    {
    abort();
    }
  else
    {
    exit(255);
    }
}

} // end of itk namespace
