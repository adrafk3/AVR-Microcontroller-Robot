## AVR Microcontroller Robot – Autonomous Course Navigation

This project implements an autonomous line‑following robot based on an AVR ATmega324PA microcontroller.  
The robot must complete a predefined course, detect posts and junction patterns, and reach a final endpoint while respecting strict hardware and timing constraints.  
The system is written in C++ and was developed in the context of the INF1900 embedded systems course.

### Overview

At startup, the robot performs an initialization phase where the user selects the turning strategy for two key junctions using the physical buttons:

- **Interrupt button (PD2)** and **white button (PD3)** are pressed in sequence to configure:
  - The direction used when leaving point **B**
  - The direction used when leaving point **C**
- A **bi‑color LED (PC2)** provides visual feedback during this configuration.

Once configured, the robot autonomously:

- Follows a **black tape line** using a 5‑sensor line follower (Makerline on `PA0–PA4`)
- Uses an **analog distance sensor** on `PA5` to detect posts and obstacles
- Drives two DC motors through an H‑bridge using PWM signals on `PD6/PD7` (speed) and `PD4/PD5` (direction)
- Uses a **buzzer** on `PB2` and the LED for feedback at key checkpoints
- Communicates debug information via **UART** at 2400 baud

The high‑level behavior is encoded as a finite state machine that moves through labeled regions of the course: `INIT → A → B → C → D → MAISON → J → GRILLE → FINAL`, with additional internal sub‑phases for grid navigation and obstacle handling.

### Course Logic & State Machine

The core control logic is implemented in the `Robot` class (`lib/robot/robot.{h,cpp}`) and organized as a **state machine** driven by the `pos` variable (`PositionsParcour` enum).  
Key states and behaviors:

- **INIT**  
  - Run `suivreLigneInitial()` from the starting segment.  
  - Depending on whether all line sensors become active or all off, the robot decides if it started in the main entrance or directly at point **B**.  
  - If all sensors are active, the robot transitions toward the **GRILLE** (grid) and approaches the first post.  
  - If all sensors are off, it assumes starting at **A/B**, plays a sound, rotates to reacquire the line, and moves to state **B**.

- **A**  
  - `suivreLigneA()` follows the line until it loses it (all sensors off), signalling a junction.  
  - The robot plays a sound, reorients based on the configured turning direction at **B**, and transitions to **B**.

- **B**  
  - `parcoursB()` handles the first major turn pattern and drives the robot toward **C**.  
  - When all sensors are off at the end of this segment, the robot plays a sound, moves forward, turns according to the configured direction at **C**, reacquires the line, and enters state **C**.

- **C**  
  - `parcoursC()` follows the track while monitoring specific sensor combinations (four sensors on the right or left).  
  - Once the exit pattern is detected, the robot advances and performs a turn to align with the track heading to **D**.

- **D**  
  - `parcoursD()` continues line following until a special junction or pattern indicates entry toward the **house / maze** section (`MAISON`).  
  - At that moment, the robot saves the upcoming turn and transitions to **MAISON**.

- **MAISON**  
  - `parcoursMaison()` executes a sequence of up to **8 controlled turns** (`virageMaison`) to navigate a compact maze‑like region containing a potential post (`poteau H`) and intermediate points (e.g., skipping point **E**, entering/leaving point **F**).  
  - The robot:
    - Follows the line between corners
    - Uses the distance sensor to check for the presence of a post
    - Blinks the LED to indicate whether a post was detected
  - After 8 turns, depending on the original starting branch, the robot either:
    - Returns to **J** to rejoin the track, or
    - Proceeds directly to the **FINAL** state.

- **J**  
  - `suivreLigneJ()` is similar to the initial entrance logic: when all line sensors become active, the robot stops, advances slightly, then approaches the grid again and sets `pos` to **GRILLE**.

- **GRILLE** (Grid with Two Obstacles)  
  - The robot must handle **two separate “obstacle” zones**, each associated with posts placed on a grid:
    - `premierObstacle()` decides which lane of the grid (left, center, right) the robot is currently using via visual scanning (`balayageApartirDuCentre`, `allerAgaucheApartirDuCentre`, `allerAdroiteApartirDuCentre`). It then follows the correct lane until it has crossed a controlled number of intersections, finally approaching the post with `approcherPoteau()`.
    - `deuxiemeObstacle()` uses a refined scanning strategy (`deuxiemeBalayage`, `balayageApartirDe`, `allerAuCentreApartirDe`, `allerA`) to route around or toward a second obstacle lane, again counting intersections and performing precise turns.  
  - In both obstacles, the robot uses:
    - Line intersection counting
    - Lane selection (`VoieGrille::GAUCHE`, `CENTRE`, `DROITE`)
    - Distance sensor checks (`estPoteauProcheGrille()`)
  - Once both grid obstacles are handled, the robot either:
    - Returns to **A** to repeat a portion of the course if it originally started at **B**, or
    - Moves to **FINAL** if it started from the other entrance.

- **FINAL**  
  - The robot stops, and the bi‑color LED alternates between green and red (`clignoterVertRouge2Hz()`), signalling the end of the course.

### Major Software Components (Libraries)

The project is decomposed into small, testable modules under `lib/`:

