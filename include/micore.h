#ifndef __micore_h__
#define __micore_h__

#include<stdint.h>
#include<hip/hip_runtime_api.h>

#if defined(_M_X64)||defined(_M_AMD64)||defined(__x86_64)||defined(_M_IA64)||defined(__LP64__)
  #if __GNUC__>=4
    #define MICOREAPIENTRY __attribute__((visibility("default")))
  #else
    #define MICOREAPIENTRY
  #endif
#else
  #error "Only 64bits-OS supported!"
#endif

#define miCoreMaskPrecisionF32   0x0000
#define miCoreMaskPrecisionF16   0x0001
#define miCoreMaskPrecisionBF16  0x0002
#define miCoreMaskActivationRelu 0x0008
#define miCoreMaskActivationBias 0x0010

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum{
    micore_success                  =0,
    micore_error_invalid_device     =1,
    micore_error_invalid_value      =2,
    micore_error_invalid_binary     =3,
    micore_error_invalid_precision  =4,
    micore_error_memory_alloc_failed=5
} micore_status_t;

typedef enum{
    micore_conv_algo_flexgemm=0,
    micore_conv_algo_cell    =2,
    micore_conv_algo_cellfft =3
} micore_conv_algo_t;

typedef struct __micore_handle     * micore_handle_t;
typedef struct __micore_tensorshape* micore_tensorshape_t;
typedef struct __micore_parambox   * micore_parambox_t;
typedef uint32_t                     micore_padding_t;
typedef uint32_t                     micore_stride_t;
typedef uint32_t                     micore_dilation_t;

MICOREAPIENTRY micore_status_t      micore_create_handle( micore_handle_t* );
MICOREAPIENTRY micore_tensorshape_t micore_create_tensorshape();
MICOREAPIENTRY micore_parambox_t    micore_create_parambox();
MICOREAPIENTRY void                 micore_set_tensorshape4d( micore_tensorshape_t, uint32_t, uint32_t, uint32_t, uint32_t );
MICOREAPIENTRY void                 micore_set_tensorshape4d_filter( micore_tensorshape_t, uint32_t, uint32_t, uint32_t, uint32_t );
MICOREAPIENTRY micore_padding_t     micore_make_padding2d( uint32_t, uint32_t, uint32_t, uint32_t );
MICOREAPIENTRY micore_stride_t      micore_make_stride2d( uint32_t, uint32_t );
MICOREAPIENTRY micore_dilation_t    micore_make_dilation2d( uint32_t, uint32_t );
MICOREAPIENTRY micore_status_t      micore_build_parambox_fconv( micore_parambox_t, micore_conv_algo_t, uint32_t, micore_tensorshape_t, micore_tensorshape_t, micore_tensorshape_t, micore_padding_t, micore_stride_t, micore_dilation_t, uint32_t );
MICOREAPIENTRY micore_status_t      micore_build_parambox_bconv( micore_parambox_t, micore_conv_algo_t, uint32_t, micore_tensorshape_t, micore_tensorshape_t, micore_tensorshape_t, micore_padding_t, micore_stride_t, micore_dilation_t, uint32_t );
MICOREAPIENTRY micore_status_t      micore_build_parambox_gconv( micore_parambox_t, micore_conv_algo_t, uint32_t, micore_tensorshape_t, micore_tensorshape_t, micore_tensorshape_t, micore_padding_t, micore_stride_t, micore_dilation_t, uint32_t );
MICOREAPIENTRY size_t               micore_get_auxsize( micore_parambox_t );
MICOREAPIENTRY void                 micore_fconv( micore_handle_t, micore_parambox_t, void*, void*, const void*, const void*, const void*, float, uint32_t, hipStream_t );
MICOREAPIENTRY void                 micore_bconv( micore_handle_t, micore_parambox_t, void*, void*, const void*, const void*, float, hipStream_t );
MICOREAPIENTRY void                 micore_gconv( micore_handle_t, micore_parambox_t, void*, void*, const void*, const void*, float, hipStream_t );
MICOREAPIENTRY void                 micore_release_tensorshape( micore_tensorshape_t );
MICOREAPIENTRY void                 micore_release_parambox( micore_parambox_t );
MICOREAPIENTRY void                 micore_release_handle( micore_handle_t );

#ifdef __cplusplus
}
#endif

#endif
