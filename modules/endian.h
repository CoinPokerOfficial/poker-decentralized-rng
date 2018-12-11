#pragma once

#if defined (__i386__) || defined(__x86_64__)
#include "endian.h"
#else
#error architecture not supported
#endif