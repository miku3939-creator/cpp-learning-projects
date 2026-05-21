import numpy as np
import matplotlib.pyplot as plt
from scipy import stats

# 1. 准备实验数据 (单位: m 为 kg, T^2 为 s^2)
m = np.array([0.230841, 0.280941, 0.330862, 0.380769])
T_sq = np.array([2.35629, 2.86286, 3.33526, 3.84184])

# 2. 线性拟合: T^2 = (4*pi^2/k) * m + (4*pi^2/k) * m0
# 对应 y = slope * x + intercept
slope, intercept, r_value, p_value, std_err = stats.linregress(m, T_sq)

# 3. 计算物理量
pi_sq_4 = 4 * np.pi**2
k_fit = pi_sq_4 / slope
m0_fit = intercept / slope

# 4. 绘图
plt.rcParams['font.sans-serif'] = ['SimHei']  # 正常显示中文
plt.rcParams['axes.unicode_minus'] = False 

plt.figure(figsize=(8, 6))
plt.scatter(m, T_sq, color='red', label='实验数据点')
plt.plot(m, slope * m + intercept, color='blue', label=f'拟合直线: $T^2 = {slope:.4f}m + {intercept:.4f}$')

# 设置标签
plt.title('作图法求弹簧组弹性系数与有效质量 ($T^2 - m$ 图)')
plt.xlabel('质量 $m$ (kg)')
plt.ylabel('周期平方 $T^2$ ($s^2$)')
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend()

# 在图上显示计算结果
result_text = f"拟合斜率: {slope:.4f}\n截距: {intercept:.4f}\n相关系数 $R^2$: {r_value**2:.4f}\n\n计算结果:\n$k = {k_fit:.4f}$ N/m\n$m_0 = {m0_fit*1000:.2f}$ g"
plt.text(0.24, 3.2, result_text, bbox=dict(facecolor='white', alpha=0.8))

plt.show()

print(f"拟合得到的弹性系数 k = {k_fit:.4f} N/m")
print(f"拟合得到的有效质量 m0 = {m0_fit*1000:.2f} g")