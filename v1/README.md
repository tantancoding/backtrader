# 设计
简单的分成了几个类
- 策略基类
- 移动平均类
- 资产记录类
- 统计信息类

使用 on_day()函数来模拟每日的策略的执行

# 编译
```
g++ -std=c++11 -g light_backtrader.cpp -o light_backtrader
```
