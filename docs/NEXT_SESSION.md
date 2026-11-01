# 下次继续学习：怎么开始

## 0. 最简方式（能读本地文件的 AI）

新开对话后，**只发一句**：

```text
继续学习
```

AI 会按根目录 `AGENTS.md` 的“触发词：继续学习”自动读文档、跑基线、接上当前步骤（S4 matmul）。

下面第一节的长提示是给“读不了本地文件”的网页版 AI 用的，能读目录时不需要。

> 这是给“新开对话 / 换一个 AI”用的接续说明。请在项目根目录工作。

## 一、最省事的做法

新开对话后，把下面这段**原样复制**给 AI：

```text
这是 tinygpt-cpp 学习项目，请在项目根目录工作。

请先读：AGENTS.md、docs/GOAL.md、docs/PLAN.md、docs/PROGRESS.md、docs/NEXT_SESSION.md。

规则：
- 我自己写 C++ 实现；你负责写测试、讲解、审查、更新本地进度文档。
- 一次只推进一个 30 分钟小步；不要顺手实现后面的任务。
- 公开文档（docs/ 除 private 外）会提交到 GitHub；docs/private/ 和会话记录只留本地。
- 不要修改 docs/GOAL.md 和 docs/PLAN.md 里的范围，除非我明确同意。
- 本版本不做教学网页。

当前进度：S0～S3 已完成（Tensor 与 add），下一步 S4 matmul。

请先运行基线确认环境：
powershell -ExecutionPolicy Bypass -File scripts/build.ps1
powershell -ExecutionPolicy Bypass -File scripts/build.ps1 -Test tests/test_ops.cpp

然后给我 S4 的目标、手算例子和验收标准；先不要直接给实现代码，我会自己写。
```

## 二、当前状态（2026-11-02）

- 已完成：S0 环境、S1 Tensor 形状、S2 Tensor 访问、S3 逐元素 add。
- 下一步：S4 matmul（先 i-j-k 三重循环）。
- 代码已推送到 GitHub（`main`）；个人背景只在本机 `docs/private/`。
- 本地文档：`docs/PROGRESS.md` 是唯一进度来源；`docs/PLAN.md` 是任务表。

## 三、AI 能不能读本地文件

- **能读本地文件的 AI**（DSH、Claude Code、Codex、Cursor、Copilot 工作区等）：直接给它上面的提示，它自己读文件。
- **只能网页聊天、不能访问你磁盘的 AI**（普通网页版 ChatGPT/Claude 等）：它看不到 `docs/`。需要你：
  1. 把 `docs/PROGRESS.md` 和 `docs/PLAN.md` 的内容粘贴给它；
  2. 把当前要改的 `include/ktorch/ops.hpp`、`src/ops.cpp` 粘贴给它；
  3. 它给测试/讲解，你自己回车运行。
  这样能用，但效率低于能读文件的 AI。

## 四、你自己每次的检查清单

1. 打开终端，进入项目根目录。
2. 跑一次 `git status`，确认没有奇怪的未提交改动。
3. 跑基线测试（见上）。
4. 新对话粘贴启动提示，或直接说“读 docs/PROGRESS.md，从 S4 开始”。
5. 学完后让 AI 更新 `docs/PROGRESS.md` 和本地私有 session。

## 五、不要把本地资料弄丢

- `docs/` 与 `AGENTS.md` 会公开到 GitHub；`docs/private/`（个人背景）和会话记录只在本地。
- 换电脑时，把整个项目文件夹复制过去（至少复制 `docs/private/` 和 `AGENTS.md`）。
- 旧项目归档在本机备份目录（不在仓库内，路径不公开），里面有旧的教材/参考答案。
