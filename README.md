# Data Structures and Applications (BCS304) — VTU Important Questions

This repo has **exam-ready, structured answers** for VTU 3rd semester "Data Structures
and Applications" (BCS304, 2025 Scheme) — starting with **Module 1: Introduction to
Data Structures, Arrays, Structures & Sparse Matrices**.

Source material: 8 previous-year BCS304 papers (Dec 2023 → Dec 2025, + Model Paper)
+ the official Module 1 class notes (vtucode.in). Notes used as reference, not copied
word-for-word — answers are written to be easy, understandable, and sufficient for
full marks at a 3rd sem level. Language used for all programs: **C** (this course is
in C, not Java — different subject from the `oops` repo).

## ⚠️ Syllabus flag — read before studying

Several previous-year questions ask about **Pattern Matching / KMP algorithm** and
**string handling functions** (compare/concatenate/reverse strings). Neither topic is
explicitly named in the new 5-module 2025-scheme syllabus for BCS304 — they were part
of the *old* syllabus's Module 1. They're included here (since they show up
repeatedly in PYQs and might still get asked), but **verify with your professor**
whether they're still examinable before spending heavy revision time on them.

## How every answer is structured

For every concept/question:

1. **Definition** — one or two lines, exam-safe.
2. **Points** — 5 to 10 easy bullet points explaining it.
3. **Syntax** — wherever applicable.
4. **Easiest Program** — a clean, complete, working C solution.
5. **Smallest Program** — the shortest valid version that still answers the question.

## Contents

| File | Covers |
|---|---|
| [01-Data-Structures-Intro-Classification.md](Module1-DataStructures-Intro/01-Data-Structures-Intro-Classification.md) | What is a Data Structure, Primitive vs Non-Primitive, Linear vs Non-Linear, the 7 DS Operations |
| [02-Pointers-and-Dynamic-Memory-Allocation.md](Module1-DataStructures-Intro/02-Pointers-and-Dynamic-Memory-Allocation.md) | Pointers, malloc/calloc/realloc/free, static vs dynamic allocation, dangling references |
| [03-Arrays-in-C.md](Module1-DataStructures-Intro/03-Arrays-in-C.md) | 1D/2D arrays in C, address calculation, dynamically allocated arrays |
| [04-Structures-and-Unions.md](Module1-DataStructures-Intro/04-Structures-and-Unions.md) | struct vs union, typedef, self-referential structures |
| [05-Polynomials.md](Module1-DataStructures-Intro/05-Polynomials.md) | Polynomial ADT, array representation, polynomial addition |
| [06-Sparse-Matrices.md](Module1-DataStructures-Intro/06-Sparse-Matrices.md) | Sparse matrix definition, triplet representation, transpose |
| [07-Pattern-Matching-and-Strings.md](Module1-DataStructures-Intro/07-Pattern-Matching-and-Strings.md) | ⚠️ Flagged topic: KMP algorithm, string handling functions without built-ins |
| [08-Question-Mapping-Index.md](Module1-DataStructures-Intro/08-Question-Mapping-Index.md) | Every IMP question mapped to the section/program that answers it |
| [programs/](Module1-DataStructures-Intro/programs/) | All standalone runnable `.c` files referenced above |

## Why organized this way

The 8 papers repeat the same ~8 core concepts in different wording (e.g. "dynamic
memory allocation functions" shows up in almost every paper). Instead of duplicating
the same answer many times, each concept is answered **once, thoroughly**, and
`08-Question-Mapping-Index.md` tells you exactly which paper/question maps to which
file — so you can revise by concept instead of by paper.

More modules will be added here as they're prepared.
