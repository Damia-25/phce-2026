# Exercise Session 1

Work through the exercises in order. Write your answers directly in this file, in the
`_Answer:_` blocks under each question, and commit it together with any `.cpp` files
you are asked to attach, to your own copy of the repository.

---

## Exercise 1: Verify your setup

Confirm that the [`SETUP.md`](../SETUP.md)
instructions have been followed and your Pico development environment is in place.

**Anything that did not work, and how you solved it:**

During the setup, CMake initially failed with the error:
>
> `CMake Error: Could not find CMAKE_ROOT`
>
> The CMake installation downloaded by the Raspberry Pi Pico extension was incomplete. I fixed this by removing the broken CMake installation from `.pico-sdk` and letting the extension download it again.
>
> I also had a flashing problem where `picotool` detected the RP2040 in BOOTSEL mode but could not access it. I fixed this by installing the WinUSB driver for `RP2 Boot (Interface 1)` using Zadig.
>
> After these fixes, the Pico SDK, toolchain, build process, and flashing worked correctly.
---

## Exercise 2: Build and run the blinker

Create, build and flash the example **Blink** project to confirm that your development
environment works from source code all the way to running firmware on the Pico W.

### Instructions

1. Open **Visual Studio Code**.
2. Open the **Raspberry Pi Pico** extension from the sidebar.
3. Create a new project and select the **Blink** example.
   - Select **Pico W** as the target board.
   - Choose a folder for the project.
   - Create/open the project in VS Code.
4. Add `stdio_init_all();` as the first step inside main()
5. Add `printf("Test");` inside while loop in main()
6. Build the project.
   - Use the **Compile / Build** command from the Raspberry Pi Pico extension.
   - Watch the terminal output and make sure the build finishes without errors.
7. Connect the Pico W to your computer using USB.
8. Flash the program to the Pico W using the **Run / Flash** command in the
   Raspberry Pi Pico extension or by manually uploading the .uf2 file.
9. Check the board. The LED should now blink continuously.
10. Connect the **Debug Probe** (hardware) and open the **Serial Monitor**, then look for the output.

### Checklist
- [ ] Blink project created and opened
- [ ] Project builds without errors
- [ ] Program flashed to the Pico W
- [ ] The LED is blinking
- [ ] Serial Monitor output is visible

**If the build or flash failed, what was the error and what fixed it?**

> The build failed because CMake was installed incorrectly and could not find `CMAKE_ROOT`. Reinstalling CMake fixed it.
>
> Flashing failed because `picotool` could not access the RP2040 in BOOTSEL mode. Installing the WinUSB driver with Zadig fixed the problem.

---

## Exercise 3: Explore PicoBricks

For each hardware module on the PicoBricks board, answer the following
questions:

1. What is the name of this module?
2. What does this module do?
3. Is it an input or output?



### Module 1

| # | Question | Answer |
|---|----------|--------|
| 1 | Name | OLED Display |
| 2 | Purpose | Displays text, numbers and other information. |
| 3 | Input or output | Output |

### Module 2

| # | Question | Answer |
|---|----------|--------|
| 1 | Name | RGB LED |
| 2 | Purpose | Produces light in different colors using red, green and blue LEDs. |
| 3 | Input or output | Output |

### Module 3

| # | Question | Answer |
|---|----------|--------|
| 1 | Name | Red LED |
| 2 | Purpose | Produces a simple on/off visual indication. |
| 3 | Input or output | Output |

### Module 4

| # | Question | Answer |
|---|----------|--------|
| 1 | Name | Push Button |
| 2 | Purpose | Detects whether the user presses the button. |
| 3 | Input or output | Input |

### Module 5

| # | Question | Answer |
|---|----------|--------|
| 1 | Name | Potentiometer |
| 2 | Purpose | Provides an adjustable analog value by turning the knob. |
| 3 | Input or output | Input |

### Module 6

| # | Question | Answer |
|---|----------|--------|
| 1 | Name | LDR / Light Sensor |
| 2 | Purpose | Measures the amount of ambient light. |
| 3 | Input or output | Input |

### Module 7

| # | Question | Answer |
|---|----------|--------|
| 1 | Name | DHT11 Temperature and Humidity Sensor |
| 2 | Purpose | Measures ambient temperature and relative humidity. |
| 3 | Input or output | Input |

### Module 8

| # | Question | Answer |
|---|----------|--------|
| 1 | Name | IR Receiver |
| 2 | Purpose | Receives infrared signals, for example from an IR remote control. |
| 3 | Input or output | Input |

### Module 9

| # | Question | Answer |
|---|----------|--------|
| 1 | Name | Buzzer |
| 2 | Purpose | Produces sound or tones. |
| 3 | Input or output | Output |

### Module 10

| # | Question | Answer |
|---|----------|--------|
| 1 | Name | Relay |
| 2 | Purpose | Electrically switches an external circuit or device on and off. |
| 3 | Input or output | Output |

### Module 11

| # | Question | Answer |
|---|----------|--------|
| 1 | Name | Motor Driver |
| 2 | Purpose | Controls external motors by providing the required drive signals. |
| 3 | Input or output | Output |

## Exercise 4: Morse Code

Make a program that blinks `help!` as Morse
code using the LED abstractions in the blink project (`pico_set_led`). How you represent
and translate Morse code is up to you.

Rules:

- dot = 1 time unit (200ms)
- dash = 3 time units
- gap between dot/dash elements within one letter = 1 unit
- gap between letters = 3 units
- gap between words = 7 units

Use the Morse-code reference below and the C++ book/documentation, Google as needed.

Reference: <https://en.wikipedia.org/wiki/Morse_code>

Simply copy the modified .c file(s) containing your solution to the exercise folder.

**Attached file(s):**

> _Filename:_morse.c, blink.c
>
