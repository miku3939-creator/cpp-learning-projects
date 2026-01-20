// 标准与第三方头文件
// <graphics.h>：EasyX 图形库，用于窗口与绘图
// <windows.h>：Windows API（线程、消息、对话框等）
#include <iostream>
#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <vector>
#include <string>
#include <ctime>
#include "UIComponents.h"

// 每个正方形格子大小（像素）
// 用于在窗口中绘制生命游戏的网格单元
// 每个细胞占据 `SPACE x SPACE` 的区域

#define SPACE 10

// 定义网格的行数和列数
// 可以调整这两个值改变地图的尺寸
#define ROWS 60
#define COLS 60

// 游戏状态枚举（用于控制主循环的不同行为）
// MODE_SETUP：用户可编辑细胞（鼠标绘制）
// MODE_RUNNING：执行演化规则，地图按代更新
// MODE_PAUSED：暂停演化，但仍可查看/编辑
enum GameMode {
    MODE_SETUP,
    MODE_RUNNING,
    MODE_PAUSED
};


// ==================== 全局游戏状态变量 ====================

// 控制游戏循环是否继续执行（当前未使用细化，可按需扩展）
bool isContinueSet = true;

// 当前游戏模式（默认为设置模式）
GameMode currentMode = MODE_SETUP;

// 当前代数计数器
int generation = 0;

// 演化速度（代/秒的控制参数，通过滑块调整）
float gameSpeed = 5.0f;

// 是否显示网格线（用于绘制网格）
bool showGrid = true;

// ==================== 性能优化相关变量 ====================

// 用于增量绘制的前一帧状态缓存：仅当当前格子状态与 prevMap 不同时才重绘
bool prevMap[ROWS][COLS] = { 0 };

// 首次绘制或需要强制整图重绘时为 true（此时会清屏并绘制全部格子）
bool firstDraw = true;

// ==================== 线程与同步控制 ====================

// 保护地图数据的互斥锁（临界区）
CRITICAL_SECTION mapLock;

// 输入线程运行控制标志（用于平滑退出）
volatile bool g_running = true;

// 输入处理线程句柄（用于在退出时等待和关闭）
HANDLE g_inputThread = NULL;

// ==================== UI增量绘制优化相关变量 ====================

// UI 脏标记：当 UI 状态（文本、按钮、滑块等）改变时设为 true，主循环会重绘 UI 区域
volatile bool uiDirty = true;

// 缓存上次绘制的文字/控件文本，只有发生变化时才更新对应 UI
std::wstring prevGenerationText;
std::wstring prevModeText;
std::wstring prevPopulationText;
std::wstring prevStartText;
std::wstring prevPauseText;
std::wstring prevResetText;
std::wstring prevRulesText;
std::wstring prevGridText;

// 上次滑块数值缓存（用于检测滑块值是否变化）
float prevSliderValue = -1.0f;

// ==================== 游戏规则配置类 ====================
class GameRules {
public:
	// 存活条件：当活细胞的周围活细胞数在这些值时，下一代继续存活
	std::vector<int> surviveConditions;

	// 出生条件：当死细胞的周围活细胞数在这些值时，下一代变为活细胞
	std::vector<int> birthConditions;

	// 构造函数：初始化默认规则（康威生命游戏的经典规则）
	GameRules() {
		setStandardRules();
	}

	// 设置标准规则：B3/S23（康威生命游戏标准规则）
	void setStandardRules() {
		// 默认规则：B3/S23
		// B3：死细胞周围有3个活细胞时，下一代出生
		// S23：活细胞周围有2或3个活细胞时，下一代存活
		surviveConditions = { 2, 3 };
		birthConditions = { 3 };
	}

	// 设置自定义规则
	//survive - 存活条件数组，birth - 出生条件数组
	void setCustomRules(const std::vector<int>& survive, const std::vector<int>& birth) {
		surviveConditions = survive;
		birthConditions = birth;
	}

