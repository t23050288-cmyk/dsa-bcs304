# Data Structures and Applications (BCS304) — VTU Important Questions

This repo has **exam-ready, structured answers** for VTU 3rd semester "Data Structures
and Applications" (BCS304, 2025 Scheme).

Source material: 8 previous-year BCS304 papers (Dec 2023 → Dec 2025, + Model Paper)
+ the official class notes (vtucode.in). Notes used as reference, not copied
word-for-word — answers are written to be easy, understandable, and sufficient for
full marks at a 3rd sem level. Language used for all programs: **C** (this course is
in C, not Java — different subject from the `oops` repo).

## ⚠️ Syllabus flag — read before studying (Module 1)

Several previous-year questions ask about **Pattern Matching / KMP algorithm** and
**string handling functions** (compare/concatenate/reverse strings). Neither topic is
explicitly named in the new 5-module 2025-scheme syllabus for BCS304 — they were part
of the *old* syllabus's Module 1. They're included in Module 1 (since they show up
repeatedly in PYQs), but **verify with your professor** whether they're still
examinable.

## How every answer is structured

For every concept/question:

1. **Definition** — one or two lines, exam-safe.
2. **Points** — 5 to 10 easy bullet points explaining it.
3. **Syntax** — wherever applicable.
4. **Easiest Program** — a clean, complete, working C solution.
5. **Smallest Program** — the shortest valid version that still answers the question.

All standalone `.c` programs in this repo have been **compiled and run** (via `gcc`)
to confirm they work correctly before being added.

## Contents

### Module 1 — Introduction to Data Structures, Arrays, Structures & Sparse Matrices

| Format | Where |
|---|---|
| **Question-Answer** (each question exactly as in the IMP PDF, answer below it) | [Module1-Question-Answers/](Module1-Question-Answers/) — 8 files, one per paper |
| **Topic-organized** (by concept, with question-mapping index) | [Module1-DataStructures-Intro/](Module1-DataStructures-Intro/) — 8 files + `programs/` |
| **Definitions Cheat Sheet** (every term, one-line summaries at the end) | [Module1-Definitions-CheatSheet.md](Module1-Definitions-CheatSheet.md) |

Topic files: [01-Data-Structures-Intro-Classification.md](Module1-DataStructures-Intro/01-Data-Structures-Intro-Classification.md) ·
[02-Pointers-and-Dynamic-Memory-Allocation.md](Module1-DataStructures-Intro/02-Pointers-and-Dynamic-Memory-Allocation.md) ·
[03-Arrays-in-C.md](Module1-DataStructures-Intro/03-Arrays-in-C.md) ·
[04-Structures-and-Unions.md](Module1-DataStructures-Intro/04-Structures-and-Unions.md) ·
[05-Polynomials.md](Module1-DataStructures-Intro/05-Polynomials.md) ·
[06-Sparse-Matrices.md](Module1-DataStructures-Intro/06-Sparse-Matrices.md) ·
[07-Pattern-Matching-and-Strings.md](Module1-DataStructures-Intro/07-Pattern-Matching-and-Strings.md) ⚠️ ·
[08-Question-Mapping-Index.md](Module1-DataStructures-Intro/08-Question-Mapping-Index.md)

### Module 2 — Stacks, Stack Applications & Queues (linear)

| Format | Where |
|---|---|
| **Question-Answer** (each question exactly as in the IMP PDF, answer below it) | [Module2-Question-Answers/](Module2-Question-Answers/) — 8 files, one per paper |
| **Topic-organized** (by concept, with question-mapping index) | [Module2-Stacks-Queues/](Module2-Stacks-Queues/) — 6 files + `programs/` |
| **Definitions Cheat Sheet** (every term, one-line summaries at the end) | [Module2-Definitions-CheatSheet.md](Module2-Definitions-CheatSheet.md) |

Topic files: [01-Stack-Definition-ADT-Operations.md](Module2-Stacks-Queues/01-Stack-Definition-ADT-Operations.md) ·
[02-Array-Representation-of-Stack.md](Module2-Stacks-Queues/02-Array-Representation-of-Stack.md) ·
[03-Stack-Applications-Polish-Notation.md](Module2-Stacks-Queues/03-Stack-Applications-Polish-Notation.md) ·
[04-Evaluation-of-Postfix-Expression.md](Module2-Stacks-Queues/04-Evaluation-of-Postfix-Expression.md) ·
[05-Queue-Definition-Array-Representation.md](Module2-Stacks-Queues/05-Queue-Definition-Array-Representation.md) ·
[06-Question-Mapping-Index.md](Module2-Stacks-Queues/06-Question-Mapping-Index.md)

## Why three formats

- **Question-Answer** files let you revise **by paper** — exact wording from the
  IMP PDF, answer immediately below.
- **Topic-organized** files let you revise **by concept** — no duplicate answers
  across papers that ask the same thing differently, plus every runnable program.
- The **Cheat Sheet** is the fastest pre-exam skim — every term's definition in
  one place, with a one-line summary table at the end for quick recall.

More modules will be added here as they're prepared.
