# COMP 3522 Lab #8: Auctioneer - (Simplified) Observer Pattern

Welcome back! This week you will simulate an auction using a simplified version of the **observer pattern**: an `Auctioneer` (the subject) tracks the current highest bid and notifies a list of `Bidder`s (the observers) whenever that bid changes, giving each of them a chance to bid again.

## Before you start

This repo uses the **CodeRewind** VS Code extension to record your editing session (typed keystrokes, pastes, AI suggestion accepts) for later review. Set it up before you start coding:

1. Install the extension: open the **Extensions** view in VS Code (`Ctrl+Shift+X`), search for **CodeRewind**, and click **Install**. Or install it directly from the Marketplace: [https://marketplace.visualstudio.com/items?itemName=NabilMAl-Rousan.code-rewind](https://marketplace.visualstudio.com/items?itemName=NabilMAl-Rousan.code-rewind). If you have multiple VS Code profiles, right-click the extension and select **Apply Extension to all profiles**.
2. That's it! This repo already contains a `.coderewind-record` file at its root, so recording **starts automatically** the moment you open this folder in VS Code. A status bar item at the bottom right shows `CodeRewind: Recording` when it's active.
3. Just code normally. Sessions are saved to `.vscode/keylog/session-<timestamp>.jsonl` and are committed along with your other work (don't remove them or add `.vscode/keylog/` to your own `.gitignore`).
4. If you ever need to pause/resume recording manually, click the status bar item, or use **CodeRewind: Start Recording** / **CodeRewind: Stop Recording** from the Command Palette (`Ctrl+Shift+P`).
5. Ensure you commit and push your work frequently, at logical points in development, with sensible commit messages. Don't leave it all to one giant commit at the end.

---

## 1. Build an auction house simulation

You've been given skeleton files for three classes: `Bidder` (`bidder.hpp`/`bidder.cpp`), `Auctioneer` (`auctioneer.hpp`/`auctioneer.cpp`), and `Auction` (`auction.hpp`/`auction.cpp`), plus a `main.cpp` with `//TODO` tags. **Do not create any other classes besides these three** - the whole lab fits in `Bidder`, `Auctioneer`, and `Auction`.

> A couple of things this lab needs weren't covered in the Week 1-9 lecture decks, and the observer pattern itself (which you'll apply here) is this week's topic rather than something from an earlier week. `Lab-08.pptx` in this repo fills in: generating random numbers with `rand()`/`srand()` (used for the bidder's probability roll), and why `bidder.hpp` needs a `class Auctioneer;` **forward declaration** instead of `#include "auctioneer.hpp"`. For the observer pattern itself, see `Week-10-Behavioral-Patterns-Observer-ChainOfResponsibility-Strategy-State-Mediator.pptx` in the shared repo - this lab is a **simplified** version of what those slides show: no abstract `Subject`/`Observer` base classes, just the three concrete classes above playing those roles directly.

### `Bidder` - the observer

A `Bidder` represents a person placing bids. Each one stores:

- `name` - the bidder's name.
- `budget` - the most this bidder is willing to spend. It will never place a bid above this.
- `bid_probability` - a value between 0 and 100 (a percentage) representing the chance this bidder retaliates against a new bid with one of its own.
- `bid_increase_perc` - a number greater than 1 (e.g. `1.4` means 140%). A bidder's new bid is the current highest bid multiplied by this value.
- `highest_bid` - the highest amount this particular bidder has bid so far.

Implement `Bidder::update(Auctioneer *auctioneer)`. The auctioneer calls this on every bidder whenever it accepts a new bid. Inside `update`, this bidder should place a new bid with the auctioneer (via `auctioneer->accept_bid(...)`, which starts the notification cycle over again) only if **all** of the following hold:

