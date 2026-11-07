# 学习进度

最后更新：2026-11-02 01:20 +08:00

## 项目

- 项目：tinygpt-cpp（C++17 手写小 GPT，后续 CPU 性能与 CUDA）
- 代码仓库：https://github.com/Kid314/tinygpt-cpp
- 计划文档：[PLAN.md](PLAN.md)
- 资料约定：`docs/` 与 `AGENTS.md` 自 2026-11-02 起也上传 GitHub；`build/`、缓存和编译产物不提交。
- 节奏：考试前每天最多 30 分钟；考试后集中推进；之后可用本机 GPU 做 CUDA。个人背景细节只在本地 `docs/private/`。

## 当前步骤

- 当前：**S4 matmul**（今天是 2026-11-02，先到这里）
- 下次开始：读 `docs/NEXT_SESSION.md`，按里面的提示启动新对话。
- S4 任务：实现 `matmul`（先 i-j-k 三重循环），AI 写测试覆盖 3×3 手算与 `2×3 @ 3×2` 非方阵。

## 考试前步骤（每天 30 分钟）

| 步骤 | 状态 | 实际证据 |
| --- | --- | --- |
| S0 环境与构建 | 已完成（2026-11-01） | 用户亲手运行 `powershell -ExecutionPolicy Bypass -File scripts/build.ps1`，输出 `ERROR: TODO(S1): implement Tensor(rows, cols, init)`，截图确认 |
| S1 Tensor 形状 | 已完成（2026-11-01） | 用户改完 `src/tensor.cpp`，构建输出从 `TODO(S1)` 推进到 `ERROR: TODO(S2): implement at(i, j)`，截图确认 |
| S2 Tensor 访问 | 已完成（2026-11-02） | 用户实现 `at()`/`data()` 与越界检查，构建输出 `PASS: tensor`；已补 0 维 `std::invalid_argument` 校验 |
| S3 add | 已完成（2026-11-02） | 用户实现 `ops.hpp`/`ops.cpp`；AI 写 `tests/test_ops.cpp`；构建输出 `PASS: ops`（5 类检查通过） |
| S4 matmul | 未开始 | — |
| S5 benchmark | 未开始 | — |
| S6 循环顺序 | 未开始 | — |
| S7 softmax | 未开始 | — |
| S8 cross entropy | 未开始 | — |
| S9 GELU | 未开始 | — |
| S10 LayerNorm | 未开始 | — |

## 里程碑

| 阶段 | 状态 | 证据 |
| --- | --- | --- |
| M1 自动求导 | 未开始 | — |
| M2 单 Block GPT | 未开始 | — |
| M3 CPU 性能 | 未开始 | — |
| M4 CUDA（本机 GPU） | 未开始 | — |
| M5 mini 推理引擎 | 未开始 | — |

## 学习日志

| 日期 | 做了什么 | 结果 / 证据 |
| --- | --- | --- |
| 2026-11-01 | 重规划项目：旧项目归档，新项目 tinygpt-cpp 初始化，建立 S0～S10 计划与本地进度文档 | 旧项目已归档到本机备份（路径不公开）；公开仓库历史已精简 |
| 2026-11-01 | 验证构建脚本（AI 代跑） | 编译通过，运行输出 `ERROR: TODO(S1)`，退出码 1（预期初始状态） |
| 2026-11-01 | 尝试推送 GitHub | 直连失败：`github.com:443` 连接超时；已记录，待代理可用 |
| 2026-11-02 | 推送 GitHub 成功 | 使用用户提供的代理推送成功（含代码与 docs）；本地已跟踪 origin/main |
| 2026-11-01 | S0 完成 | 用户运行构建脚本，确认输出 `ERROR: TODO(S1)`；理解 `init`、`data()`、`at()` 的含义 |
| 2026-11-01 | S1 完成 | 用户实现构造函数与 `rows/cols/size`；构建输出 `ERROR: TODO(S2): implement at(i, j)` |
| 2026-11-02 | S2 完成 | 用户实现 `at()`（const/非 const）与 `data()`；构建输出 `PASS: tensor`；审查发现缺少 0 维参数校验、错误信息过短，待收尾 |
| 2026-11-02 | S3 完成 | 用户修正 `ops.cpp`；AI 写 `tests/test_ops.cpp`；构建输出 `PASS: ops`；代码已本地提交 |
| 2026-11-02 | 路径清理 | `scripts/build.ps1` 去掉硬编码编译器路径，改为只认 PATH 或 `-Compiler`；README/PLAN/NEXT_SESSION/PROGRESS 中的本地绝对路径改为通用描述；公开 Git 历史压缩为一个初始提交，旧提交已从远端移除并本地清理 |
| 2026-11-02 | 隐私清理 | 个人背景移到本地 `docs/private/`；删除公开会话记录；重写公开 Git 历史，旧个人记录不再出现在远端分支 |
| 2026-11-02 | 验证新编译器 | 本机 GCC 16.2.0（MinGW-W64 UCRT, x86_64）编译并运行 `test_tensor`、`test_ops` 均 PASS；构建脚本改为优先使用 PATH 中的 g++ |
| 2026-11-02 | 今日结束 | 完成 S0～S3；下次从 S4 matmul 继续；详见 `docs/NEXT_SESSION.md` |

