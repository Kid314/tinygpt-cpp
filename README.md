# tinygpt-cpp

从零用 C++17 实现一个小型 GPT，并把它做成 LLM 系统学习实验台：Tensor、算子、自动求导、单 Block Transformer、文本训练与生成；之后在同一套代码上做 CPU 性能实验（分块、OpenMP、SIMD）和 CUDA 算子。

> 这是学习项目，不是生产框架。实现由学习者逐步完成；仓库先提供接口、构建脚本和第一个测试。

## 当前状态

学习进行中：M0 基础阶段，已完成二维 `Tensor`、逐元素 `add` 与 i-j-k `matmul`（S0–S4），下一步测量矩阵乘法耗时与 GFLOPS（S5）。

## 路线

| 阶段 | 内容 | 目标 |
| --- | --- | --- |
| M0 基础 | 环境、Tensor、基础算子、benchmark | CPU 上手写并测量矩阵乘法 |
| M1 求导 | 计算图、反向传播、有限差分检查 | 梯度正确 |
| M2 GPT | 单头单 Block、文本训练、保存与生成 | 真实 loss 下降并生成字符 |
| M3 性能 | 分块、OpenMP、SIMD、Roofline | 有改前/改后性能数字 |
| M4 CUDA | CUDA matmul / softmax / LayerNorm / attention | 本机 GPU 上的算子实验 |

## 构建与运行（Windows / MinGW）

```powershell
powershell -ExecutionPolicy Bypass -File scripts/build.ps1
```

构建脚本会优先使用 PATH 中的 `g++`；如果找不到，会提示你安装或显式指定编译器：

```powershell
powershell -ExecutionPolicy Bypass -File scripts/build.ps1 -Compiler "<g++ 的完整路径>"
```

## 学习文档

- [目标与约束](docs/GOAL.md)
- [实施计划](docs/PLAN.md)
- [学习进度](docs/PROGRESS.md)
- [下次继续学习](docs/NEXT_SESSION.md)
- [AI 协作规则](AGENTS.md)

## 目录

- `include/ktorch/`：公开头文件
- `src/`：C++ 实现（学习者补写）
- `tests/`：可执行测试
- `scripts/`：构建脚本
- `bench/`：性能实验（后续）

项目按小步推进：一次只做一个能在 30 分钟内验收的改动，先手算再写代码，测试通过才进入下一步。
