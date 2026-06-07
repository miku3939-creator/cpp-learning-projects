/*#include "student_matmul.h"*/

typedef float v __attribute__((vector_size(32)));

float arraySumVector(const float *values, int N)
{
    v v_sum = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    v v_sum0 = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

    int W = 8;
    int i = 0;

    for (; i <= N - 2 * W; i += 2 * W)
    {
        v_sum += *(const v *)(values + i);
        v_sum0 += *(const v *)(values + i + W);
    }

    v_sum += v_sum0;

    if (i <= N - W)
    {
        v_sum += *(const v *)(values + i);
        i += W;
    }

    float sum0 = v_sum[0] + v_sum[4];
    float sum1 = v_sum[1] + v_sum[5];
    float sum2 = v_sum[2] + v_sum[6];
    float sum3 = v_sum[3] + v_sum[7];

    float sum4 = sum0 + sum2;
    float sum5 = sum1 + sum3;

    sum0 = sum4 + sum5;

    for (; i < N; i++)
    {
        sum0 += values[i];
    }

    return sum0;
}

/*#include "student_simd.h"

float arraySumVector(const float *values, int N)
{
    // Todo：在这里完成你的代码
    typedef float v __attribute__((vector_size(32)));
    v v_sum = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    v v_sum0 = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

    int W = 8;
    int i = 0;

    for (; i <= N - 2 * W; i += 2 * W)
    {
        v_sum += *(const v *)(values + i);
        v_sum0 += *(const v *)(values + i + W);
    }

    v_sum += v_sum0;

    if (i <= N - W)
    {
        v_sum += *(const v *)(values + i);
        i += W;
    }

    float sum0 = 0.0f;
    for (int j = 0; j < 8; j++)
    {
        sum0 += v_sum[j];
    }

    for (; i < N; i++)
    {
        sum0 += values[i];
    }

    return sum0;
}*/