## 记录规则

- 只有实际运行并通过的测试/benchmark 才算证据；未运行写“未运行”。
- 每完成一步，更新对应状态和证据，并在 `docs/sessions/<窗口ID>.md` 追加过程记录。
- 计划和进度文档只保存在本机，不提交、不推送。

## 下一步

1. S4：实现 `matmul`（i-j-k 三重循环），AI 写 3×3 与非方阵测试；验收 `PASS: ops`。
2. 后续直接在项目目录 `git push` 即可（本机 `.git/config` 已配置代理，代理地址不写入仓库）。
3. 本版本不维护教学网页，讲解只在 docs 与对话中。
4. 下一次新对话先读 [NEXT_SESSION.md](NEXT_SESSION.md)。

## 2026-11-07 S4 实现审查与测试（追加，当前状态以此节为准）

- 用户已完成 `matmul` 声明与 i-j-k 三重循环实现，内维检查、输出形状、逐项累加和返回结果均正确。
- AI 扩展 `tests/test_ops.cpp`，覆盖 7 组 matmul 用例：3×3 手算、2×3 @ 3×2、2×3 @ 3×4、1×1 负数小数、向量内积、向量外积、内维不匹配异常；同时检查输入全部元素保持不变及结果存储独立。
- 实际命令：`powershell -ExecutionPolicy Bypass -File scripts/build.ps1 -Test tests/test_ops.cpp`。
- 真实输出：`PASS: matmul (7 cases)`、`PASS: ops`，退出码 0。
- 实际命令：`powershell -ExecutionPolicy Bypass -File scripts/build.ps1`。
- 真实输出：`PASS: tensor`，退出码 0。
- 两次构建均有 3 处 `[-Wsign-compare]` 警告，位置为 `src/ops.cpp:32`、`:34`、`:36`：`int` 循环变量与 `std::size_t` 尺寸比较。
- 当前状态：S4 功能验收通过，等待用户将三个循环变量改为 `std::size_t` 后复验收尾；AI 未代改实现。
- 下一步先完成上述收尾与提交推送，再开始 S5；本轮未运行 benchmark，未开展 S5。
- 本轮详细记录保存在被忽略的 `docs/private/sessions/`；公开文档随仓库提交，private 内容仅留本地。旧“记录规则”中的本地文档不提交表述已过时，以根目录 AGENTS.md 为准。

## 2026-11-07 S4 完成（追加，当前步骤与下一步以此节为准）

- 用户已将 `matmul` 的 i/j/k 三个循环变量改为 `std::size_t`，AI 未修改实现。
- 实际命令：`powershell -ExecutionPolicy Bypass -File scripts/build.ps1 -Test tests/test_ops.cpp`。
- 真实输出：`PASS: matmul (7 cases)`、`PASS: ops`，退出码 0，无编译警告。
- 实际命令：`powershell -ExecutionPolicy Bypass -File scripts/build.ps1`。
- 真实输出：`PASS: tensor`，退出码 0，无编译警告。
- **S4 matmul 已完成**：i-j-k 三重循环、手算与非方阵验收通过，类型警告已消除。
- **下一步为 S5 benchmark（未开始）**：由用户编写 `bench/bench_matmul.cpp`，测量 64/256 方阵耗时与 GFLOPS，记录机器与真实数字；本次未运行 benchmark。
- 接续说明与 README 已同步；目标和计划的范围未改变。公开代码、测试与文档纳入本步提交，私有会话记录仅留本地。
