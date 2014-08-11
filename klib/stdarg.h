/*

   Copyright 2009 Pierre KRIEGER

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
   
*/
#ifndef _STDC_STDARG_H_
#define _STDC_STDARG_H_

#include <stddef.h>

typedef size_t*                 va_list;
#define va_start(l,p)           ((l) = ((size_t*)(&(p))) + 1)
#define va_arg(l,t)             (*((t*)(l++)))
#define va_end(l)               ((void)0)
#define va_copy(d,s)            ((d) = (s))

#endif

