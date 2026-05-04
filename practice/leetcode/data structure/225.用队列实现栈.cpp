/*
 * @lc app=leetcode.cn id=225 lang=cpp
 *
 * [225] 用队列实现栈
 */

// @lc code=start
class MyStack {
public:
 queue<int> q;
    MyStack() {
       
    }
    
    void push(int x) {
        q.push(x);
        for(int i=0;i<q.size()-1;i++){
            int j=q.front();
            q.pop();
            q.push(j);
        }
    }
    
    int pop() {
        int i=q.front();
        q.pop();
        return i;
    }
    
    int top() {
        return q.front();
    }
    
    bool empty() {
        return q.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
// @lc code=end

