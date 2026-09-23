# Exercise Session 3

Work through the exercises in order. Write your answers directly in this file, in the
`_Answer:_` blocks under each question, and commit it together with any `.cpp`
files you are asked to attach, to your own copy of the repository.

Exercises 1 and 2 (below) are worked through together during the session. Exercises 3
and 4 are homework - see [`homework.md`](homework.md).

---

## Exercise 1: Fundamental data types

**Goal:** See the actual size, on this hardware, of C++'s fundamental types - `char`,
the rest of the whole-number and fractional families, `bool`, and `char16_t` - and see
what happens when a value doesn't fit in the type you picked for it.

*Read more (optional): Beginning C++17, Chapter 2 ("The sizeof Operator", "Finding the
Limits"), and Real-Time C++, Sect. 3.2 ("Fixed-Size Integer Types").*

Recall from Computer Systems: a **bit** is 0 or 1, a **byte** is 8 bits - the unit
`sizeof` counts in (`sizeof(char)` is always exactly `1`). With `n` bits you can count
`0` up to `2^n - 1`: 3 bits gives 8 patterns (`000` to `111`), and each extra bit doubles
that count. A type that needs to hold bigger numbers (or a fractional part) generally
needs more bits, and so more bytes - that's the reasoning to guess with below.

The table lists what each type holds and the *minimum* range the C++ standard guarantees
for it (a floor - real hardware is often free to give more, which is what you're about to
measure). `uint8_t` isn't here; it's covered separately in Part 2, since its size is
fixed by its name, not something to guess.

Why does this floor actually matter, instead of just telling you the real numbers? On a
regular laptop, `int` is basically always 4 bytes - you could assume that and be right
almost every time. But on small chips, that's not true: some tiny 8-bit microcontrollers
only give `int` 2 bytes, not 4. So on embedded hardware, the "guaranteed minimum" isn't
just a technicality - it can be the actual number you get.

| Type | What it is | Guaranteed minimum |
|---|---|---|
| `char` | a single character | exactly 1 byte, always (this is the one *fixed* size here) |
| `int` | whole number | -32,767 to +32,767 |
| `short` | whole number, ≤ `int`'s size | same floor as `int` |
| `long` | whole number, ≥ `int`'s size | -2,147,483,647 to +2,147,483,647 |
| `long long` | whole number, ≥ `long`'s size | -9,223,372,036,854,775,807 to +9,223,372,036,854,775,807 |
| `unsigned int` | whole number, no sign | 0 to 65,535 |
| `bool` | only `true`/`false` | none - see below |
| `float` | has a fractional part | precise to ≥ 6 decimal digits |
| `double` | has a fractional part | precise to ≥ 10 decimal digits |
| `long double` | has a fractional part | never less precise than `double` |
| `char16_t` | a character, wider than `char` | ≥ 16 bits (65,536 values) |

A few things that table can't say by itself:

- `short`/`long`/`long long` are just `int` scaled down or up - same idea, different
  guaranteed floor.
- `unsigned int` is `int` with no sign bit, so the same bits buy a bigger positive range
  instead of splitting across positive and negative.
- `bool` gets no bit-count guarantee because individual bits aren't addressable in
  memory - you can only point at a whole byte. So even though 1 bit is all the
  information it needs, it's 1 byte everywhere in practice.
- A fractional type can't be sized the same way as a whole number. A whole number only
  needs to count up to its max, so its range converts directly to a bit count. A
  fractional type also has to store *where the decimal point goes* (that's the
  "floating"), which costs extra bits on top of the digits - so expect it to cost more
  than a whole number of similar-looking range, with no exact formula here.
- `char16_t` is `char` sized for a bigger alphabet: plain `char`'s 8 bits only
  distinguish 256 characters, nowhere near enough for Unicode. Same "how many values do I
  need -> how many bits" reasoning, just a bigger target.

One more type, already hiding in your own code: `size_t`. The name means "size type" -
it's just the type C++ uses whenever it needs to say "how big is this" or "how many of
these." `sizeof()` always returns a `size_t`. That's also why `print_size()`'s `size`
parameter, above, is a `std::size_t` and not an `int`.

Two facts about it:
- It's always unsigned - a size can never be negative.
- Its exact size depends on the platform. On a 32-bit system (like this Pico), it's
  usually the same size as `unsigned int`. On a 64-bit system, it's usually the same
  size as `unsigned long`.

So guess it like this: once you've measured `unsigned int` below, guess `size_t` is
probably the same size.

(There are more built-in types than these - `signed char`, `unsigned char`, `wchar_t`,
`char32_t`, and unsigned versions of `short`/`long`/`long long`. Skipped here just to
keep the table from getting too long. `char16_t` is the one extra type we kept, since
it's a good real example of "need more values -> need more bits.")

### Instructions

1. Before touching the board: guess the size in bytes of every type below except `char`,
   using the guaranteed minimums above as your starting point (`size_t`: guess based on
   which of `unsigned int`/`unsigned long` you think it matches, per the reasoning above).
   Write your guesses in the "Predicted" column (`char` is filled in already - its size is
   fixed by the standard, not something to guess).

   | Type | Predicted | Measured |
   |---|---|---|
   | `char` | 1 | 1|
   | `int` |2 | 4|
   | `short` | 2|2 |
   | `long` | 4|4 |
   | `long long` | 8|8 |
   | `unsigned int` | 2| 4|
   | `bool` |1 | 1|
   | `float` |4 | 4|
   | `double` | 8|8 |
   | `long double` |8 |8 |
   | `char16_t` |2 | 2|
   | `size_t` | 4| 4|

2. Still before touching the board: a fixed-width type, `uint8_t`, from `<cstdint>`
   (already included). The name decodes literally - `u` for unsigned (no negative
   numbers), `int` for whole number, `8` for exactly 8 bits, always, on every platform
   (`_t` is just the standard's naming convention for this kind of typedef). That fixed
   guarantee is exactly what you'd reach for once the exact size genuinely matters and
   "at least this big, maybe more" (like `int` above) is the wrong promise - e.g. a value
   that has to match a hardware register's exact bit width, a field in a file or network
   format that must be exactly N bytes on every machine that reads it, or packing many
   small values tightly into limited memory.

   Predict its minimum and maximum value. This isn't two new things to work out - it's
   the same binary-counting fact from above, just named: for `n` *unsigned* bits, the
   range of values you can count is `0` up to `2^n - 1`, full stop. "Minimum" and
   "maximum" are just the two ends of that same range - here, `n = 8`.

   | | Predicted | Measured |
   |---|---|---|
   | `uint8_t` minimum |0 |0 |
   | `uint8_t` maximum |255 | 255|

3. Create a new Pico project `data_types` (C++, **Console over UART**), and copy in
   [`code/data_types.cpp`](code/data_types.cpp). Recall, `stdio_init_all()` and printing
   to the Serial Monitor go back to Session 1 - only `std::cout` instead of `printf` is
   new (and a better fit here: `printf` needs a format specifier matched to each type by
   hand, `%d` vs `%ld` vs `%f`, and gets it silently wrong with no compiler error if you
   mismatch one - `std::cout`'s `<<` can't be mismatched, it picks the right output for
   whatever type you give it). Fill in the TODO: follow the given `print_size("char", ...)`
   example to call it once for every other row in Part 1's table above, instead of
   repeating the same line for each.
4. Build, flash, and open the **Serial Monitor**. Everything prints in one go, so now fill
   in "Measured" in both tables above: Part 1's sizes, and the `uint8_t minimum`/
   `uint8_t maximum` lines from Part 2's output right below them.
5. Look at the last three lines of output, for `number = 0`, `number = 255`, and
   `number = 256` (`number` is a `uint8_t`). `256` doesn't fit in the range you just
   measured, so note down exactly what gets printed instead.

### Checklist

- [x] Sizes guessed before building
- [x] `print_size()` written and called for every type in Part 1's table
- [ ] `data_types` builds, runs, and the size table is filled in
- [x] `uint8_t` min/max predicted before building, then checked against the output
- [x] Output for `number = 256` recorded

**What was printed for `number = 256`, and why?**

> _Answer:_
>It printed `0`. A `uint8_t` can store values from 0 to 255. When 256 is assigned to it, the value wraps around because `uint8_t` is an 8-bit unsigned integer. Therefore, 256 becomes 0.

**Why does `uint8_t` exist at all, if `int` can already hold every value it can? Give one
situation where the exact size matters and a plain `int` would be the wrong choice.**

> _Answer:_
>`uint8_t` exists because it guarantees an exact size of 8 bits, while `int` only guarantees a minimum range and its actual size depends on the platform. An exact size matters when working with hardware registers. For example, if a hardware register is exactly 8 bits wide, using `uint8_t` matches the register size, while a plain `int` may be 32 bits and would be the wrong choice.

**Attached file(s):**

> _Filename:_
>`data_types.cpp`

---

## Exercise 2: GPIO, from the SDK to registers

**Goal:** Drive the PicoBricks LED (GPIO 7) from the PicoBricks button (GPIO 10) three
ways, going back one layer of abstraction at a time: first with the Pico SDK's
`gpio_*()` functions, then the HAL structs those functions are built on, then the raw
registers underneath that.

Setting up a pin means deciding three things: which internal signal is wired to it (its
"function", GPIO here, could be UART or PWM elsewhere), whether its pull-up/pull-down
and input buffer are switched on, and whether it's an output or an input.

Here's why that matters for the button pin (GPIO 10) below. A button is just a switch:
pressing it physically connects two wires together, nothing more. On this board, one
side of that connection is wired to 3.3V, the other to GPIO 10. So:

- **Pressed** - the switch closes, GPIO 10 is now directly wired to 3.3V, and it reads
  HIGH.
- **Not pressed** - the switch is open, so GPIO 10 isn't wired to anything at all. A pin
  wired to nothing is "floating": it has no fixed voltage and just picks up stray
  electrical noise, reading HIGH or LOW at random.

`gpio_pull_down(BUTTON_PIN)` fixes the floating case. It quietly wires the pin to 0V
through a very weak internal resistor, giving it somewhere to "rest" when the button
isn't pressed. Not pressed -> weakly held at 0V -> reads a clean LOW. Pressed -> the
button's direct connection to 3.3V easily overpowers that weak pull -> reads HIGH. (A
**pull-up** is the mirror image: it weakly holds the pin at 3.3V by default, for a button
wired to connect to 0V when pressed instead.)

That covers the voltage on the pin. But a voltage isn't a "0" or a "1" by itself - it's
just a number between 0V and 3.3V. Something inside the chip has to look at that voltage
and decide "that's a LOW" or "that's a HIGH" before software can use it. That something is
the **input buffer**: a small circuit, one per pin, that converts the raw voltage into
the digital value `gpio_get()` actually returns. It's switched on by default, which is
why the SDK snippet below never mentions it - but it's still a real setting, and you'll
see it set explicitly as its own bit (IE, "Input Enable") right next to the pull-down in
`gpio_hal.cpp`/`gpio_registers.cpp` later in this exercise. Turn it off and `gpio_get()`
has nothing to read, no matter what voltage is actually on the pin - it's mainly turned
off to save a little power on pins that are unused or carrying an analog signal instead.

### Instructions

1. In the **Raspberry Pi Pico** extension: **New Pico Project** → **C/C++**. Name it
   `gpio_sdk`, board **Pico W**, tick **Generate C++ code**.
2. Copy in the short program below and build and run it: pressing the button should
   light the LED. Recall, you already used `gpio_init()`, `gpio_set_dir()`, and
   `gpio_put()` in Session 2 - only `gpio_pull_down()` and `gpio_get()` are new here.

   ```cpp
   #include "hardware/gpio.h"
   #include "pico/stdlib.h"

   constexpr uint LED_PIN = 7;
   constexpr uint BUTTON_PIN = 10;

   int main()
   {
       gpio_init(LED_PIN);
       gpio_set_dir(LED_PIN, GPIO_OUT);
       gpio_put(LED_PIN, false);

       gpio_init(BUTTON_PIN);
       gpio_set_dir(BUTTON_PIN, GPIO_IN);
       gpio_pull_down(BUTTON_PIN);  // enable internal pull-down: unpressed reads LOW

       while (true)
       {
           gpio_put(LED_PIN, gpio_get(BUTTON_PIN));  // gpio_get: read the pin's current level
           sleep_ms(10);
       }
   }
   ```
3. Use **F12** (or Ctrl+Click) on `GPIO_OUT`, `GPIO_IN`, or `gpio_put` right here in your
   own code. You'll land in the SDK's own hardware-abstraction-layer (HAL) code - read
   through it, these are the same structs `gpio_hal.cpp` uses in the next step.
4. Create a second project the same way, named `gpio_hal`, and copy in
   [`code/gpio_hal.cpp`](code/gpio_hal.cpp). Before building, read through it and match
   each line against the structs you just saw under F12 (`sio_hw`, `io_bank0_hw`,
   `pads_bank0_hw`). Then build and run it: same behavior again, but written directly
   against those structs instead of calling `gpio_*()` functions.
5. Create a third project the same way, named `gpio_registers`, and copy in
   [`code/gpio_registers.cpp`](code/gpio_registers.cpp). Before building, read through it
   and match each register access back to the struct field it replaces in `gpio_hal.cpp`.
   Then build and run it: same behavior again, but with every struct field swapped for
   the raw address and bit shift it compiles down to.

   A register is a fixed memory address that controls or reports on hardware instead of
   holding ordinary data. This file's `reg()` helper turns such an address into something
   you can read and write like a normal variable:

   ```cpp
   static inline volatile uint32_t& reg(uint32_t address)
   {
       return *reinterpret_cast<volatile uint32_t*>(address);
   }
   ```

   It's `volatile` so the compiler doesn't skip or reorder the access - the value can
   change on its own, or the write itself is the point even if nothing reads it back.
6. Fill in the table below: for each SDK call, find the matching line in `gpio_hal.cpp`
   and in `gpio_registers.cpp`, and say in a few words what it does.

| SDK call | Matching line in `gpio_hal` | Matching line in `gpio_registers` | What does it do? |
|---|---|---|---|
| `gpio_init(LED_PIN)` | `io_bank0_hw->io[LED_PIN].ctrl = GPIO_FUNC_SIO;` + `sio_hw->gpio_clr = 1u << LED_PIN;` | `reg(IO_BANK0_BASE_ADDR + 0x04u + 8u * LED_PIN) = 5u;` + `reg(SIO_BASE_ADDR + 0x018u) = 1u << LED_PIN;` | Configures GPIO7 for SIO control and sets its initial output value to LOW |
| `gpio_set_dir(BUTTON_PIN, GPIO_IN)` | `pads_bank0_hw->io[BUTTON_PIN] |= PADS_BANK0_GPIO0_IE_BITS;` | `button_pad |= 1u << 6;` | Enables the input buffer so GPIO10 can be read as an input |
| `gpio_pull_down(BUTTON_PIN)` | `pads_bank0_hw->io[BUTTON_PIN] &= ~PADS_BANK0_GPIO0_PUE_BITS;` + `pads_bank0_hw->io[BUTTON_PIN] |= PADS_BANK0_GPIO0_PDE_BITS;` | `button_pad &= ~(1u << 3);` + `button_pad |= 1u << 2;` | Disables pull-up and enables pull-down, so the released button reads LOW |
| `gpio_set_dir(LED_PIN, GPIO_OUT)` | `sio_hw->gpio_oe_set = 1u << LED_PIN;` | `reg(SIO_BASE_ADDR + 0x024u) = 1u << LED_PIN;` | Enables GPIO7 as an output |
| `gpio_get(BUTTON_PIN)` | `sio_hw->gpio_in & (1u << BUTTON_PIN)` | `reg(SIO_BASE_ADDR + 0x004u) & (1u << BUTTON_PIN)` | Reads the current state of GPIO10 |
| `gpio_put(LED_PIN, true)` | `sio_hw->gpio_set = 1u << LED_PIN;` | `reg(SIO_BASE_ADDR + 0x014u) = 1u << LED_PIN;` | Sets GPIO7 HIGH and turns the LED on |
| `gpio_put(LED_PIN, false)` | `sio_hw->gpio_clr = 1u << LED_PIN;` | `reg(SIO_BASE_ADDR + 0x018u) = 1u << LED_PIN;` | Sets GPIO7 LOW and turns the LED off |
7. Compare the compiled size of all three projects:
   `arm-none-eabi-size build/<project_name>.elf` (run from each project's folder, or use
   the memory usage summary already printed at the end of a normal build). Fill in the
   `text` size (the actual code, in bytes) for each.

| Project | `text` size (bytes) |
|---|---|
| `gpio_sdk` | 10676 |
| `gpio_hal` | 10604 |
| `gpio_registers` | 10644 |

### Checklist

- [ ] `gpio_sdk` builds and runs; button press lights the LED
- [ ] `gpio_hal` builds and runs with identical behavior
- [ ] `gpio_registers` builds and runs with identical behavior
- [ ] SDK-to-HAL-to-register table filled in
- [ ] Compiled `text` size compared across all three

**The button is configured with a pull-down resistor. What logic level does the input read when the button is released and when it is pressed? How would this change if a pull-up resistor were used instead?**

> _Answer:_
>
> With a pull-down resistor, the button reads LOW when released and HIGH when pressed. With a pull-up resistor, the logic would be reversed: the button would read HIGH when released and LOW when pressed, if the button were wired to ground.

**Did the three projects' compiled sizes actually match how different the source code looks, or were they closer/further apart than you expected? Why might that be?**

> _Answer:_
>
> The compiled sizes were very close even though the source code looked quite different. `gpio_sdk` was 10676 bytes, `gpio_hal` was 10604 bytes, and `gpio_registers` was 10644 bytes. The maximum difference was only 72 bytes. This is because the compiler can inline and optimize many SDK functions, so the higher-level SDK code can compile into almost the same low-level instructions as the HAL or direct-register code.

**When would you reach for direct register access instead of the SDK, and when is the SDK clearly the better choice? Where would the HAL level (`gpio_hal.cpp`) fit in?**

> _Answer:_
>
> Direct register access is useful when very precise control of the hardware is required, when using a hardware feature not provided by the SDK, or when writing very low-level code. The SDK is usually the better choice because it is easier to read, maintain, and use correctly. The HAL level is in between: it gives more direct control of the hardware through named register structures without requiring raw memory addresses and magic numbers.

**`gpio_registers.cpp`/`gpio_hal.cpp` clear the `PUE` bit and set the `PDE` bit for the button pin (pull-down). What third combination of those two bits is possible, and what would it mean electrically for a button input if neither pull-up nor pull-down were enabled?**

> _Answer:_
>
> A third configuration is `PUE = 0` and `PDE = 0`, which means that neither the pull-up nor the pull-down resistor is enabled. When the button is released, the input would then be floating because it is not connected to a defined voltage. Electrical noise could make it randomly read HIGH or LOW.

**Attached file(s):**

> _Filename:_
>
> `gpio_sdk.cpp`
>
> `gpio_hal.cpp`
>
> `gpio_registers.cpp`

Exercises 3 and 4 continue in [`homework.md`](homework.md).