	// ==================== 获取规则字符串表示 ====================
	//将规则转换为字符串格式，如 "B3/S23"，返回规则字符串
	std::wstring getRulesString() const {
		std::wstring result = L"B";

		// 添加出生条件数字
		for (int condition : birthConditions) {
			result += std::to_wstring(condition);
		}

		result += L"/S";

		// 添加存活条件数字
		for (int condition : surviveConditions) {
			result += std::to_wstring(condition);
		}

		return result;
	}

	// ==================== 从字符串解析规则 ====================
	// 功能：从字符串解析游戏规则，支持格式如 "B3/S23" 或 "B36/S23"
	// 参数：rulesStr - 规则字符串
	bool parseRulesFromString(const std::wstring& rulesStr) {
		// 清空现有条件
		surviveConditions.clear();
		birthConditions.clear();

		// 查找关键字符位置
		// B：出生条件标识，S：存活条件标识，/：分隔符
		size_t bPos = rulesStr.find(L'B');
		size_t sPos = rulesStr.find(L'S');
		size_t slashPos = rulesStr.find(L'/');

		// 验证字符串格式是否有效
		if (bPos == std::wstring::npos || sPos == std::wstring::npos) {
			return false;  // 格式错误，缺少关键标识
		}

		// 解析出生条件
		// 从B字符后开始，到/分隔符结束
		for (size_t i = bPos + 1; i < slashPos && i < rulesStr.length(); i++) {
			if (iswdigit(rulesStr[i])) {  // 检查是否为数字字符
				birthConditions.push_back(rulesStr[i] - L'0');  // 转换为整数
			}
		}

		// 解析存活条件
		// 从S字符后开始，到字符串结束
		for (size_t i = sPos + 1; i < rulesStr.length(); i++) {
			if (iswdigit(rulesStr[i])) {  // 检查是否为数字字符
				surviveConditions.push_back(rulesStr[i] - L'0');  // 转换为整数
			}
		}

		// 验证解析结果，不能为空（至少要有出生和存活条件）
		return !(surviveConditions.empty() || birthConditions.empty());
	}

	// ==================== 判断细胞是否存活 ====================
	// 功能：当细胞当前为活细胞时，判断是否继续存活
	// 注意：该函数假定 currentState 为 true 时才有意义
	bool shouldSurvive(int aliveNeighbors, bool currentState) {
		// 如果当前是死细胞，直接返回false
		if (!currentState) return false;

		// 检查周围活细胞数是否满足任一存活条件
		for (int condition : surviveConditions) {
			if (aliveNeighbors == condition) return true;
		}
		return false;
	}

	// ==================== 判断细胞是否出生 ====================
	// 功能：当细胞当前为死细胞时，判断是否满足出生条件
	// 参数：aliveNeighbors - 周围活细胞数
	bool shouldBeBorn(int aliveNeighbors) {
		// 检查周围活细胞数是否满足任一出世条件
		for (int condition : birthConditions) {
			if (aliveNeighbors == condition) return true;
		}
		return false;
	}
};

// 辅助函数：将条件数组格式化为可读的中文描述，例如 "2或3"
std::wstring formatConditions(const std::vector<int>& conditions) {
	if (conditions.empty()) return L"无";

	std::wstring result;
	for (size_t i = 0; i < conditions.size(); i++) {
		if (i > 0) {
			result += L"或";
		}
		result += std::to_wstring(conditions[i]);
	}
	return result;
}

// 声明全局对象
bool map[ROWS][COLS] = { 0 };
GameRules gameRules;

// UI 组件声明
// 以下指针由 initializeUI() 分配，用于管理按钮、滑块、面板与标签等界面元素
Button* startButton;
Button* pauseButton;
Button* resetButton;
Button* rulesButton;
Button* gridToggleButton;
Slider* speedSlider;
Panel* controlPanel;
Label* generationLabel;
Label* modeLabel;
Label* populationLabel;

// 函数声明（实现位于同一文件）
void drawRect(int x, int y, bool flag);                     // 绘制单个格子
void drawMap(bool map[ROWS][COLS]);                         // 绘制整个地图（支持增量重绘）
DWORD WINAPI InputThreadProc(LPVOID param);                 // 输入线程回调
void lifeWeek(bool map[ROWS][COLS]);                        // 演化一代
int getRoundAlive(bool map[ROWS][COLS], int i, int j);      // 统计周围活细胞
int countPopulation(bool map[ROWS][COLS]);                  // 统计全地图活细胞数量
void initializeUI();                                        // 初始化 UI 组件
void updateUI();                                            // 更新 UI 状态并设置脏标志
void handleUIEvents(ExMessage& m);                          // 处理 UI 事件（鼠标等）
void cleanupUI();                                           // 释放 UI 资源
void drawGrid();                                            // 绘制网格线

