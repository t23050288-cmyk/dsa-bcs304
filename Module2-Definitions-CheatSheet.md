# Module 2 — All Definitions Cheat Sheet (Easy to Understand & Tell to Ma'am)

> Each concept: **simple definition → key points → syntax (if applicable)**

---

## 1. Stack

**What it is:** An ordered list where insertions and deletions happen at only
**one end**, called the **top** — Last-In-First-Out (**LIFO**).

**Points:**
- `push` = insert onto stack. `pop` = remove and return the top element.
- **Underflow** = trying to pop an empty stack. **Overflow** = trying to push a full stack.
- Real-world example: a stack of plates.
- A **system stack** manages function calls in every program (activation records).

---

## 2. Stack ADT

**What it is:** Defines *what* operations a stack supports, without saying *how*
it's implemented (array or linked list).

**Points:**
- Main ops: `push(data)`, `pop()`.
- Auxiliary ops: `top()` (peek), `size()`, `isEmptyStack()`, `isFullStack()`.

---

## 3. Array Representation of a Stack

**What it is:** A stack implemented using array `stack[]` and an integer `top`
pointing to the current top's index.

**Points:**
- `top = -1` → empty. `top >= MAX_STACK_SIZE-1` → full.
- `push`: `stack[++top] = item`. `pop`: `return stack[top--]`.

**Syntax:**
```c
int stack[MAX_STACK_SIZE], top = -1;
```

---

## 4. Stack Using Dynamic Arrays

**What it is:** A stack whose underlying array **grows automatically** (via
`realloc`, doubling the capacity) instead of using a fixed compile-time size.

**Points:**
- Avoids guessing a good `MAX_STACK_SIZE` in advance.
- **Array doubling**: when full, allocate `2 * capacity` and copy old elements over.
- Total time spent doubling across `n` pushes = **O(n)** — "amortized O(1)" per push.

---

## 5. Polish Notation — the 3 Expression Forms

**Easy way to remember:** where is the operator relative to the operands?

| Form | Operator position | Example |
|---|---|---|
| Infix | Between operands | `A + B` |
| Prefix (Polish) | Before operands | `+ A B` |
| Postfix (Reverse Polish) | After operands | `A B +` |

**Why postfix?** No parentheses, no precedence rules needed — evaluated directly
with a simple stack scan.

---

## 6. Operator Precedence (for infix-to-postfix conversion)

| Precedence | Operators | Associativity |
|---|---|---|
| Highest | `^` | Right to left |
| Middle | `* /` | Left to right |
| Lowest | `+ -` | Left to right |

---

## 7. Infix to Postfix Conversion

**What it is:** Converting an infix expression (`A+B`) to postfix (`AB+`) using a
stack to temporarily hold operators.

**Manual method (easiest for exams):**
1. Fully parenthesize the expression by precedence.
2. Move each operator to replace its matching closing `)`.
3. Delete all parentheses.

**Example:** `A*(B*C+D*E)+F` → `A B C * D E * + * F +`

---

## 8. Evaluation of Postfix Expression

**What it is:** Evaluating a postfix expression with a single left-to-right scan
and a stack — no parentheses or precedence needed.

**Algorithm:**
1. If token is an **operand**, push it.
2. If token is an **operator**, pop `op2` then `op1`, compute `op1 <op> op2`, push result.
3. Final stack value = the answer.

**Example:** `6 2 / 3 - 4 2 * +` → 6/2=3, 3-3=0, 4*2=8, 0+8 = **8**

---

## 9. Queue

**What it is:** An ordered list where insertions happen at the **rear** and
deletions at the **front** — First-In-First-Out (**FIFO**).

**Points:**
- Real-world example: a line at a ticket counter.
- Used in **job scheduling** by operating systems.

---

## 10. Array Representation of a Linear Queue

**What it is:** A queue maintained with array `queue[]` and two variables:
`front` (front element's index) and `rear` (rear element's index).

**Points:**
- `front = rear = -1` → empty.
- **IsFull**: `rear == MAX_QUEUE_SIZE - 1`.
- `addq`: increment `rear`, store item. `deleteq`: increment `front`, return item.

---

## 11. Disadvantages of Linear (Ordinary) Queue

**Easy way to remember:** *"space gets stuck at the front."*

**Points:**
1. Queue shifts right as elements are inserted/deleted — freed front slots are
   never reused.
2. `rear` hits `MAX_QUEUE_SIZE-1` → reports **"full"** even with free space at front.
3. Shifting the whole queue left on every delete is **O(n)** — slow.
4. Solved by the **Circular Queue** (Module 3 topic) — wraps around instead of shifting.

---

## 12. Queue Using Dynamic Arrays

**What it is:** A queue whose storage grows via `realloc` instead of a fixed
`MAX_QUEUE_SIZE` — same "array doubling" idea as dynamic stacks.

**Points:**
- Start with small `capacity`; double it via `realloc` when full.
- A full circular + dynamic-array queue (handling wrap-around while doubling) is
  a more advanced Module 3 topic.

---

## Quick Memory Summary (one-liners for ma'am)

| Term | One-line definition |
|---|---|
| Stack | LIFO list — insert/delete only from the top |
| Stack ADT | The operations a stack supports (push/pop/top/isEmpty/isFull) |
| Underflow / Overflow | Pop from empty stack / push to full stack |
| Dynamic array stack | Stack that grows its array via realloc when full |
| Infix / Prefix / Postfix | Operator between / before / after its operands |
| Postfix evaluation | Scan left to right, push operands, pop+compute+push on operators |
| Queue | FIFO list — insert at rear, delete at front |
| Linear queue disadvantage | Front slots go unused once rear hits max size |
| Dynamic array queue | Queue that grows its array via realloc when full |
| Circular Queue | (Module 3) Wraps around to reuse freed front slots — fixes linear queue's drawback |
