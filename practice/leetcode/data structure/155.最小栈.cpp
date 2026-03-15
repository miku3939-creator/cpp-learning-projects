/*
 * @lc app=leetcode.cn id=155 lang=cpp
 *
 * [155] 最小栈
 */

// @lc code=start
class MinStack
{
public:
    MinStack()
    {
        maxCapacity = 4;
        elements = new int[maxCapacity];
        minarray = new int[maxCapacity];
        topIndex = -1;
    }

    void push(int val)
    {
        if (topIndex == maxCapacity - 1)
        {
            int *old = elements;
            int *old2 =minarray;
            elements = new int[maxCapacity * 2];
            minarray = new int[maxCapacity * 2];
            for (int i = 0; i < maxCapacity; i++)
            {
                elements[i] = old[i];
                minarray[i]=old2[i];
            }
            maxCapacity *= 2;
            delete[] old;
            delete[]old2;
        }
        topIndex++;
        elements[topIndex] = val;
        if (topIndex == 0)
        {
            minarray[0] = val;
        }
        else
        {
            if (val < minarray[topIndex - 1])
                minarray[topIndex] = val;
            else
                minarray[topIndex] = minarray[topIndex - 1];
        }
    }

    void pop()
    {
        if (topIndex == -1)
            return;
        topIndex--;
    }

    int top()
    {
        if (topIndex == -1)
            return 0;
        return elements[topIndex];
    }

    int getMin()
    {
        if (topIndex == -1)
            return 0;
        return minarray[topIndex];
    }

private:
    int *elements;
    int topIndex;
    int maxCapacity;
    int *minarray;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
// @lc code=end
