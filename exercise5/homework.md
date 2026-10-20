
# Exercise Session 5, Homework

Do these after Exercises 1-3, in [`instructions.md`](instructions.md). Write answers in the
`_Answer:_` blocks. Commit this file and your `.cpp` files.

---

## Exercise 4: Swap two numbers

**Goal:** Swap two variables inside a function.

Session 4 flipped a `bool` three ways. Now you swap two `int`s. The three ways are the
same.

### Instructions

1. Create a project `swap`. Copy in this program:

   ```cpp
   #include <iostream>

   #include "pico/stdlib.h"

   void swap_by_value(int a, int b)  // gets copies
   {
       const int temp {a};
       a = b;
       b = temp;
   }

   void swap_by_pointer(int* a, int* b)  // gets addresses
   {
       // TODO 1: swap the two ints that a and b point at.
   }

   void swap_by_reference(int& a, int& b)  // gets other names
   {
       // TODO 2: swap a and b.
   }

   int main()
   {
       stdio_init_all();
       sleep_ms(2000);  // time to open the Serial Monitor

       int x {1};
       int y {2};
       std::cout << "start:        x = " << x << ", y = " << y << std::endl;

       swap_by_value(x, y);
       std::cout << "by value:     x = " << x << ", y = " << y << std::endl;

       swap_by_pointer(&x, &y);
       std::cout << "by pointer:   x = " << x << ", y = " << y << std::endl;

       swap_by_reference(x, y);
       std::cout << "by reference: x = " << x << ", y = " << y << std::endl;

       while (true)
       {
           sleep_ms(1000);
       }
   }
   ```

2. Fill in TODO 1. Copy the body of `swap_by_value()`. Put `*` before every `a` and `b`.
3. Fill in TODO 2. Copy the body of `swap_by_value()`. Change nothing.
4. Open the Serial Monitor. Then build and run. Fill in the table.

| Line | `x` | `y` |
|---|---|---|
| start | 1 | 2 |
| by value | 1 | 2 |
| by pointer | 2 | 1 |
| by reference | 1 | 2 |

### Checklist

- [x] TODO 1 and 2 filled in
- [x] Table filled in

**Why did `swap_by_value()` not swap?**

> _Answer:_
> The function receives copies of the original variables x and y.
> It swaps only these local copies, so the original variables in main()
> remain unchanged. After the function returns, x is still 1 and y is still 2.

**The last line shows `x = 1` again. Why?**

> _Answer:_
> First, swap_by_pointer() changes the original variables, making
> x = 2 and y = 1. Then swap_by_reference() swaps them again using
> references to the same original variables. As a result, their
> original values are restored: x = 1 and y = 2.

**Attached file(s):**

> _Filename:_
> `swap.cpp`

---

## Exercise 5: A function that calls itself

**Goal:** Write a small recursive function.

A recursive function calls itself. Each call gets a smaller number. The base case says
when to stop.

### Instructions

1. Create a project `recursion`. Copy in this program:

   ```cpp
   #include <iostream>

   #include "pico/stdlib.h"

   // Prints n, n - 1, ... 1, then "Liftoff!". Then each call says when it ends.
   void countdown(int n)
   {
       if (n == 0)  // the base case: stop here
       {
           std::cout << "Liftoff!" << std::endl;
           return;
       }
       std::cout << n << std::endl;
       countdown(n - 1);  // the function calls itself
       std::cout << "back in " << n << std::endl;
   }

   // Adds 1 + 2 + ... + n.
   int sum_to(int n)
   {
       // TODO 1: if n is 0, return 0.
       // TODO 2: else return n + sum_to(n - 1).
       return 0;
   }

   int main()
   {
       stdio_init_all();
       sleep_ms(2000);  // time to open the Serial Monitor

       countdown(5);
       std::cout << "sum_to(10) = " << sum_to(10) << std::endl;

       while (true)
       {
           sleep_ms(1000);
       }
   }
   ```

2. Open the Serial Monitor. Then build and run. Read `countdown()` and its output. Why do
   the `back in` lines count up?
3. Fill in TODO 1 and 2. You should see `sum_to(10) = 55`.
4. Define `factorial(int n)` like `sum_to()`. Use `*` instead of `+`. `factorial(0)` is 1.
5. Print `factorial(5)` in `main()`. You should see 120.
6. Delete the base case in `countdown()`. Build, run and watch. Then put it back and
   re-flash.

### Checklist

- [x] `sum_to(10) = 55`
- [x] `factorial(5) = 120`
- [ ] Step 6 tried, then fixed

**What does the base case in `sum_to()` do?**

> _Answer:_
> The base case stops the recursion when n reaches 0 by returning 0.
> It prevents the function from calling itself forever and allows
> previous recursive calls to finish and return their results.
> Without the base case, the recursion would continue and could
> eventually cause a stack overflow.

**What happened in step 6? Why?**

> _Answer:_
> After removing the base case from countdown(), the function did
> not stop at 0. It continued printing negative numbers, reaching
> approximately -3138 in the Serial Monitor.
>
> This happened because the function kept calling countdown(n - 1)
> without a stopping condition. Every recursive call uses additional
> stack memory. Eventually, this can cause a stack overflow,
> memory corruption or a program crash.
>
> The experiment demonstrates why recursive functions need
> a base case to stop correctly.

**Attached file(s):**

> _Filename:_
> `recursion.cpp`

---

*Read more (optional): Beginning C++17, Chapter 8 ("Pass-by-Value", "Pass-by-Reference",
"Recursion").*
