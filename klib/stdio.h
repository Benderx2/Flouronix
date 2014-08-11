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

#ifndef _STDC_STDIO_H_
#define _STDC_STDIO_H_

#include <stddef.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

int             snprintf(char* s, size_t n, const char* format, ...);
int             sprintf(char* s, const char* format, ...);
int             sscanf(const char* s, const char* format, ...);
int vsnprintf(char* str, size_t size, const char* format, va_list ap);
int             vsprintf(char* s, const char* format, va_list arg);
int             vsscanf(const char* s, const char* format, va_list arg);
       
#ifdef __cplusplus
}
#endif


#endif

