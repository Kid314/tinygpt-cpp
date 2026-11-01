# 实施计划（2026-11-01 重写）

## 原则

1. **代码优先**：先手算一个小例子，再写代码，再跑测试；不写用不上的文档。
2. **一次一步**：每个步骤 30～60 分钟，有明确的验收命令和输出。
3. **记录数字**：benchmark 必须记录机器、尺寸、耗时、GFLOPS。
4. **不阻塞**：卡住超过 30 分钟就写进 session，下一轮先讲思路。

## 考试前：每天 30 分钟（S0～S10）

| 步骤 | 任务 | 验收 |
| --- | --- | --- |
| S0 | 读 `README.md`、`scripts/build.ps1`、`tests/test_tensor.cpp`；运行一次构建 | 看到 `ERROR: TODO(S1)...`；能说出 g++ 命令、include、src、test 的关系 |
| S1 | 实现 `Tensor` 构造、`rows/cols/size` | 构建通过，报错推进到 `TODO(S2)` |
| S2 | 实现 `at()`、`data()`、越界检查 | 输出 `PASS: tensor` |
| S3 | 新建 `include/ktorch/ops.hpp`、`src/ops.cpp`、`tests/test_ops.cpp`，实现逐元素 `add` | 2×3 手算相加通过 |
| S4 | 实现 `matmul`（三重循环，先 i-j-k） | 3×3 手算；`2×3 @ 3×2` 非方阵结果正确 |
| S5 | 写 `bench/bench_matmul.cpp`，测 64/256 方阵耗时与 GFLOPS | 记录数字到 `docs/PROGRESS.md` |
| S6 | 改成 i-k-j 循环，重复 S5 | 记录两种顺序的耗时与倍数 |
| S7 | 稳定 softmax（一行，减最大值） | `[1001,1002,1003]` 概率≈`[0.090031,0.244728,0.665241]` |
| S8 | 交叉熵（接收 logits 与 target，按行平均） | target=2 时 loss≈0.407606 |
| S9 | GELU 的 tanh 近似 | x=1 时≈0.841192；x=0 导数为 0.5（先只做前向） |
| S10 | LayerNorm 前向（γ=1、β=0） | `[-1,0,1]` → ≈`[-1.224736,0,1.224736]` |

> 每步如果超过 60 分钟，拆成两个 30 分钟步骤；不要跳过手算。

## 考试后里程碑

| 阶段 | 时间（拟定） | 内容 | 验收 |
| --- | --- | --- | --- |
| M1 自动求导 | 12/21–1/10 | `grad`、计算图、add/mul/matmul 反向、有限差分 | 小矩阵梯度通过有限差分 |
| M2 单 Block GPT | 1/11–2/7 | gather、LayerNorm/GELU/softmax/CE 反向；单头因果注意力、MLP、绑定 E；训练 `data/tiny.txt`；保存与生成 | 真实 loss 下降；checkpoint 重建后 logits 一致；能逐字符生成 |
| M3 CPU 性能 | 2/8–2/28 | tiling、OpenMP、AVX2、Roofline、profile | 有改前/改后数字与解释 |
| M4 CUDA | 1 月起并行 | 环境、vector add、tiled matmul、softmax/LN、attention、Nsight | 本机 GPU 上跑通并记录耗时 |
| M5 推理引擎 | 2027 春 | mini 推理引擎：KV Cache、连续批处理、量化、HTTP | 可在本机跑通并给出延迟/吞吐 |

## CPU 模拟 GPU 的练法（M3 与 M4 前）

- **GPU thread ↔ CPU 线程**：OpenMP `parallel for` 按输出元素并行。
- **shared memory ↔ 缓存分块**：matmul 分块，让同一行/列重复使用 cache。
- **warp/SIMD ↔ AVX2**：一次处理 4 个 double，观察加速比。
- **branch divergence**：写一个带分支的 kernel，比较数据分布对性能的影响。
- **Roofline**：算 `FLOPs/byte`，判断是算力受限还是带宽受限。
- 每个练习都记录：输入尺寸、循环顺序、线程数、耗时、GFLOPS。

## 怎么用这个计划

- 开始一步前，先读该步目标，在纸上手算小例子。
- 写代码只改这一步需要的文件；不要顺手扩展。
- 运行 `powershell -ExecutionPolicy Bypass -File scripts/build.ps1`。
- 通过后更新 `docs/PROGRESS.md`；失败就把错误原文记进 session。
- 卡住超过 30 分钟：先描述“我期望什么、实际看到什么”，再要提示。

## 资源

- C++：cppreference；《Effective Modern C++》；CSAPP 第 3、6 章。
- 系统：OSTEP；CS144；MIT 6.S081。
- 并行：Stanford CS149；OpenMP 文档；CUDA C++ Programming Guide；《Programming Massively Parallel Processors》；Nsight Systems/Compute。
- AI Infra 中文路线：[AIInfraGuide](https://github.com/caomaolufei/AIInfraGuide)、[minivllm](https://github.com/feiguangba/minivllm)。
- 课程：CMU 10-714（Deep Learning Systems）、Stanford CS336（Language Modeling from Scratch）、MLSys 论文。
- 工程参考：vLLM、SGLang、llama.cpp、DeepGEMM、FlashMLA 源码。
