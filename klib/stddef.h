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

#ifndef _STDC_STDDEF_H_
#define _STDC_STDDEF_H_

#undef NULL
#if defined(__cplusplus)
#define NULL    0
#else
#define NULL    ((void*)0)
#endif

typedef __SIZE_TYPE__           size_t;
typedef __PTRDIFF_TYPE__                ptrdiff_t;
typedef __WCHAR_TYPE__          wchar_t;

#define offsetof(st, m) \
    ((size_t)((char*)&((st*)(0))->m - (char*)0))

#endif


