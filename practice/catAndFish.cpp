#include <iostream>
#include <ctime>
#include <string>
#include <locale>
#include <memory>
#include <vector>
#include <iomanip>
#include <map>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// 设置控制台编码（Windows）
void setConsoleEncoding() {
#ifdef _WIN32
    // Windows 下设置控制台为 UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    // Windows 下使用中文本地化
    try {
        locale::global(locale("chs"));
    } catch (...) {
        locale::global(locale(""));
    }
#else
    // Linux/macOS 下使用默认本地化
    try {
        locale::global(locale("C.UTF-8"));
    } catch (...) {
        locale::global(locale(""));
    }
#endif
    cout.imbue(locale());
    cin.imbue(locale());
}

class Fish;
class Cat {
public:
    string name;
    int level;
    int exp;
    int totalFishCaught;
    map<string, int> fishCount;  // 记录每种鱼的数量
    
    void CatchFish(Fish &fish);
    void display();
    void displayStatistics();
    Cat(string n, int l = 0, int e = 0, int sum = 0) : 
        name(n), level(l), exp(e), totalFishCaught(sum) {}
};

// 改进的随机数生成函数
int generateRandomWeight(int minWeight, int maxWeight) {
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned int>(time(NULL)));
        seeded = true;
    }
    return rand() % (maxWeight - minWeight + 1) + minWeight;
}

class Fish {
public:
    int weight;
    int expValue;
    string typeName;  // 添加鱼的类型名称
    
    virtual void displayInfo() = 0;
    Fish(int w, int e, string name) : weight(w), expValue(e), typeName(name) {}
    virtual ~Fish() = default;
    
    string getTypeName() const { return typeName; }
};

class Octopus : public Fish {
public:
    Octopus();
    void displayInfo() override;
};

class Whale : public Fish {
public:
    Whale();
    void displayInfo() override;
};

class GoldFish : public Fish {
public:
    GoldFish();
    void displayInfo() override;
};

class Shark : public Fish {
public:
    Shark();
    void displayInfo() override;
};

class ClownFish : public Fish {
public:
    ClownFish();
    void displayInfo() override;
};

// 构造函数实现
Octopus::Octopus() : Fish(generateRandomWeight(10, 20), 0, "章鱼") {
    expValue = 2 * weight;  // 章鱼经验值是重量的2倍
}
Whale::Whale() : Fish(generateRandomWeight(1000, 2000), 200, "鲸鱼") {}
Shark::Shark() : Fish(generateRandomWeight(25, 50), 0, "鲨鱼") {
    expValue = -5 * weight;  // 鲨鱼减少经验值是重量的5倍
}
GoldFish::GoldFish() : Fish(generateRandomWeight(1, 3), 500, "金鱼") {}
ClownFish::ClownFish() : Fish(generateRandomWeight(1, 3), 0, "小丑鱼") {
    expValue = 3 * weight;  // 小丑鱼经验值是重量的3倍
}

// 实现 displayInfo 函数
void Octopus::displayInfo() {
    cout << "🎣 钓到了章鱼！重量=" << weight << "kg, 经验值=" << expValue << endl;
}

void Whale::displayInfo() {
    cout << "🐋 钓到了鲸鱼！重量=" << weight << "kg, 经验值=" << expValue << endl;
}

void GoldFish::displayInfo() {
    cout << "🐠 钓到了金鱼！重量=" << weight << "kg" << endl;
    cout << "✨ 特殊效果：直接升一级！" << endl;
}

void Shark::displayInfo() {
    cout << "🦈 钓到了鲨鱼！重量=" << weight << "kg, 损失经验=" << -expValue << endl;
}

void ClownFish::displayInfo() {
    cout << "🎭 钓到了小丑鱼！重量=" << weight << "kg, 经验值=" << expValue << endl;
}

void Cat::CatchFish(Fish& fish) {
    cout << "\n=== 钓鱼结果 ===" << endl;
    fish.displayInfo();
    
    int oldLevel = level;
    int oldExp = exp;
    
    exp += fish.expValue;
    if (exp < 0)
        exp = 0;
    
    // 处理升级（普通经验升级）
    while (exp >= 500) {
        level++;
        exp -= 500;
        cout << "🎉 升级啦！当前等级：" << level << endl;
    }
    
    totalFishCaught++;
    fishCount[fish.typeName]++;  // 记录这种鱼的数量
    
    // 特殊处理金鱼（直接升级）
    if (fish.typeName == "金鱼") {
        level++;
        exp = 0;  // 金鱼升级后经验清零
        cout << "✨ 金鱼特效生效：直接升一级！" << endl;
    }
    
    cout << "\n📊 属性变化：" << endl;
    cout << "经验值：" << oldExp << " → " << exp << " (";
    if (fish.expValue >= 0)
        cout << "+" << fish.expValue;
    else
        cout << fish.expValue;
    cout << ")" << endl;
    
    if (level > oldLevel) {
        cout << "等级：" << oldLevel << " → " << level << endl;
    }
    
    display();
}

