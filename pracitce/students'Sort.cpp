#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
/*【问题描述】
假设用C++定义了一个学生类，包含如下字段：
class Student {
private:
    int id;         // 学号
    int chinese;    // 语文
    int math;       // 数学
    int english;    // 英语
    int physics;    // 物理
    int chemistry;  // 化学
    int biology;    // 生物
    int total;      // 总分
public:
    Student (int id, int chinese, int math, int english, 
    int physics, int chemistry, int biology);
};
任务要求：
1. 补全Student类的构造函数，在构造函数中计算并初始化total字段。
2. 编写一个main函数，实现以下功能：
￮ 接收用户输入的学生信息，并将学生信息存入合适的STL容器中。
￮ 根据用户的选择进行排序：输入1,按照学号升序排序并输出学生信息;
输入2, 按照总分降序排序并输出学生信息。
￮ 用户输入的语文、数学和英语的分数介于0~150之间，
物理、化学、生物的分数介于0~100之间。
如果学生的任一成绩不在合法范围内，则该学生总成绩无效，
在排序输出时，该学生信息应置于最后，并在总分列标记“invalid”。
￮ 总成绩“invalid”的学生信息排在最后面（不论是按照学号排列，还是按照总分排列）
，若有多个学生总分无效，总分无效部分按照稳定排序方式进行（即：排序前顺序排列）
￮ 学生成绩合法性检查可在Student类的构造函数中实现。
￮ 建议：使用std::sort进行排序，编写函数对象或lambda表达式完成自定义排序逻辑。
￮ 可以适当在Student类中增加字段；可以适当改造构造函数；可以适当添加Student类的成员函数。
【输入形式】
• n个学生的测试用例由n+2行输入。第一行，表示学生的数量n
；接下来第2~（n+1）行表示学生的信息；
第n+2行，表示排序方式（1表示按学号排序，2表示按总分排序）。
• 学生信息由“学号 语文 数学 英语 物理 化学 生物”等7个整型数字组成，
学号编号为4位数字，第一位数字不为0。
【输出形式】
学号: 语文 数学 英语 物理 化学 生物 总分
注意，
• 学号后面是英文状态下的“:",后面有空格（space键）；
• 分数之间有空（space键）
• 总分后面没有空格，但有回车换行符。*/
class Student {
private:
    int id;         // 学号
    int chinese;    // 语文
    int math;       // 数学
    int english;    // 英语
    int physics;    // 物理
    int chemistry;  // 化学
    int biology;    // 生物
    int total;      // 总分
    bool valid;
public:

    Student(int id = 0, int chi = 0, int m = 0, int e = 0,
        int p = 0, int c = 0, int b = 0);
           // 获取成员函数
    int getId() const { return id; }
    int getTotal() const { return total; }
    bool isValid() const { return valid; }
    friend istream& operator >> (istream& cin,  Student& x);
    friend ostream& operator << (ostream& cout, const Student& x);
    friend bool compareById(const Student& a, const Student& b) ;
    friend bool compareByTotal(const Student& a, const Student& b) ;
};
Student::Student(int id, int chi, int m, int e,
    int p, int c, int b):id(id), chinese(chi), math(m),english(e),
    physics(p), chemistry(c), biology(b),total(chi+m+e+p+c+b){ 
    valid = (chi >= 0 && chi <= 150) &&
        (m >= 0 && m <= 150) &&
        (e >= 0 && e <= 150) &&
        (p >= 0 && p <= 100) &&
        (c >= 0 && c <= 100) &&
        (b >= 0 && b <= 100);

    // 计算总分
    if (valid) {
        total = chi + m + e + p + c + b;
    }
    else {
        total = -1;  // 标记无效成绩
    }
}

    


istream& operator >> (istream& cin,  Student& stu) {
    int id, chi, m, e, p, c, b;
    cin >> id >> chi >> m >> e >> p >> c >> b;
    Student temp(id, chi, m, e, p, c, b);
    stu = temp;
    return cin;
}


ostream& operator << (ostream& cout, const Student& x) {
    cout << x.id << ": ";
    cout << x.chinese << ' ';
    cout << x.math << ' ';
    cout << x.english << ' ';
    cout << x.physics << ' ';
    cout << x.chemistry << ' ';
    cout << x.biology << ' ';
    if (x.valid) {
        cout << x.total;
    }
    else {
        cout << "invalid";
    }
    cout << endl;

    return cout;
}
// 自定义排序比较函数
bool compareById(const Student& a, const Student& b) {
    // 有效成绩的排前面，无效的排后面
    if (a.isValid() != b.isValid()) {
        return a.isValid();  // true > false
    }
    // 都有效或都无效时，按学号升序
    return a.getId() < b.getId();
}

bool compareByTotal(const Student& a, const Student& b) {
    // 有效成绩的排前面，无效的排后面
    if (a.isValid() != b.isValid()) {
        return a.isValid();  // true > false
    }
    // 都无效时保持原顺序（稳定排序）
    if (!a.isValid() && !b.isValid()) {
        return false;  // 保持原顺序
    }
    // 都有效时，按总分降序
    return a.getTotal() > b.getTotal();
}

int main() {
    int n;
    cin >> n;
    
    vector<Student> students;
    students.reserve(n);
    
    // 输入学生信息
    for (int i = 0; i < n; i++) {
        Student stu;
        cin >> stu;
        students.push_back(stu);
    }
    
    int choice;
    cin >> choice;
    
    // 根据选择进行排序
    switch (choice) {
        case 1:  // 按学号排序
            // 使用稳定排序保持无效成绩部分的原顺序
            stable_sort(students.begin(), students.end(), compareById);
            break;
            
        case 2:  // 按总分排序
            // 先分离有效和无效成绩
            auto partition_point = partition(students.begin(), students.end(),
                [](const Student& s) { return s.isValid(); });
            
            // 对有效成绩部分按总分降序排序
            sort(students.begin(), partition_point,
                [](const Student& a, const Student& b) {
                    return a.getTotal() > b.getTotal();
                });
            // 无效成绩部分保持原顺序（已经在后面）
            break;
    }
    
    // 输出结果
    for (const auto& stu : students) {
        cout << stu;
    }
    
    return 0;
}
