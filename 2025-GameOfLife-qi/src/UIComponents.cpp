#define NOMINMAX
#include <windows.h>
#include "UIComponents.h"
#include <algorithm>
#include <cmath>  

// ==================== UI 组件实现 ====================
// 本文件包含简单的 UI 控件实现：按钮(Button)、滑动条(Slider)、面板(Panel)、标签(Label)
// 注释保持简短，说明各方法的用途、主要行为和参数/返回值约定。

// ==================== Button 实现 ====================

// 构造函数：初始化按钮位置、尺寸、文字及交互状态
Button::Button(int x, int y, int w, int h, const std::wstring& text)
    : x(x), y(y), width(w), height(h), text(text),
    isHovered(false), isPressed(false), enabled(true), onClick(nullptr) {
}

void Button::draw() {
    // 根据当前状态选择按钮颜色（禁用/按下/悬停/默认）并绘制按钮
    COLORREF buttonColor;
    if (!enabled) {
        buttonColor = RGB(150, 150, 150); // 禁用状态
    }
    else if (isPressed) {
        buttonColor = BUTTON_PRESSED_COLOR;
    }
    else if (isHovered) {
        buttonColor = BUTTON_HOVER_COLOR;
    }
    else {
        buttonColor = BUTTON_NORMAL_COLOR;
    }

    // 绘制按钮背景
    setfillcolor(buttonColor);
    setlinecolor(PANEL_BORDER_COLOR);
    fillrectangle(x, y, x + width, y + height);

    // 绘制按钮边框
    rectangle(x, y, x + width, y + height);

    // 计算并绘制居中文字
    settextcolor(BUTTON_TEXT_COLOR);
    setbkmode(TRANSPARENT);

    // 计算文字位置使其居中
    int textWidth = textwidth(text.c_str());
    int textHeight = textheight(text.c_str());
    int textX = x + (width - textWidth) / 2;
    int textY = y + (height - textHeight) / 2;

    outtextxy(textX, textY, text.c_str());
}

bool Button::update(int mouseX, int mouseY, int message) {
    // 如果被禁用则忽略所有事件并重置状态
    if (!enabled) {
        isHovered = false;
        isPressed = false;
        return false;
    }

    // 判断鼠标是否在按钮范围内
    bool mouseOver = (mouseX >= x && mouseX <= x + width &&
        mouseY >= y && mouseY <= y + height);

    // 根据 Windows 消息更新交互状态并在必要时触发回调
    switch (message) {
    case WM_MOUSEMOVE:
        isHovered = mouseOver;
        break;

    case WM_LBUTTONDOWN:
        if (mouseOver) {
            isPressed = true; // 按下开始
            return true;
        }
        break;

    case WM_LBUTTONUP:
        // 仅当之前按下且鼠标仍在按钮上时触发点击
        if (isPressed && mouseOver) {
            isPressed = false;
            if (onClick) {
                onClick();
            }
            return true;
        }
        isPressed = false;
        break;
    }

    return false;
}

void Button::setOnClick(std::function<void()> callback) {
    // 设置按钮的点击回调。
    // callback: 无参无返回值的函数，在按钮被点击（按下并释放且鼠标仍在按钮内）时调用。
    onClick = callback;
}

void Button::setEnabled(bool enabled) {
    // 启用或禁用按钮。禁用后不会响应鼠标事件并重置交互状态。
    // enabled: true 表示可用，false 表示禁用。
    this->enabled = enabled;
    if (!enabled) {
        isHovered = false;
        isPressed = false;
    }
}

bool Button::getEnabled() const {
    // 返回按钮当前是否可用
    return enabled;
}

void Button::setText(const std::wstring& newText) {
    // 更新按钮显示的文字
    text = newText;
}

std::wstring Button::getText() const {
    // 获取当前按钮文字
    return text;
}

void Button::setPosition(int newX, int newY) {
    // 设置按钮的新位置（左上角坐标）
    x = newX;
    y = newY;
}

// ==================== Slider 实现 ====================

Slider::Slider(int x, int y, int w, int h, float minVal, float maxVal, float initial, const std::wstring& label)
    : x(x), y(y), width(w), height(h),
    minValue(minVal), maxValue(maxVal), currentValue(initial),
    isDragging(false), label(label) {
    // 确保初始值在范围内
    currentValue = std::max(minValue, std::min(maxValue, initial));
}

void Slider::draw() {
    // 绘制滑轨和滑块（包含标签与当前数值显示）
    int trackY = y + height / 2;
    setlinecolor(SLIDER_TRACK_COLOR);
    setlinestyle(PS_SOLID, 2);
    line(x, trackY, x + width, trackY);

    // 绘制滑块手柄
    int handleX = valueToPosition(currentValue);
    int handleY = trackY;
    int handleRadius = 6;

    setfillcolor(SLIDER_HANDLE_COLOR);
    setlinecolor(PANEL_BORDER_COLOR);
    fillcircle(handleX, handleY, handleRadius);

    // 绘制标签和值（如果有）
    if (!label.empty()) {
        settextcolor(BLACK);
        setbkmode(TRANSPARENT);

        // 绘制标签
        outtextxy(x, y - 20, label.c_str());

        // 绘制当前值
        wchar_t valueText[50];
        swprintf(valueText, 50, L"%.2f", currentValue);
        outtextxy(x + width + 10, y - 20, valueText);
    }

    // 恢复默认线型
    setlinestyle(PS_SOLID, 1);
}