void Cat::display() {
    cout << "\n=== 小猫属性 ===" << endl;
    cout << "名字：" << name << endl;
    cout << "等级：" << level << endl;
    cout << "经验：" << exp << "/500" << endl;
    cout << "捕鱼总数：" << totalFishCaught << "条" << endl;
    cout << "==============" << endl;
}

void Cat::displayStatistics() {
    cout << "\n📈 === 钓鱼统计 ===" << endl;
    cout << "钓鱼种类和数量：" << endl;
    
    for (const auto& [fishType, count] : fishCount) {
        cout << "  " << fishType << ": " << count << "条" << endl;
    }
    
    if (totalFishCaught > 0) {
        double sharkRate = (fishCount.count("鲨鱼") ? fishCount["鲨鱼"] : 0) * 100.0 / totalFishCaught;
        cout << fixed << setprecision(2);
        cout << "\n📊 鲨鱼概率分析：" << endl;
        cout << "钓到鲨鱼的概率: " << sharkRate << "%" << endl;
        
        if (sharkRate > 20.0) {
            cout << "⚠️  警告：小猫运气差！鲨鱼概率超过20%" << endl;
        } else if (sharkRate == 0) {
            cout << "🎊 恭喜！一次鲨鱼都没遇到！" << endl;
        } else {
            cout << "🍀 运气不错！鲨鱼概率在正常范围内" << endl;
        }
    }
    cout << "=================" << endl;
}

// 随机生成鱼的工厂函数
unique_ptr<Fish> createRandomFish() {
    int choice = generateRandomWeight(1, 100);  // 1-100的随机数
    
    // 设置各种鱼的概率
    if (choice <= 30) {        // 30% 章鱼
        return make_unique<Octopus>();
    } else if (choice <= 55) { // 25% 小丑鱼
        return make_unique<ClownFish>();
    } else if (choice <= 75) { // 20% 鲸鱼
        return make_unique<Whale>();
    } else if (choice <= 90) { // 15% 鲨鱼
        return make_unique<Shark>();
    } else {                   // 10% 金鱼
        return make_unique<GoldFish>();
    }
}

int main() {
    // 设置编码
    setConsoleEncoding();
    
    string name;
    cout << "🐱 ===========================" << endl;
    cout << "   欢迎来到小猫钓鱼游戏！" << endl;
    cout << "=============================" << endl;
    cout << "\n请输入小猫的名字：";
    cin >> name;
    
    Cat cat(name);
    cout << "\n开始小猫钓鱼游戏..." << endl;
    cat.display();
    
    char continueFishing = 'y';
    int round = 1;
    
    while (continueFishing == 'y' || continueFishing == 'Y') {
        cout << "\n🎮 === 第 " << round << " 次钓鱼 ===" << endl;
        cout << "按回车键开始钓鱼...";
        cin.ignore();
        cin.get();
        
        // 随机钓鱼
        unique_ptr<Fish> fish = createRandomFish();
        cat.CatchFish(*fish);
        
        round++;
        
        if (cat.totalFishCaught >= 50) {
            cout << "\n🎯 已达到最大钓鱼次数限制！" << endl;
            break;
        }
        
        cout << "\n是否继续钓鱼？(y/n): ";
        cin >> continueFishing;
    }
    
    cout << "\n🎮 ===========================" << endl;
    cout << "       游戏结束！" << endl;
    cout << "=============================" << endl;
    
    // 显示最终属性
    cat.display();
    
    // 显示统计信息
    cat.displayStatistics();
    
    // 总结评价
    cout << "\n📝 === 游戏评价 ===" << endl;
    if (cat.level >= 10) {
        cout << "🏆 钓鱼大师！等级非常高！" << endl;
    } else if (cat.level >= 5) {
        cout << "👍 表现不错！继续努力！" << endl;
    } else {
        cout << "💪 刚刚开始，还有进步空间！" << endl;
    }
    
    if (cat.fishCount.count("鲨鱼") && cat.fishCount["鲨鱼"] > cat.totalFishCaught * 0.2) {
        cout << "😿 今天运气不太好，遇到了太多鲨鱼..." << endl;
    } else if (cat.fishCount.count("金鱼") && cat.fishCount["金鱼"] >= 3) {
        cout << "🍀 幸运的小猫！钓到了不少金鱼！" << endl;
    }
    
    cout << "感谢游玩，再见！" << endl;
    
    // 按任意键继续（仅Windows）
#ifdef _WIN32
    cout << "\n按任意键退出..." << endl;
    system("pause");
#endif
    
    return 0;
}