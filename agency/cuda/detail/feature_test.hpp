#pragma once

// cf. c++ feature test study group
#if defined(__CUDACC__)
#  if !defined(__CUDA_ARCH__) || (__CUDA_ARCH__>= 350 && defined(__CUDACC_RDC__))
#    define __cuda_lib_has_cudart 1
#  else
#    define __cuda_lib_has_cudart 0
#  endif
#else
#  define __cuda_lib_has_cudart 0
#endif

#if defined(__CUDACC__)
#  if !defined(__CUDA_ARCH__) || (__CUDA_ARCH__ >= 200)
#    define __cuda_lib_has_printf 1
#  else
#    define __cuda_lib_has_printf 0
#  endif
#else
#  define __cuda_lib_has_printf 1
#endif