bool Slider::update(int mouseX, int mouseY, int message) {
    int handleX = valueToPosition(currentValue);
    int trackY = y + height / 2;
    int handleRadius = 8; // 稍微大一点便于点击

    bool mouseOverHandle = (std::abs(mouseX - handleX) <= handleRadius &&  // 使用std::abs
        std::abs(mouseY - trackY) <= handleRadius);

    // 处理鼠标事件以实现拖动/跳转功能
    switch (message) {
    case WM_LBUTTONDOWN:
        // 点击滑块或在轨道上点击时开始拖动（轨道点击直接跳转）
        if (mouseOverHandle ||
            (mouseX >= x && mouseX <= x + width &&
                std::abs(mouseY - trackY) <= height / 2)) {
            isDragging = true;
            // 点击轨道时直接将值设为该位置
            if (!mouseOverHandle) {
                currentValue = positionToValue(mouseX);
                currentValue = std::max(minValue, std::min(maxValue, currentValue));
            }
            return true;
        }
        break;

    case WM_MOUSEMOVE:
        // 拖动时随鼠标更新数值
        if (isDragging) {
            currentValue = positionToValue(mouseX);
            currentValue = std::max(minValue, std::min(maxValue, currentValue));
            return true;
        }
        break;

    case WM_LBUTTONUP:
        // 停止拖动
        if (isDragging) {
            isDragging = false;
            return true;
        }
        break;
    }

    return false;
}

float Slider::getValue() const {
    // 返回滑块当前数值（浮点数）
    return currentValue;
}

void Slider::setValue(float newValue) {
    // 设置滑块数值，超出范围会被钳位到 [minValue, maxValue]
    currentValue = std::max(minValue, std::min(maxValue, newValue));
}

void Slider::setRange(float minVal, float maxVal) {
    // 设置数值范围并确保当前值仍在新范围内
    minValue = minVal;
    maxValue = maxVal;
    currentValue = std::max(minValue, std::min(maxValue, currentValue));
}

std::wstring Slider::getLabel() const {
    // 获取滑块的标签文本
    return label;
}

void Slider::setLabel(const std::wstring& newLabel) {
    // 设置滑块标签文本
    label = newLabel;
}

int Slider::valueToPosition(float value) const {
    // 将滑块数值 value 转换为对应的屏幕像素位置 X 坐标
    float normalized = (value - minValue) / (maxValue - minValue);

    // x 是滑块轨道起点的 X 坐标
    // normalized * width 计算归一化值对应的轨道长度
    // static_cast<int> 将浮点数转换为整数像素坐标
    return x + static_cast<int>(normalized * width);
}

float Slider::positionToValue(int position) const {
    // 将屏幕像素位置 position 转换为对应的滑块数值为浮点数
    // width 是滑块轨道的总像素宽度
    float normalized = static_cast<float>(position - x) / width;

    //  映射到数值范围：
    // normalized * (maxValue - minValue) 计算归一化位置对应的数值偏移量
    return minValue + normalized * (maxValue - minValue);
}
}

// ==================== Panel 实现 ====================

// Panel 表示一个带标题的矩形区域，可用于承载其他控件或显示分组信息

Panel::Panel(int x, int y, int w, int h, const std::wstring& title)
    : x(x), y(y), width(w), height(h), title(title),
    bgColor(PANEL_BG_COLOR), borderColor(PANEL_BORDER_COLOR) {
}

void Panel::draw() {
    // 绘制面板背景和边框，若有标题则绘制标题与分隔线
    setfillcolor(bgColor);
    setlinecolor(borderColor);
    fillrectangle(x, y, x + width, y + height);
    rectangle(x, y, x + width, y + height);

    // 绘制标题
    if (!title.empty()) {
        settextcolor(BLACK);
        setbkmode(TRANSPARENT);
        outtextxy(x + 5, y + 5, title.c_str());

        // 绘制标题下划线
        setlinecolor(borderColor);
        line(x, y + 25, x + width, y + 25);
    }
}

void Panel::setPosition(int newX, int newY) {
    // 设置面板左上角位置
    x = newX;
    y = newY;
}

void Panel::setSize(int newWidth, int newHeight) {
    // 设置面板宽高
    width = newWidth;
    height = newHeight;
}

void Panel::setColors(COLORREF background, COLORREF border) {
    // 设置面板背景色和边框颜色
    bgColor = background;
    borderColor = border;
}

bool Panel::contains(int pointX, int pointY) const {
    // 判断给定点是否在面板区域内（包括边界）
    return (pointX >= x && pointX <= x + width &&
        pointY >= y && pointY <= y + height);
}

// ==================== Label 实现 ====================

// Label 是最小的显示控件，用于在指定位置绘制文本。

Label::Label(int x, int y, const std::wstring& text)
    : x(x), y(y), text(text), textColor(BLACK), textSize(12) {
}

void Label::draw() {
    settextcolor(textColor);
    setbkmode(TRANSPARENT);

    // 保存当前字体设置并按需调整高度绘制文本
    LOGFONT fontStyle;
    gettextstyle(&fontStyle);

    // 设置新字体大小并绘制文本
    fontStyle.lfHeight = textSize;
    settextstyle(&fontStyle);

    // 在指定坐标绘制文本
    outtextxy(x, y, text.c_str());

    // 恢复字体样式（如果需要，此处可保存并恢复先前样式）
    settextstyle(&fontStyle);
}

void Label::setText(const std::wstring& newText) {
    // 设置标签文本
    text = newText;
}

void Label::setPosition(int newX, int newY) {
    // 设置标签位置（基于文本绘制的起始点）
    x = newX;
    y = newY;
}

void Label::setColor(COLORREF color) {
    // 设置文本颜色
    textColor = color;
}

void Label::setTextSize(int size) {
    // 设置文本像素高度
    textSize = size;
}