// 初始化UI组件
void initializeUI() {
	int panelX = COLS * SPACE + 10;
	int panelY = 20;
	int panelWidth = 200;
	int panelHeight = 400;

	// 创建控制面板
	controlPanel = new Panel(panelX, panelY, panelWidth, panelHeight, L"生命游戏控制面板");

	// 创建按钮
	int buttonY = panelY + 40;
	int buttonWidth = 120;
	int buttonHeight = 30;
	int buttonSpacing = 10;

	startButton = new Button(panelX + 40, buttonY, buttonWidth, buttonHeight, L"开始演化");
	buttonY += buttonHeight + buttonSpacing;

	pauseButton = new Button(panelX + 40, buttonY, buttonWidth, buttonHeight, L"暂停");
	pauseButton->setEnabled(false);
	buttonY += buttonHeight + buttonSpacing;

	resetButton = new Button(panelX + 40, buttonY, buttonWidth, buttonHeight, L"重置");
	buttonY += buttonHeight + buttonSpacing;

	rulesButton = new Button(panelX + 40, buttonY, buttonWidth, buttonHeight, L"规则设置");
	buttonY += buttonHeight + buttonSpacing;

	gridToggleButton = new Button(panelX + 40, buttonY, buttonWidth, buttonHeight, L"隐藏网格");
	buttonY += buttonHeight + buttonSpacing + 20;

	// 创建滑块
	speedSlider = new Slider(panelX + 20, buttonY, 160, 30, 1.0f, 20.0f, gameSpeed, L"演化速度");
	buttonY += 60;

	// 创建标签
	generationLabel = new Label(panelX + 20, buttonY, L"代数: 0");
	buttonY += 25;

	modeLabel = new Label(panelX + 20, buttonY, L"模式: 设置中");
	buttonY += 25;

	populationLabel = new Label(panelX + 20, buttonY, L"种群: 0");

	// 初始缓存（迫使首次绘制）
	prevGenerationText.clear();
	prevModeText.clear();
	prevPopulationText.clear();
	prevStartText.clear();
	prevPauseText.clear();
	prevResetText.clear();
	prevRulesText.clear();
	prevGridText.clear();
	prevSliderValue = -1.0f;
	uiDirty = true;

	// 设置按钮回调函数（回调中标记 UI 脏）
	startButton->setOnClick([]() {  // Lambda表达式定义匿名回调函数
		currentMode = MODE_RUNNING;      // 切换到运行模式
		startButton->setEnabled(false);  // 禁用开始按钮（因为已经在运行）
		pauseButton->setEnabled(true);   // 启用暂停按钮
		modeLabel->setText(L"模式: 运行中");  // 更新模式显示文本
		uiDirty = true;                  // 标记UI需要重绘（因为状态改变了）
		});

	pauseButton->setOnClick([]() {
		currentMode = MODE_PAUSED;       // 切换到暂停模式
		startButton->setEnabled(true);   // 启用开始按钮（可以从暂停继续）
		pauseButton->setEnabled(false);  // 禁用暂停按钮（因为已经暂停）
		modeLabel->setText(L"模式: 已暂停");
		uiDirty = true;
		});

	resetButton->setOnClick([]() {
		currentMode = MODE_SETUP;        // 切换到设置模式
		generation = 0;                  // 重置代数计数器

		// === 重置地图数据（需要线程安全）===
		EnterCriticalSection(&mapLock);   // 加锁保护共享地图数据
		memset(map, 0, sizeof(map));     // 将地图所有细胞置为死亡（清零）
		LeaveCriticalSection(&mapLock);   // 解锁

		// === 重置UI状态 ===
		startButton->setEnabled(true);   // 启用开始按钮
		pauseButton->setEnabled(false);  // 禁用暂停按钮
		modeLabel->setText(L"模式: 设置中");
		generationLabel->setText(L"代数: 0");
		populationLabel->setText(L"种群: 0");

		// === 新增：重置时恢复优化状态 ===
		memset(prevMap, 0, sizeof(prevMap));  // 清空前一帧状态缓存
		firstDraw = true;                     // 标记需要完整重绘
		uiDirty = true;                       // 标记UI需要重绘
		});

	// === 修改：完整的自定义规则设置 ===
	rulesButton->setOnClick([]() {
		// 获取当前规则字符串（如"B3/S23"）
		std::wstring currentRules = gameRules.getRulesString();

		// 准备输入对话框缓冲区（预填充当前规则）
		wchar_t customRules[100] = { 0 };
		wcscpy_s(customRules, currentRules.c_str());  // 安全拷贝字符串

		// 使用EasyX的输入框让用户自定义规则
		// InputBox参数说明：
		// customRules: 输入/输出缓冲区
		// 100: 缓冲区最大长度
		// L"自定义生命游戏规则": 对话框标题
		// L"请输入自定义规则格式...": 提示信息
		// currentRules.c_str(): 默认显示内容
		// 350: 对话框宽度
		// 0: 对话框高度（0表示自适应）
		// true: 只显示确定按钮（简化界面）
		if (InputBox(customRules, 100, L"自定义生命游戏规则",
			L"请输入自定义规则格式：\n例如：\nB3/S23 表示：\n- 出生条件：周围有3个细胞\n- 存活条件：周围有2或3个细胞\n\nB36/S23 表示：\n- 出生条件：周围有3或6个细胞\n- 存活条件：周围有2或3个细胞\n\n当前规则：",
			currentRules.c_str(), 350, 0, true)) {

			// 用户点击了确定按钮，尝试解析输入的规则
			if (gameRules.parseRulesFromString(customRules)) {
				// 解析成功，显示成功消息
				MessageBox(GetHWnd(),
					(L"规则设置成功！\n新规则：" + gameRules.getRulesString() +
						L"\n\n出生条件(B): 周围有" + formatConditions(gameRules.birthConditions) +
						L"个细胞\n存活条件(S): 周围有" + formatConditions(gameRules.surviveConditions) + L"个细胞").c_str(),
					L"规则设置", MB_OK | MB_ICONINFORMATION);  // 信息图标
			}
			else {
				// 解析失败，显示错误信息并恢复默认规则
				MessageBox(GetHWnd(),
					L"规则格式错误！\n请使用格式：B.../S...\n例如：B3/S23\n\nB：出生条件\nS：存活条件\n数字：邻居数量",
					L"错误", MB_OK | MB_ICONERROR);  // 错误图标
				// 恢复默认规则（保证程序有有效的规则）
				gameRules.setStandardRules();
			}
		}
		uiDirty = true;  // 无论是否成功修改规则，UI都需要更新
		});

	gridToggleButton->setOnClick([]() {
		showGrid = !showGrid;  // 切换网格显示状态（取反）
		// 根据新状态更新按钮文本
		gridToggleButton->setText(showGrid ? L"隐藏网格" : L"显示网格");
		// === 新增：切换网格显示时强制重绘 ===
		firstDraw = true;  // 需要完全重绘地图（网格线会影响所有单元格）
		uiDirty = true;
		});

	// 更新UI状态（仅当文本/值变化时标记 uiDirty）
	void updateUI() {
		// 1. 更新游戏速度（从滑块获取当前值）
		gameSpeed = speedSlider->getValue();

		// 2. 更新标签文本（使用脏标记优化，避免不必要的重绘）

		// 代数标签
		wchar_t genText[50];
		swprintf(genText, 50, L"代数: %d", generation);  // 格式化字符串
		std::wstring genWs = genText;
		if (genWs != prevGenerationText) {  // 检查文本是否改变
			generationLabel->setText(genText);
			prevGenerationText = genWs;      // 更新缓存
			uiDirty = true;                  // 标记需要重绘
		}

		// 模式标签（根据currentMode选择对应文本）
		std::wstring modeWs = (currentMode == MODE_RUNNING) ? L"模式: 运行中" :
			(currentMode == MODE_PAUSED) ? L"模式: 已暂停" : L"模式: 设置中";
		if (modeWs != prevModeText) {
			modeLabel->setText(modeWs);
			prevModeText = modeWs;
			uiDirty = true;
		}

		// 种群数量标签
		wchar_t popText[50];
		int population = countPopulation(map);  // 统计当前活细胞数量
		swprintf(popText, 50, L"种群: %d", population);
		std::wstring popWs = popText;
		if (popWs != prevPopulationText) {
			populationLabel->setText(popText);
			prevPopulationText = popWs;
			uiDirty = true;
		}

		// 3. 检测按钮文本变化（尽管按钮文本通常不变，但状态可能改变）
		// 例如：gridToggleButton文本会在"显示网格"/"隐藏网格"间切换
		std::wstring startText = startButton->getText();
		if (startText != prevStartText) {
			prevStartText = startText;
			uiDirty = true;
		}
		std::wstring pauseText = pauseButton->getText();
		if (pauseText != prevPauseText) {
			prevPauseText = pauseText;
			uiDirty = true;
		}
		std::wstring resetText = resetButton->getText();
		if (resetText != prevResetText) {
			prevResetText = resetText;
			uiDirty = true;
		}
		std::wstring rulesText = rulesButton->getText();
		if (rulesText != prevRulesText) {
			prevRulesText = rulesText;
			uiDirty = true;
		}
		std::wstring gridText = gridToggleButton->getText();
		if (gridText != prevGridText) {
			prevGridText = gridText;
			uiDirty = true;
		}

		// 4. 检测滑块值变化（使用浮点数容差比较）
		float sv = speedSlider->getValue();
		if (fabs(sv - prevSliderValue) > 1e-3f) {  // 容差0.001
			prevSliderValue = sv;
			uiDirty = true;
		}
	}

	// 处理UI事件（根据 update 返回决定是否需要重绘 UI）
	void handleUIEvents(ExMessage & m) {
		int mouseX = m.x;
		int mouseY = m.y;

		bool changed = false;  // 记录是否有UI状态改变

		// 依次调用每个UI组件的update方法处理事件
		// 使用|=操作符：只要有一个组件处理了事件，changed就为true
		changed |= startButton->update(mouseX, mouseY, m.message);
		changed |= pauseButton->update(mouseX, mouseY, m.message);
		changed |= resetButton->update(mouseX, mouseY, m.message);
		changed |= rulesButton->update(mouseX, mouseY, m.message);
		changed |= gridToggleButton->update(mouseX, mouseY, m.message);
		changed |= speedSlider->update(mouseX, mouseY, m.message);

		// 如果有任何UI状态改变，标记需要重绘
		if (changed) uiDirty = true;
	}

// 清理UI资源
void cleanupUI() {
	delete startButton;
	delete pauseButton;
	delete resetButton;
	delete rulesButton;
	delete gridToggleButton;
	delete speedSlider;
	delete controlPanel;
	delete generationLabel;
	delete modeLabel;
	delete populationLabel;
}

// 主程序
int main() {
	// 初始化图形窗口（增加宽度以容纳控制面板）
	initgraph(COLS * SPACE + 220, ROWS * SPACE);

	// 设置随机种子
	srand(static_cast<unsigned int>(time(NULL)));

	// 初始化同步对象
	InitializeCriticalSection(&mapLock);

	// 初始化UI
	initializeUI();

	// === 创建输入线程（线程安全处理鼠标输入，不干扰主线程的消息队列） ===
	g_running = true;
	g_inputThread = CreateThread(NULL, 0, InputThreadProc, (LPVOID)map, 0, NULL);
	if (!g_inputThread) {
		// 若线程创建失败，仍继续但提示（不影响核心功能）
		MessageBox(GetHWnd(), L"警告：输入线程创建失败，应用仍可运行但并发输入处理不可用。", L"警告", MB_OK | MB_ICONWARNING);
	}

	// === 新增：创建缓冲图像（双缓冲，但使用增量更新以优化重绘） ===
	IMAGE bufferImg;
	bufferImg.Resize(COLS * SPACE + 220, ROWS * SPACE);

	bool shouldExit = false;

	// 主游戏循环
	while (!shouldExit) {
		// 处理系统消息（响应窗口关闭等）
		MSG winMsg;
		while (PeekMessage(&winMsg, NULL, 0, 0, PM_REMOVE)) {
			if (winMsg.message == WM_CLOSE || winMsg.message == WM_QUIT) {
				shouldExit = true;
			}
			TranslateMessage(&winMsg);
			DispatchMessage(&winMsg);
		}
		if (shouldExit) break;

		// 处理 EasyX 鼠标消息（仅用于 UI 组件）
		ExMessage m;
		while (peekmessage(&m, EX_MOUSE)) {
			if (m.message == WM_LBUTTONDOWN || m.message == WM_LBUTTONUP ||
				m.message == WM_MOUSEMOVE || m.message == WM_RBUTTONDOWN) {
				// 先处理UI事件（按钮/滑块等）
				handleUIEvents(m);
				// 鼠标在地图区的实际地图编辑由输入线程处理（避免消息竞争）
			}
		}

		// 设置工作区到缓冲图像（后续所有绘制写入 bufferImg）
		SetWorkingImage(&bufferImg);

		// 首次绘制或需要完整重绘时清除缓冲区
		if (firstDraw) {
			cleardevice();
		}

		// 在缓冲中绘制游戏内容（实现增量重绘）
		drawMap(map);

		// 仅当 UI 发生变化时绘制 UI 区域（减少每帧覆盖）
		if (uiDirty || firstDraw) {
			controlPanel->draw();
			startButton->draw();
			pauseButton->draw();
			resetButton->draw();
			rulesButton->draw();
			gridToggleButton->draw();
			speedSlider->draw();
			generationLabel->draw();
			modeLabel->draw();
			populationLabel->draw();
			uiDirty = false;
		}
		// 恢复工作区到屏幕
		SetWorkingImage(NULL);

		// 一次性将缓冲图像显示到屏幕
		putimage(0, 0, &bufferImg);

		// 更新UI状态（标签、速度等），并根据变化设置 uiDirty（但不必立即重绘）
		updateUI();

		// 游戏逻辑更新
		if (currentMode == MODE_RUNNING) {
			lifeWeek(map);
			generation++;

			// 根据速度控制帧率
			int delayTime = static_cast<int>(1000.0f / gameSpeed);
			Sleep(delayTime);
		}
		else {
			Sleep(10); // 在设置和暂停模式下减少CPU占用
		}
	}

	// 退出前清理：停止输入线程并等待其结束
	g_running = false;
	if (g_inputThread) {
		WaitForSingleObject(g_inputThread, 1000);
		CloseHandle(g_inputThread);
		g_inputThread = NULL;
	}

	cleanupUI();
	DeleteCriticalSection(&mapLock);
	closegraph();
	return 0;
}

// 绘制单个细胞
void drawRect(int x, int y, bool flag) {
	if (flag) {
		setfillcolor(WHITE);
	}
	else {
		setfillcolor(BLACK);
	}

	setcolor(showGrid ? RGB(167, 167, 167) : BLACK);
	fillrectangle(x * SPACE, y * SPACE, x * SPACE + SPACE, y * SPACE + SPACE);
}

// 绘制网格
void drawGrid() {
	if (!showGrid) return;

	setcolor(RGB(167, 167, 167));
	for (int i = 0; i <= ROWS; i++) {
		line(0, i * SPACE, COLS * SPACE, i * SPACE);
	}
	for (int j = 0; j <= COLS; j++) {
		line(j * SPACE, 0, j * SPACE, ROWS * SPACE);
	}
}

// 绘制整个地图（支持增量重绘：仅重绘发生变化的格子；首次或全重绘时绘制全部）
void drawMap(bool map[ROWS][COLS]) {
	bool snapshot[ROWS][COLS];

	// 先拷贝地图快照（加锁）
	EnterCriticalSection(&mapLock);
	memcpy(snapshot, map, sizeof(snapshot));
	LeaveCriticalSection(&mapLock);

	if (firstDraw) {
		// 首次绘制：绘制全部内容并更新 prevMap
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				drawRect(j, i, snapshot[i][j]);
			}
		}
		// 绘制网格（覆盖在细胞上）
		drawGrid();
		memcpy(prevMap, snapshot, sizeof(prevMap));
		firstDraw = false;
		return;
	}

	// 增量重绘：只绘制与 prevMap 不同的单元格
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (snapshot[i][j] != prevMap[i][j]) {
				drawRect(j, i, snapshot[i][j]);
			}
		}
	}

	// 如果显示网格，单独绘制（网格线可能覆盖在改变的格子上）
	if (showGrid) {
		drawGrid();
	}

	// 更新 prevMap
	memcpy(prevMap, snapshot, sizeof(prevMap));
}

