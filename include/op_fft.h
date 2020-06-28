#ifndef __op_fft_h__
#define __op_fft_h__

#include"kernel.h"
#include"param.h"

__local_func void lk_fft2d_r2c_perm_a( kernel_t*, const param_fftconv_t*, void*, void*, uint32_t, hipStream_t );
__local_func void lk_fft2d_r2c_perm_b( kernel_t*, const param_fftconv_t*, void*, void*, uint32_t, hipStream_t );
__local_func void lk_fft2d_r2c_perm_pad( kernel_t*, const param_fftconv_t*, void*, void*, uint32_t, hipStream_t );
__local_func void lk_fft2d_r2c_perm_s( kernel_t*, const param_fftconv_t*, void*, void*, uint32_t, hipStream_t );
__local_func void lk_fft2d_r2c_grid_perm( kernel_t*, const param_fftconv_t*, void*, void*, hipStream_t );
__local_func void lk_fft2d_r2c_grid_perm_pad( kernel_t*, const param_fftconv_t*, void*, void*, hipStream_t );
__local_func void lk_fft2d_r2c_grid_perm_nov( kernel_t*, const param_fftconv_t*, void*, void*, hipStream_t );
__local_func void lk_fft2d_c2r_perm( kernel_t*, const param_fftconv_t*, void*, void*, hipStream_t );
__local_func void lk_fft2d_c2r_grid_perm( kernel_t*, const param_fftconv_t*, void*, void*, hipStream_t );
__local_func void lk_fft2d_c2r_grad_perm( kernel_t*, const param_fftconv_t*, void*, void*, hipStream_t );
__local_func void lk_fft2d_c2r_grad_perm_s( kernel_t*, const param_fftconv_t*, void*, void*, hipStream_t );

#endif