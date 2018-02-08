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

#ifdef LINUX
/* BEGIN quote
http://graphviz.sourcearchive.com/documentation/2.16/gvrender__pango_8c-source.html
*/
/* _GNU_SOURCE is needed (supposedly) for the feenableexcept
 * prototype to be defined in fenv.h on GNU systems.
 * Presumably it will do no harm on other systems.
*/
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

/* We are not supposed to need __USE_GNU, but I can't see
 * how to get the prototype for fedisableexcept from
 * /usr/include/fenv.h without it.
*/
#ifndef __USE_GNU
#define __USE_GNU
#endif
/* END quote */
#endif // LINUX

#include <fenv.h>

//-----------------------------------------------------------------------------
// feenableexcept/fedisableexcept implementations
//-----------------------------------------------------------------------------

#if defined(__sun) || defined(__EMSCRIPTEN__)

static int
feenableexcept (unsigned int /*excepts*/)
{
  return 0;
}

static int
fedisableexcept (unsigned int /*excepts*/)
{
  return 0;
}

#elif defined(__APPLE__)

#include "itkFloatingPointExceptions_macos.cxx"

#endif

// Implementation of "fhdl" sigaction used below
#include "itkFloatingPointExceptions_fhdl.cxx"

#include <cstring> // memset

namespace itk
{

void
FloatingPointExceptions
::Enable()
{
  feenableexcept (FE_DIVBYZERO);
  feenableexcept (FE_INVALID);
  feenableexcept (FPE_FLTOVF);
  feenableexcept (FPE_FLTUND);
  feenableexcept (FPE_FLTRES);
  feenableexcept (FPE_FLTSUB);
  feenableexcept (FPE_INTDIV);
  feenableexcept (FPE_INTOVF);

  struct sigaction act;
  memset(&act,0,sizeof(struct sigaction));
  act.sa_sigaction = fhdl;
  sigemptyset(&act.sa_mask);
  act.sa_flags = SA_SIGINFO;
  sigaction(SIGFPE,&act,ITK_NULLPTR);
  FloatingPointExceptions::m_Enabled = true;
}

void
FloatingPointExceptions
::Disable()
{
  fedisableexcept (FE_DIVBYZERO);
  fedisableexcept (FE_INVALID);
  fedisableexcept (FPE_FLTOVF);
  fedisableexcept (FPE_FLTUND);
  fedisableexcept (FPE_FLTRES);
  fedisableexcept (FPE_FLTSUB);
  fedisableexcept (FPE_INTDIV);
  fedisableexcept (FPE_INTOVF);
  FloatingPointExceptions::m_Enabled = false;
}

} // end of itk namespace