1. The bid being reacted to wasn't this same bidder's own bid (a bidder can't retaliate against itself).
2. The amount this bidder would bid (current highest bid times `bid_increase_perc`) does not exceed its `budget`.
3. A randomly generated roll succeeds against `bid_probability` (see `Lab-08.pptx`).

### `Auctioneer` - the subject

The `Auctioneer` maintains:

- `bidders` - a vector of `Bidder*` it can notify.
- `highest_bid` - the current highest bid.
- `highest_bidder` - a pointer to whoever placed it.

`Auctioneer` is **not** a static class, and none of its methods should be `static`. Implement:

- `register_bidder(Bidder *bidder)` - adds a bidder to `bidders`.
- `reset_auctioneer()` - clears `bidders` and resets the highest bid back to 0.
- `notify_bidders()` - calls `update(this)` on every registered bidder **except** `highest_bidder` (that bidder placed the bid being reacted to, so they're excluded from their own notification).
- `accept_bid(double bid, Bidder *bidder = nullptr)` - if `bid` is greater than the current `highest_bid`, records the new highest bid/bidder and calls `notify_bidders()`.

### `Auction` - the controller

`Auction` sets up and drives one auction. It is **not** a static class either - no static functions here. Implement:

- `Auction(vector<Bidder *> bidders)` - registers every bidder with this auction's `Auctioneer` so they can be notified later.
- `simulate_auction(string item, double start_price)` - places `start_price` as the opening bid via `accept_bid`, which triggers `notify_bidders`, which in turn may trigger more bids, and so on until the chain stops (either nobody wants to bid, or everyone has exhausted their budget). Once it settles, print the winning bidder and their winning bid, followed by a summary line for every bidder showing their name and their own highest bid (including bidders who never won, or never bid at all).

### `main.cpp`

Your `main()` should:

1. Have a handful of test bidders preloaded (already done for you).
2. Prompt the user for the name of the item being auctioned and its starting price.
3. Let the user choose whether to start the auction with just the preloaded bidders, or add more bidders first (prompting for each new bidder's name, budget, bid probability, etc).
4. Construct an `Auction` with the final list of bidders and call `simulate_auction(...)`.

Since there's no dedicated UI class in this lab, put your `cout` statements wherever makes sense as you implement the classes above.

### Sample output

```
Starting Auction!!
------------------
Auctioning Antique Vase at starting price $100
Priya bidded $110 in response to Starting bid's bid of $100
Jojo bidded $132 in response to Priya's bid of $110
Priya bidded $145.2 in response to Jojo's bid of $132
Scott bidded $290 in response to Priya's bid of $145
Melissa bidded $435 in response to Scott's bid of $290
Priya bidded $478.5 in response to Melissa's bid of $435
Melissa bidded $717 in response to Priya's bid of $478
Priya bidded $788.7 in response to Melissa's bid of $717
Scott bidded $1576 in response to Priya's bid of $788
Priya bidded $1733.6 in response to Scott's bid of $1576
Scott bidded $3466 in response to Priya's bid of $1733
Melissa bidded $5199 in response to Scott's bid of $3466
Priya bidded $5718.9 in response to Melissa's bid of $5199

The Antique Vase goes to Priya for $5718

Bidder: Jojo, Highest bid: $132
Bidder: Melissa, Highest bid: $5199
Bidder: Priya, Highest bid: $5718.9
Bidder: Kewei, Highest bid: $0
Bidder: Scott, Highest bid: $3466
```

Your exact numbers will differ since the bid probabilities are randomly generated, but the shape (a chain of bids, a winner announcement, then a per-bidder summary) should match.

---

## 2. Build and run in VS Code (CMake)

This repo already includes a `CMakeLists.txt` at the project root, listing the starter files as sources for the `lab8` executable:

```cmake
cmake_minimum_required(VERSION 3.20)
project(lab8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab8 main.cpp auction.cpp auction.hpp auctioneer.cpp auctioneer.hpp bidder.cpp bidder.hpp)
```

As you add new files (if any), add each new `.cpp` (and, if you like, `.hpp`) file to the `add_executable(...)` list above so CMake picks it up.

Configure and build from the terminal:

```
cmake -S . -B build
cmake --build build
```

Then run the executable from `build/` (e.g. `.\build\lab8.exe` on Windows, `./build/lab8` on Linux/macOS).

If you have the **CMake Tools** extension installed in VS Code, you can instead use the status bar's **Build**/**Run**/**Debug** buttons, or the `F7` / `Ctrl+Shift+F5` / `Shift+F5` shortcuts, once the `lab8` target is selected as active.

### Alternative: build and run with g++ directly (no CMake)

If you'd rather skip CMake, you can compile every `.cpp` file directly with g++. List them all on one command line:

```
g++ -std=c++20 -Wall -Wextra -pedantic -o lab8 main.cpp auction.cpp auctioneer.cpp bidder.cpp
```

(Add any new `.cpp` files you create to this list too.) Then run the executable (`.\lab8.exe` on Windows, `./lab8` on Linux/macOS).

---

## Frequently asked questions / troubleshooting

1. **Can a bidder bid against their own current highest bid?**
   No. If `highest_bidder` is the bidder being notified, skip them in `notify_bidders()` - that's the whole reason `accept_bid` tracks who placed the current highest bid.
2. **Why does `bidder.hpp` need `class Auctioneer;` instead of `#include "auctioneer.hpp"`?**
   `auctioneer.hpp` includes `bidder.hpp` (it stores `vector<Bidder *>`), and `bidder.hpp` needs an `Auctioneer*` parameter for `update()`. If both headers tried to `#include` each other directly, you'd get a circular include. A forward declaration tells the compiler "this name is a class, trust me" without needing the full definition, which is enough since `bidder.hpp` only ever uses an `Auctioneer*` (a pointer doesn't need the full class layout). See `Lab-08.pptx` for more detail.
3. **How do I generate the probability roll for `bid_probability`?**
   Generate a random number and compare it against the bidder's `bid_probability`. `Lab-08.pptx` covers the two common ways to do this in C++ (`rand()`/`srand()`, and the `<random>` header), and the tradeoffs between them.
4. **My auction only ever produces one bid instead of a back-and-forth chain. Why?**
   Check that `srand()` is only called once, in `main()`, before any bidding happens. If you also call `srand(time(0))` inside `Bidder::update()` (e.g. right before rolling the probability check), you're reseeding the random number generator on every single call. `time(0)` only has 1-second resolution, so every bidder notified within that same second gets reseeded with the same value and ends up with the exact same "random" roll, which breaks the independence the probability check relies on and can stall the chain after just one bid. Seed once, then call `rand()` as many times as you need.
5. **Why isn't `Auctioneer` or `Auction` a static class?**
   Each `Auction` needs its own `Auctioneer` with its own independent list of bidders and highest bid, so a future auction doesn't interfere with a past one. A `static` class (or static-only methods) would mean every auction shares the same state, which isn't what we want.
6. **I'm getting a "class redefinition" error when I build.**
   Every header here already has `#pragma once` at the top. If you add new header files of your own, give each one the same so the compiler only processes its contents once per translation unit even if it ends up `#include`d indirectly more than once.
7. **Can I add new functions like getters and setters to classes?**
   Yes. You should be able to finish the lab with the methods already declared plus a handful of getters (e.g. so `Auction` can read a bidder's name and highest bid for the summary, or the auctioneer's highest bid/bidder for the result line).
8. **Can I write more member functions and data members than the ones named above?**
   Yes, definitely. You're free to add as many as you need, as long as you stick to the three classes `Bidder`, `Auctioneer`, and `Auction`.
