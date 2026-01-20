#ifndef UICOMPONENTS_H
#define UICOMPONENTS_H

#include <graphics.h>
#include <string>
#include <functional>

// 颜色常量定义
const COLORREF BUTTON_NORMAL_COLOR = RGB(70, 130, 180);     // 按钮默认颜色 - 钢蓝色
const COLORREF BUTTON_HOVER_COLOR = RGB(100, 149, 237);     // 鼠标悬停颜色 - 矢车菊蓝
const COLORREF BUTTON_PRESSED_COLOR = RGB(30, 144, 255);    // 按钮按下颜色 - 道奇蓝
const COLORREF BUTTON_TEXT_COLOR = WHITE;                   // 按钮文字颜色
const COLORREF SLIDER_TRACK_COLOR = RGB(200, 200, 200);     // 滑块轨道颜色
const COLORREF SLIDER_HANDLE_COLOR = RGB(70, 130, 180);     // 滑块手柄颜色
const COLORREF PANEL_BG_COLOR = RGB(240, 240, 240);         // 面板背景色
const COLORREF PANEL_BORDER_COLOR = RGB(180, 180, 180);     // 面板边框色

// ========================================================================= //
// 按钮类 (Button)
// 功能：创建可交互按钮，支持点击事件和状态变化（正常/悬停/按下）
class Button {
public:
    // 构造函数：在指定位置(x,y)创建按钮，设置宽度(w)、高度(h)和显示文本
    Button(int x, int y, int w, int h, const std::wstring& text);

    // 绘制按钮到屏幕
    void draw();

    // 更新按钮状态（处理鼠标交互）
    // 参数：mouseX, mouseY - 鼠标当前位置
    //       message - Windows消息类型（WM_MOUSEMOVE/WM_LBUTTONDOWN等）
    // 返回值：是否触发了点击事件
    bool update(int mouseX, int mouseY, int message);

    // 设置按钮点击回调函数
    void setOnClick(std::function<void()> callback);

    // 启用/禁用按钮
    void setEnabled(bool enabled);
    bool getEnabled() const;

    // 设置/获取按钮文本
    void setText(const std::wstring& newText);
    std::wstring getText() const;
    
    // 设置按钮位置
    void setPosition(int newX, int newY);

private:
    int x, y;                   // 按钮左上角坐标
    int width, height;          // 按钮尺寸
    std::wstring text;          // 按钮显示文本
    bool isHovered;             // 鼠标是否悬停
    bool isPressed;             // 按钮是否被按下
    bool enabled;               // 按钮是否启用
    std::function<void()> onClick; // 点击事件回调函数
};

// ========================================================================= //
// 滑块类 (Slider)
// 功能：创建可拖动的滑块控件，用于在[minValue, maxValue]范围内选择数值
class Slider {
public:
    // 构造函数：创建滑块控件
    // 参数：x,y - 滑块左上角位置
    //       w,h - 滑块尺寸（h通常较小，w为滑块长度）
    //       minVal, maxVal - 数值范围
    //       initial - 初始值
    //       label - 滑块标签（可选）
    Slider(int x, int y, int w, int h, float minVal, float maxVal, float initial, 
           const std::wstring& label = L"");

    // 绘制滑块控件
    void draw();

    // 更新滑块状态（处理鼠标拖动）
    // 参数：mouseX, mouseY - 鼠标当前位置
    //       message - Windows消息类型
    // 返回值：滑块值是否发生变化
    bool update(int mouseX, int mouseY, int message);

    // 获取/设置当前滑块值
    float getValue() const;
    void setValue(float newValue);

    // 设置滑块数值范围
    void setRange(float minVal, float maxVal);

    // 获取/设置滑块标签文本
    std::wstring getLabel() const;
    void setLabel(const std::wstring& newLabel);

private:
    int x, y;                   // 滑块位置
    int width, height;          // 滑块尺寸
    float minValue, maxValue;   // 数值范围
    float currentValue;         // 当前值
    bool isDragging;            // 是否正在拖动
    std::wstring label;         // 标签文本

    // 辅助函数：数值与位置的相互转换
    int valueToPosition(float value) const;    // 数值转滑块位置
    float positionToValue(int position) const; // 位置转对应数值
};

// ========================================================================= //
// 面板类 (Panel)
// 功能：创建矩形面板，用于组织和容纳其他UI组件
// 特点：提供背景和边框，可作为UI组件的容器
class Panel {
public:
    // 构造函数：创建面板
    // 参数：x,y - 面板左上角位置
    //       w,h - 面板尺寸
    //       title - 面板标题（可选）
    Panel(int x, int y, int w, int h, const std::wstring& title = L"");

    // 绘制面板
    void draw();

    // 设置面板位置和尺寸
    void setPosition(int newX, int newY);
    void setSize(int newWidth, int newHeight);
    
    // 设置面板颜色
    void setColors(COLORREF background, COLORREF border);

    // 判断点是否在面板区域内
    bool contains(int pointX, int pointY) const;

private:
    int x, y;                   // 面板位置
    int width, height;          // 面板尺寸
    std::wstring title;         // 面板标题
    COLORREF bgColor;           // 背景颜色
    COLORREF borderColor;       // 边框颜色
};

// ========================================================================= //
// 标签类 (Label)
// 功能：创建文本标签，用于显示静态文本信息
class Label {
public:
    // 构造函数：创建标签
    // 参数：x,y - 标签位置（通常为文本左下角或左上角）
    //       text - 显示文本
    Label(int x, int y, const std::wstring& text);

    // 绘制标签文本
    void draw();

    // 设置标签文本
    void setText(const std::wstring& newText);
    
    // 设置标签位置
    void setPosition(int newX, int newY);
    
    // 设置文本颜色
    void setColor(COLORREF color);
    
    // 设置文本大小（字体大小）
    void setTextSize(int size);

private:
    int x, y;                   // 标签位置
    std::wstring text;          // 显示文本
    COLORREF textColor;         // 文本颜色
    int textSize;               // 文本大小（字体尺寸）
};

#endif // UICOMPONENTS_H