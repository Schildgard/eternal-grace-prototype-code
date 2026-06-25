# EternalGrace — Prototype (*Shadow Keep*)

> A third-person **soulslike action prototype** built from the ground up in **Unreal Engine 5 (C++)**.
> This is the **deliberate, cleaner rebuild** of my first-ever Unreal project — re-engineered from scratch with more experience.

This repository contains the **C++ gameplay framework** of the prototype. I share it publicly as an **engineering portfolio piece**: the focus below is on *how the code is structured and why*, not on selling a finished game.

> **Status — prototype, intentionally unfinished.** This was a solo R&D project: not every system is fully played out. Its value is the **architecture and the engineering decisions on display**, not feature-completeness.

<div align="center">
<img src="https://github.com/user-attachments/assets/a0dcb301-bd75-4de7-8baa-02d3bc630f9b" alt="SK_Titlescreen" width = "600"/>  
 </div>

 
---

## Where this fits in my development

I build games as a solo developer and, more recently, as co-founder of a two-person indie team. Across my projects there is a clear, deliberate progression in how I architect software:

| Project | When | Engine | What it shows |
|---|---|---|---|
| **Bonfire** | earliest (~1.5 yrs in) | Unity / C# | First 3D & coding work: hand-built FSM, interfaces from day one, ScriptableObject events, procedural generation |
| **Eternal Grace Arena** | university | UE5 / C++ | My **first Unreal project** — a solo soulslike. Gameplay logic largely lived inside the character |
| **➡ EternalGrace Prototype (this repo)** | after graduating | UE5 / C++ | The **conscious clean rebuild**: data payloads, interface segregation, a real save subsystem, Behavior-Tree AI, documented utilities |
| **Project Mirror / Glass Purgatory** | current indie project | UE5 / C++ | Decoupled Pub/Sub event subsystem, CommonUI + MVVM, framework-for-reuse |

This prototype is the point where my code stops being *"it works"* and starts being *"it is deliberately designed."* Two threads run through it:

- **AI paradigms:** hand-built FSM (*Bonfire*) → manual tick-based sensing (*Eternal Grace Arena*) → **Behavior Trees (this project)** → State Trees (later, professional work).
- **Architecture:** logic-in-the-character (*Eternal Grace Arena*) → **interfaces, data payloads & dedicated subsystems (this project)** → fully decoupled Pub/Sub + reusable framework (*Project Mirror*).

Everything in [`Source/`](Source/) is my own work.

---

## Tech stack

| Area | Details |
|---|---|
| Engine | **Unreal Engine 5.5** |
| Language | **C++** — `USTRUCT` data payloads, C++ interfaces, `UActorComponent` composition, `UBlueprintFunctionLibrary` utilities |
| AI | **Behavior Trees + Blackboard**, a dedicated `AAIController`, and custom `UBTTask`s |
| Persistence | `USaveGame`-based save/load subsystem with an `ISaveable` interface and slot management |
| Data | **DataTable-driven** items, equipment and damage definitions |
| Tooling | Visual Studio 2022, Git |

---

<div align="center">
<img src="https://github.com/user-attachments/assets/ccbcaa12-c5d8-4b4d-9d0c-e2d8dca6a0f6" width="600"/>  
 </div>

## Engineering highlights

The systems below are the reason this prototype is worth reading — they are exactly the things that the previous (student) version *didn't* do well.

### Clean API design — refactoring to a data payload
Damage is modelled as a single **`FDamage` struct** (value, poise damage, direction, hit location/rotation, attacker) instead of the six loose function parameters the older project passed around (`GetDamage(float, float, float, EStaggeringType, …)` → `GetDamage(FDamage)`). One coherent, extensible data object instead of a brittle parameter list — a small change that signals an understanding of **clean interfaces and maintainability**.

### Interface segregation / SOLID
Behaviour is split into many small, focused C++ interfaces rather than a few large ones:
`ISaveable`, `IAttackable`, `IDamageable`, `IStaggerable`, `ITargetable`, `IAggroable`, `IPlayable`, `IInteractable`, `ITriggerable`. Actors implement only what they actually are — **deliberate OOP architecture** instead of inheritance dumping grounds.

### Save / Load subsystem
A standalone persistence layer (`UEternalGrace_SaveGame` on `USaveGame`):

- Per-category, **ObjectID-indexed `TMap`s** (player, treasure chests, triggerables, NPCs).
- **Slot-based save files** with de-duplication checks.
- An **`ISaveable` interface** through which every savable actor serializes itself — the subsystem never needs to know concrete types.

→ A genuine, self-contained subsystem rather than ad-hoc field saving.

### Behavior-Tree enemy AI
Enemies are driven by **Unreal Behavior Trees** (a deliberate move away from the tick-based, character-embedded sensing of my earlier project): a dedicated `AEnemyControllerBase` (`AAIController`), a Behavior Tree + Blackboard, and **custom BT tasks** such as `UBTTask_StrafeAroundTarget` for circling the player. This is my **second AI paradigm**, showing breadth across both Behavior Trees and (in later work) State Trees.

### Responsive combat input — buffering & combos
A dedicated **`UInputBufferComponent`** with a timed window, plus a combo system driven by animation notifies (`Notify_Combo`). Inputs are captured and replayed at the right moment so attacks *feel* responsive — a core technique behind good action-game control and **game-feel engineering**.

### Hit-stop / time-stop
`StartHitStop` / `StopHitStop` with a configurable `TimeStopDuration` give hits weight and impact — another small but deliberate **game-feel** detail.

### Modular character & data-driven equipment
The player character is assembled from separate skeletal meshes (head, hair, upper/lower body, hands, feet) with a modular **inventory / equipment system** (weapons, armor, helmet, greaves, key items) defined via **global DataTables** and held in per-actor maps. → **Data-driven RPG item systems** and modular character presentation.

### World / puzzle interaction with persistent state
Chained, stateful trigger objects (`ITriggerable`, `DependendTriggerableActor`, `MoveableWall`, `TreasureChest`) carry their own save data, so puzzle and world state survive a save/load cycle. → Systems that **interlock across the world, save and interaction layers**.

### Local two-player & class selection
A local two-player mode (`bIsTwoPlayerModeActivated`, `PlayerClassMap`) with a `CharacterClassSelectWidget` — multiple pawns and a class/configuration system.

---

<div align="center">
<img src="https://github.com/user-attachments/assets/aa529505-15a8-443f-a21a-f2212b8c24cb" alt="SK_Treasure" width="600"/>  
 </div>

---

## License

© 2026 Leonard Kemenani. All rights reserved.
Source is published for **portfolio and review purposes**. Not licensed for redistribution or reuse without permission.