- **`robot`**  
  High‑level orchestration and state machine. Manages the full course logic, obstacle handling, and integration of all peripherals.

- **`deplacement` / `roue`**  
  Motor control abstraction. Provides:
  - `avancer`, `reculer`, `virage`, `virageNet`, and `arreter`
  - Encapsulates the H‑bridge logic and PWM configuration

- **`capteurLigne`**  
  Line follower interface with convenience queries:
  - Individual sensor status (`extremeGaucheActif`, `milieuActif`, `extremeDroiteActif`, etc.)
  - Common patterns (`tousLesCapteursActifs`, `tousEteintes`, `milieuEtNonExtreme`, `troisDroite`, `troisGauche`, etc.)

- **`capteurAnalogique` / `can`**  
  Distance sensor reading and analog‑to‑digital conversion. Provides `estPoteauProche()` and `estPoteauProcheGrille()` to detect posts at calibrated thresholds.

- **`led`**  
  Abstraction for a single bi‑color LED on `PC2`. Supports turning green/red on and off and higher‑level effects such as 4 Hz blinking and alternating patterns.

- **`son`**  
  Buzzer driver. Generates tones used for checkpoints, error feedback, and debugging.

- **`bouton`**  
  Handles button debouncing and press detection for:
  - Interrupt button on `PD2`
  - White button on `PD3`

- **`UART`**  
  Serial debugging interface at 2400 baud. The robot logs state transitions and debug messages (e.g., “ligne trouver apres C”, “je vais dans maison”).

- **`minuterie`, `memoire_24`, `constantes`, `debug`**  
  Support modules for timing, I2C EEPROM access (for experimentation), compile‑time constants, and additional debugging utilities.

### Hardware Configuration

The project targets an **AVR ATmega324PA** microcontroller on a development board or custom robot chassis.

- **Microcontroller**: ATmega324PA  
- **Power**: DC supply for motors + regulated logic voltage for MCU and sensors  
- **Key connections**:
  - Line follower (5 sensors): `PA0–PA4`
  - Distance sensor (analog): `PA5`
  - Bi‑color LED: `PC2`
  - Interrupt button: `PD2`
  - White button: `PD3`
  - Motor control via H‑bridge:
    - Left motor PWM: `PD6`, direction: `PD4`
    - Right motor PWM: `PD7`, direction: `PD5`
  - Buzzer: `PB2`
  - UART TX/RX: configured at 2400 baud for serial debug

Peripheral components include:

- Line‑following sensor (Makerline or equivalent)
- Infrared/analog distance sensor
- Piezoelectric buzzer
- Dual DC motors with gearbox
- AVR programmer (e.g., Atmega8‑based ISP)

### Software Architecture

- **Language**: C++ for AVR (using `avr-gcc` / `avr-g++` toolchain)
- **Build system**: `make` with separate `lib/` and `app/` Makefiles
- **Entry point**: `app/apptest.cpp`
  - Creates a `Robot` instance and calls `reussirParcours()` to start the autonomous behavior.

The code is designed around:

- A clear separation between **high‑level behavior** (state machine, obstacle strategy) and **low‑level drivers** (motors, sensors, timers).
- Use of **constexpr parameters** for speeds and delays (e.g., `VITESSE_MAX`, `DELAI_AVANCER_MS`) to ease tuning.
- Extensive use of **static utility methods** and small classes to keep each hardware concern localized.

### Building the Project

From the project root:

```bash
cd lib
make clean
make

cd ../app
make clean
make
```

This produces the application binary for the AVR microcontroller, linking against the static libraries in `lib/`.

### Flashing the Microcontroller

With the programmer connected and the appropriate AVR toolchain installed, from `app/`:

```bash
make install
```

The exact command used by the Makefile may depend on your environment (programmer type, serial port, and `avrdude` configuration).  
Ensure that:

- The ATmega324PA board is powered
- The ISP or USB programmer is correctly wired
- Any required `avrdude` configuration matches your hardware

### How to Run the Demo

1. **Flash** the latest binary using `make install`.  
2. **Place** the robot at the start of the course, aligned with the tape.  
3. **Configure turns**:
   - Press the **interrupt button** (`PD2`) or the **white button** (`PD3`) twice in total to choose the turning direction at **B** and **C**.  
   - The LED indicates which button was used at each step, encoding the chosen orientation for the course.
4. After a short delay, the robot starts `reussirParcours()` automatically:
   - It traverses the labeled regions (A, B, C, D, MAISON, J, GRILLE).  
   - It detects posts in the maze and on the grid using the distance sensor.  
   - It reaches the final endpoint and signals completion by alternating LED colors.

For debugging, you can connect a serial adapter to observe UART messages describing state transitions and sensor events.

### Educational Objectives & Skills Demonstrated

This project demonstrates:

- **Embedded C++ on bare‑metal AVR** (register‑level I/O, timers, PWM, ADC, UART)
- **Finite‑state machine design** for non‑trivial navigation logic
- **Sensor fusion** between a line follower and a distance sensor
- **Real‑time control** of DC motors with PWM and H‑bridge drivers
- **Robustness to physical uncertainty**, using intersection counting and visual scanning strategies (balayage) to infer position on a grid

It is suitable as a portfolio piece to illustrate experience with low‑level embedded development, real‑time control, and structured C++ design on resource‑constrained hardware.

