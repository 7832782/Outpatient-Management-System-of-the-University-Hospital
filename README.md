# 大学门诊管理系统

Qt6 + C++ 的门诊管理系统课程设计，CMake 构建。

## 功能模块

- 患者、医生、药品、员工的基础信息管理
- 挂号、开具处方、收费、检查缴费
- 营收统计与领取记录查询

## 构建

需要 Qt6（Widgets 模块）与 CMake 3.16 以上：

```bash
cmake -B build -DCMAKE_PREFIX_PATH=<Qt6 的 cmake 目录>
cmake --build build
```

## 代码结构

`*window.*` 是各个界面，`*.h` 是对应的数据模型（patient、doctor、prescription、medicine、staff、cashier），`data.cpp` 负责数据的读写，`tool.cpp` 放公共工具函数。