// 输入线程：直接读取鼠标与按键状态，线程安全地修改地图（避免与主线程消息队列冲突）
DWORD WINAPI InputThreadProc(LPVOID param) {
	bool (*pmap)[COLS] = (bool(*)[COLS])param;
	HWND hwnd = GetHWnd();
	POINT pt;

	while (g_running) {
		// 仅在设置模式下允许修改地图
		if (currentMode == MODE_SETUP) {
			if (GetCursorPos(&pt)) {
				ScreenToClient(hwnd, &pt);
				// 仅响应地图区域
				if (pt.x >= 0 && pt.x < COLS * SPACE && pt.y >= 0 && pt.y < ROWS * SPACE) {
					int row = pt.y / SPACE;
					int col = pt.x / SPACE;

					SHORT left = GetAsyncKeyState(VK_LBUTTON);
					SHORT right = GetAsyncKeyState(VK_RBUTTON);

					EnterCriticalSection(&mapLock);
					if (left & 0x8000) {
						pmap[row][col] = true;
					}
					else if (right & 0x8000) {
						pmap[row][col] = false;
					}
					LeaveCriticalSection(&mapLock);
					// 鼠标输入改变地图时也可能影响屏幕，需要重绘 UI/地图
					uiDirty = true;
				}
			}
		}
		Sleep(8); // 控制轮询频率
	}
	return 0;
}

