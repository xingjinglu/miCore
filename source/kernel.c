#include"../include/kernel.h"

static hipError_t launch_kernel( hipFunction_t kern, uint32_t gdx, uint32_t gdy, uint32_t gdz, const uint32_t* block, hipStream_t s, void** args )
{
    return hipModuleLaunchKernel( kern, gdx, gdy, gdz, block[0], block[1], block[2], 0, s, NULL, args );
}
__local_func void init_kernel( kernel_t* p_kern )
{
    p_kern->launch=&launch_kernel;
    p_kern->block[1]=1;
    p_kern->block[2]=1;
}