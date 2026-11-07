# tinygpt-cpp 本地协作规则

## 触发词：继续学习

如果用户只发“`继续学习`”（或“继续学”“接着上次”），**不要要求用户粘贴长提示**，直接执行：

1. 读 `docs/GOAL.md`、`docs/PLAN.md`、`docs/PROGRESS.md`、`docs/NEXT_SESSION.md`。
2. 查 `git status`，并跑基线：
   - `powershell -ExecutionPolicy Bypass -File scripts/build.ps1`
   - `powershell -ExecutionPolicy Bypass -File scripts/build.ps1 -Test tests/test_ops.cpp`
3. 从 `docs/PROGRESS.md` 的“当前步骤/下一步”确定今天的小步，以最新追加记录为准。
4. 先向用户简短报告：上次做到哪、今天做哪一步、验收是什么；然后按教学流程走：
   先手算例子 → 用户自己写实现 → AI 写测试 → 跑通 → 更新 `docs/PROGRESS.md` 与 session。
5. 一次只做一个 30 分钟小步；不要替用户写实现，不要顺手做后面的步骤。
6. 如果测试失败，先贴真实错误和位置，再讲原因。

公开文档（AGENTS.md、docs/ 中除 private 外）随仓库上传 GitHub；`docs/private/`、个人背景和会话记录只留本地，不提交。

## 项目

- 用户用 C++17 从零实现一个小 GPT 与 LLM 系统实验：Tensor、算子、自动求导、单 Block Transformer、训练/生成、CPU 性能优化、CUDA 算子。
- 用户目标 AI Infra 方向；个人背景与时间细节见本地 `docs/private/CONTEXT.md`（不上传）。
- 用户自己写实现。AI 负责：搭骨架、写测试、讲解、审查、记录进度；**不代写整块实现**，除非用户明确要求。

## 每次开始

1. 读 `docs/GOAL.md`、`docs/PLAN.md`、`docs/PROGRESS.md`、本文件；**新对话/新 AI 第一次接手时再读 `docs/NEXT_SESSION.md`**。
2. 查 `git status`；按 `PLAN.md` 的下一步工作，只做一个 30 分钟可验收的小步。
3. 用户先自己写；卡住时先讲思路和最小例子，再给提示，最后才给代码。

## 每步结束

1. 更新 `docs/PROGRESS.md`：步骤状态、实际命令、真实输出。
2. 在本窗口 `docs/private/sessions/<窗口ID>.md` 记录（本地忽略，不上传）：改了什么、为什么、验证结果、未运行项。
3. 公开文档（AGENTS.md、docs/ 中除 private 外）提交并推送 GitHub；`docs/private/` 与会话记录只留本地；不要提交 build/、*.exe、__pycache__ 等产物。

## 验证与真实

- 构建失败就是失败；0 个测试不算通过。
- 记录真实命令与输出；没跑的检查写“未运行”。
- 不把教学示例数字当成实际运行结果。

## 修改授权

- 未经用户同意，不修改 `docs/GOAL.md` 与 `docs/PLAN.md` 的范围和目标。
- `docs/PROGRESS.md` 与本窗口 session 可随工作更新（只追加，不覆盖他人记录）。
