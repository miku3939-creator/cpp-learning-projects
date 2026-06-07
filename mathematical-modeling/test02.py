import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import make_interp_spline

# 1. 实验基础数据设置
f0 = 9550  # 中心谐振频率 (Hz)
R = 30     # 电阻 (欧姆)

# 2. 录入各频点的 Delta f (单位: Hz，左侧为负，右侧为正)
delta_f_left = np.array([-5000, -2500, -1000, -500, -250, -100])
delta_f_right = np.array([0, 100, 250, 500, 1000, 2500, 5000])

# 实际频率 f = f0 + delta_f
f_left = f0 + delta_f_left
f_right = f0 + delta_f_right
f = np.concatenate([f_left, f_right])

# 3. 录入修正后的电压数据 U' (单位: V)
U_left = np.array([1.05e-2, 2.85e-2, 7.90e-2, 1.485e-1, 2.685e-1, 0.485])  # 4.485e-1已改为0.485
U_right = np.array([0.55, 4.75e-1, 2.70e-1,1.50e-1, 8.10e-2, 0.0300, 1.23e-2])  # 0.300e-2已改为0.300
U = np.concatenate([U_left, U_right])

# 4. 计算电流 I (单位: mA) -> I = (U / R) * 1000
I = (U / R) * 1000

# 5. 为了让曲线更平滑，使用样条插值 (Spline Interpolation)
# 注意：插值仅用于画平滑线，实际数据点依然会以散点形式展现在图上
f_smooth = np.linspace(f.min(), f.max(), 500)
# 将 k=3 改为 k=1（线性插值）
spl = make_interp_spline(f, I, k=2)
I_smooth = spl(f_smooth)

# 6. 开始绘图
plt.rcParams['font.sans-serif'] = ['SimHei']  # 正常显示中文
plt.rcParams['axes.unicode_minus'] = False    # 正常显示负号

plt.figure(figsize=(9, 6))

# 画出实验数据点
plt.scatter(f, I, color='red', zorder=5, label='实验数据点')

# 画出平滑拟合的谐振曲线
plt.plot(f_smooth, I_smooth, color='blue', linewidth=2, label='RLC 谐振幅频特性曲线')

# 标注中心谐振点
plt.axvline(x=f0, color='gray', linestyle='--', alpha=0.7)
plt.text(f0 + 100, max(I) * 0.9, f'谐振频率 $f_0$ = {f0} Hz', color='gray')

# 界面优化设置
plt.title(f'RLC 串联电路的幅频特性曲线 ($I - f$ 图，R = {R} $\Omega$)', fontsize=14)
plt.xlabel('频率 $f$ (Hz)', fontsize=12)
plt.ylabel('电流 $I$ (mA)', fontsize=12)
plt.grid(True, linestyle='--', alpha=0.6)
plt.legend(fontsize=11)

# 显示图像
plt.show()

# 打印最终计算出来的电流数组，方便你誊写到实验报告上
print("各频点对应的电流值 (mA):")
for freq, curr in zip(f, I):
    print(f"f = {freq} Hz : I = {curr:.2f} mA")