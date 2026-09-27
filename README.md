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

| File | Covers |
|---|---|
| [01-Data-Structures-Intro-Classification.md](Module1-DataStructures-Intro/01-Data-Structures-Intro-Classification.md) | What is a Data Structure, Primitive vs Non-Primitive, Linear vs Non-Linear, the 7 DS Operations |
| [02-Pointers-and-Dynamic-Memory-Allocation.md](Module1-DataStructures-Intro/02-Pointers-and-Dynamic-Memory-Allocation.md) | Pointers, malloc/calloc/realloc/free, static vs dynamic allocation, dangling references |
| [03-Arrays-in-C.md](Module1-DataStructures-Intro/03-Arrays-in-C.md) | 1D/2D arrays in C, address calculation, dynamically allocated arrays |
| [04-Structures-and-Unions.md](Module1-DataStructures-Intro/04-Structures-and-Unions.md) | struct vs union, typedef, self-referential structures |
| [05-Polynomials.md](Module1-DataStructures-Intro/05-Polynomials.md) | Polynomial ADT, array representation, polynomial addition |
| [06-Sparse-Matrices.md](Module1-DataStructures-Intro/06-Sparse-Matrices.md) | Sparse matrix definition, triplet representation, transpose |
| [07-Pattern-Matching-and-Strings.md](Module1-DataStructures-Intro/07-Pattern-Matching-and-Strings.md) | ⚠️ Flagged topic: KMP algorithm, string handling functions without built-ins |
| [08-Question-Mapping-Index.md](Module1-DataStructures-Intro/08-Question-Mapping-Index.md) | Every Module 1 IMP question mapped to its answer |
| [programs/](Module1-DataStructures-Intro/programs/) | Standalone runnable `.c` files for Module 1 |

### Module 2 — Stacks, Stack Applications & Queues (linear)

| File | Covers |
|---|---|
| [01-Stack-Definition-ADT-Operations.md](Module2-Stacks-Queues/01-Stack-Definition-ADT-Operations.md) | Stack definition, LIFO, ADT stack (push/pop/top/size/isEmpty/isFull) |
| [02-Array-Representation-of-Stack.md](Module2-Stacks-Queues/02-Array-Representation-of-Stack.md) | Array-based stack (push/pop/display, empty/full conditions), dynamic-array stacks |
| [03-Stack-Applications-Polish-Notation.md](Module2-Stacks-Queues/03-Stack-Applications-Polish-Notation.md) | Prefix/Infix/Postfix, precedence, full infix→postfix conversion algorithm + 6 worked examples |
| [04-Evaluation-of-Postfix-Expression.md](Module2-Stacks-Queues/04-Evaluation-of-Postfix-Expression.md) | Postfix evaluation algorithm + 3 worked traces (incl. the `$` exponent notation) |
| [05-Queue-Definition-Array-Representation.md](Module2-Stacks-Queues/05-Queue-Definition-Array-Representation.md) | Queue/FIFO, array representation, disadvantages of linear queue, dynamic-array queues |
| [06-Question-Mapping-Index.md](Module2-Stacks-Queues/06-Question-Mapping-Index.md) | Every Module 2 IMP question mapped to its answer |
| [programs/](Module2-Stacks-Queues/programs/) | Standalone runnable `.c` files for Module 2 (all compiled & tested) |

## Why organized this way

The 8 papers repeat the same core concepts in different wording (e.g. "evaluate a
postfix expression" shows up in almost every paper with a different sample
expression). Instead of duplicating the same answer many times, each concept is
answered **once, thoroughly**, and the `Question-Mapping-Index.md` in each module
tells you exactly which paper/question maps to which file — so you can revise by
concept instead of by paper.

More modules will be added here as they're prepared.