// 细胞演化（线程安全：对 map 的写入使用临时数组并在写回时加锁）
void lifeWeek(bool map[ROWS][COLS]) {
	bool temp[ROWS][COLS] = { 0 };
	bool snapshot[ROWS][COLS];

	// 读取当前地图快照
	EnterCriticalSection(&mapLock);
	memcpy(snapshot, map, sizeof(snapshot));
	LeaveCriticalSection(&mapLock);

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			int num = getRoundAlive(snapshot, i, j);

			if (snapshot[i][j]) {
				// 存活细胞
				temp[i][j] = gameRules.shouldSurvive(num, true);
			}
			else {
				// 死亡细胞
				temp[i][j] = gameRules.shouldBeBorn(num);
			}
		}
	}

	// 写回主地图（加锁）
	EnterCriticalSection(&mapLock);
	memcpy(map, temp, sizeof(temp));
	LeaveCriticalSection(&mapLock);

	// 下一帧需要增量重绘：prevMap 已保存上一次显示状态，无需强制全重绘
	uiDirty = true;
}

// 获取周围存活细胞数量（基于传入快照安全计算）
int getRoundAlive(bool map[ROWS][COLS], int i, int j) {
	int num = 0;
	for (int di = -1; di <= 1; di++) {
		for (int dj = -1; dj <= 1; dj++) {
			if (di == 0 && dj == 0) continue;

			int ni = i + di;
			int nj = j + dj;

			if (ni >= 0 && ni < ROWS && nj >= 0 && nj < COLS && map[ni][nj]) {
				num++;
			}
		}
	}
	return num;
}

// 统计种群数量
int countPopulation(bool map[ROWS][COLS]) {
	int count = 0;
	bool snapshot[ROWS][COLS];

	EnterCriticalSection(&mapLock);
	memcpy(snapshot, map, sizeof(snapshot));
	LeaveCriticalSection(&mapLock);

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (snapshot[i][j]) count++;
		}
	}
	return count;
}