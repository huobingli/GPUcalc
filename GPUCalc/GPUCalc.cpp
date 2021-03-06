// GPUCalc.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>

#include <cuda_runtime.h>
#include <cuda_device_runtime_api.h>
#include <cuda.h>
#include <assert.h>
//#define N 10;/* 定义10个GPU运算线程 */

#define SIZE (10 * sizeof(int));


/* 运行在GPU端的程序 */

__global__ void vectorADD(int* a, int* b, int* c)

{
// 	int index = threadIdx.x;//获得当前线程的序号
// 
// 	if (index < blockDim.x)
// 		c[index] = a[index] + b[index];

}


int main()
{
// 	int* a = (int*)malloc(10 * sizeof(int));
// 
// 	int* b = (int*)malloc(10 * sizeof(int));
// 
// 	int* c = (int*)malloc(10 * sizeof(int));
// 
// 	/* 初始化数组A, B和C */
// 
// 	int h_a[10],h_b[10];
// 
// 	for (int i = 0; i < 10; i++)
// 	{
// 		h_a[i] = i;
// 		h_b[i] = i;
// 	}
// 
// 
// 	/* 在GPU上分配同样大小的三个数组 */
// 
// 	int* d_a;
// 
// 	int* d_b;
// 
// 	int* d_c;
// 
// 	cudaMalloc((void**)&d_a, 10 * sizeof(int));
// 
// 	cudaMalloc((void**)&d_b, 10 * sizeof(int));
// 
// 	cudaMalloc((void**)&d_c, 10 * sizeof(int));
// 
// 
// 	/* 把本地的数组拷贝进GPU内存 */
// 
// 	cudaMemcpy(d_a, a, 10 * sizeof(int), cudaMemcpyHostToDevice);
// 
// 	cudaMemcpy(d_b, b, 10 * sizeof(int), cudaMemcpyHostToDevice);
// 
// 
// 	/* 定义一个GPU运算块 由 10个运算线程组成 */
// 
// 	dim3 DimBlock = N;
// 
// 	/* 通知GPU用10个线程执行函数vectorADD */
// 
// 	vectorADD(d_a, d_b, d_c);
// 
// 	/* 将GPU运算完的结果复制回本地 */
// 
// 	cudaMemcpy(c, d_c, 10 * sizeof(int), cudaMemcpyDeviceToHost);
// 
// 
// 	/* 释放GPU的内存 */
// 
// 	cudaFree(d_a);
// 
// 	cudaFree(d_b);
// 
// 	cudaFree(d_c);
// 
// 	/* 验证计算结果 */
// 
// 	for (int j = 0; j < 10; j++)
// 	{
// 		printf("%d ", c[j]);
// 		printf("\n");
// 	}

	float *a_h, *b_h;     // pointers to host memory
	float *a_d, *b_d;     // pointers to device memory
	int N = 14;
	int i;
	// allocate arrays on host
	a_h = (float *)malloc(sizeof(float)*N);
	b_h = (float *)malloc(sizeof(float)*N);
	// allocate arrays on device
	cudaMalloc((void **)&a_d, sizeof(float)*N);
	cudaMalloc((void **)&b_d, sizeof(float)*N);
	// initialize host data
	for (i = 0; i < N; i++) {
		a_h[i] = 10.f + i;
		b_h[i] = 0.f;
	}
	// send data from host to device: a_h to a_d 
	cudaMemcpy(a_d, a_h, sizeof(float)*N, cudaMemcpyHostToDevice);
	// copy data within device: a_d to b_d
	cudaMemcpy(b_d, a_d, sizeof(float)*N, cudaMemcpyDeviceToDevice);
	// retrieve data from device: b_d to b_h
	cudaMemcpy(b_h, b_d, sizeof(float)*N, cudaMemcpyDeviceToHost);
	// check result
	for (i = 0; i < N; i++)
		assert(a_h[i] == b_h[i]);
	// cleanup
	free(a_h); free(b_h);
	cudaFree(a_d); cudaFree(b_d);
}