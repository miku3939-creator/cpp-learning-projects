/*#include "student_matmul.h"*/

#include <stdio.h>
void matmul_forward_naive(
    float *out,          // 输出矩阵指针，大小为 B×T×OC
    const float *inp,    // 输入矩阵指针，大小为 B×T×C
    const float *weight, // 权重矩阵指针，大小为 OC×C
    const float *bias,   // 偏置向量，大小为 OC
    int B, int T,        // 输入的 Batch size 和每个样本的时间长度
    int C,               // 输入数组的维度
    int OC               // 输出数组的维度
)
{
    for (int b = 0; b < B; b++)
    {
        for (int t = 0; t < T; t++)
        {
            int bt = b * T + t;
            for (int o = 0; o < OC; o++)
            {
                float val = (bias != NULL) ? bias[o] : 0.0f;
                for (int i = 0; i < C; i++)
                {
                    val += inp[bt * C + i] * weight[o * C + i];
                }
                out[bt * OC + o] = val;
            }
        }
    }
}
void matmul_forward(float *out,
                    const float *inp,
                    const float *weight,
                    const float *bias,
                    int B,
                    int T,
                    int C,
                    int OC)
{
    int BT = B * T;
    for (int bt = 0; bt < BT; bt += 4)
    {
        for (int o = 0; o < OC; o++)
        {
            float v0 = 0.0f, v1 = 0.0f, v2 = 0.0f, v3 = 0.0f;

            int b0 = bt * C;
            int b1 = b0 + C;
            int b2 = b1 + C;
            int b3 = b2 + C;

            int w = o * C;

            int i = 0;
            for (; i <= C - 4; i += 4)
            {
                float w0 = weight[w + i];
                float w1 = weight[w + i + 1];
                float w2 = weight[w + i + 2];
                float w3 = weight[w + i + 3];

                v0 += inp[b0 + i] * w0 + inp[b0 + i + 1] * w1 + inp[b0 + i + 2] * w2 + inp[b0 + i + 3] * w3;
                v1 += inp[b1 + i] * w0 + inp[b1 + i + 1] * w1 + inp[b1 + i + 2] * w2 + inp[b1 + i + 3] * w3;
                v2 += inp[b2 + i] * w0 + inp[b2 + i + 1] * w1 + inp[b2 + i + 2] * w2 + inp[b2 + i + 3] * w3;
                v3 += inp[b3 + i] * w0 + inp[b3 + i + 1] * w1 + inp[b3 + i + 2] * w2 + inp[b3 + i + 3] * w3;
            }
            for (; i < C; i++)
            {
                float w_r = weight[w + i];

                v0 += inp[b0 + i] * w_r;
                v1 += inp[b1 + i] * w_r;
                v2 += inp[b2 + i] * w_r;
                v3 += inp[b3 + i] * w_r;
            }
            float biasv = bias ? bias[o] : 0.0f;

            out[(bt + 0) * OC + o] = v0 + biasv;
            out[(bt + 1) * OC + o] = v1 + biasv;
            out[(bt + 2) * OC + o] = v2 + biasv;
            out[(bt + 3) * OC + o] = v3 + biasv;
        }
    }
}
