# Memory Leak Analysis for Trading Game

## Date: October 21, 2025

## Summary
✅ **GOOD NEWS**: Your game appears to have proper memory management with no obvious leaks!

---

## Memory Allocations Found

### 1. **Game.cpp - `initCommodities()` method**
**Allocations:**
- Line 352: `commodities = new Commodity*[NumberOfCommodities];` (array of 7 pointers)
- Lines 353-359: 7 commodity objects created with `new`
  - 3 × Harvest objects
  - 3 × Gems objects  
  - 1 × Crypto object

**Deallocation:**
- ✅ Lines 372-374 in `Game::run()`:
  ```cpp
  for (int i = 0; i < NumberOfCommodities; ++i) {
      if (commodities[i]) delete commodities[i];  // Deletes each object
  }
  delete[] commodities;  // Deletes the array itself
  ```

**Status:** ✅ **NO LEAK** - Properly cleaned up

---

### 2. **Commodity.cpp - Constructor**
**Allocation:**
- Line 25: `this->prices = new double[30];`

**Deallocation:**
- ✅ Destructor in Commodity.cpp (lines 94-97):
  ```cpp
  Commodity::~Commodity() {
      delete[] prices; 
      prices = nullptr;
  }
  ```

**Status:** ✅ **NO LEAK** - Properly cleaned up by destructor

---

## Potential Issues to Watch



---

### ⚠️ Issue 2: Game Class Destructor Missing
**Location:** `Game.h` and `Game.cpp`

**Problem:** The `Game` class has a member `Commodity** commodities;` but no destructor.

**Current Behavior:** Memory is cleaned up in `Game::run()`, but if `Game::run()` exits early (e.g., exception), memory could leak.

**Recommendation:** Add a destructor to `Game` class:

**In Game.h:**
```cpp
class Game {
    // ... existing members ...
    
    ~Game();  // Add destructor
};
```

**In Game.cpp:**
```cpp
Game::~Game() {
    // Clean up commodities if they exist
    if (commodities != nullptr) {
        for (int i = 0; i < 7; ++i) {
            if (commodities[i]) delete commodities[i];
        }
        delete[] commodities;
        commodities = nullptr;
    }
}
```

---

### ⚠️ Issue 3: commodities Not Initialized in Constructor
**Location:** `Game.cpp` - constructors (lines 18-26)

**Problem:**
```cpp
Game::Game(){
    this->day=0;
    this->coins=0;
    // commodities is not initialized! Could be garbage
}
```

**Recommendation:**
```cpp
Game::Game(){
    this->day=0;
    this->coins=0;
    this->commodities=nullptr;  // Initialize to nullptr
}

Game::Game(int coins, int day){
    this->day=day;
    this->coins=coins;
    this->commodities=nullptr;  // Initialize to nullptr
}
```

---

## How to Test for Memory Leaks on macOS

### Method 1: Using `leaks` command
```bash
# Compile with debug symbols
clang++ -std=c++17 -g main.cpp Commodity.cpp DigitalCommodities.cpp Game.cpp \
  Gems.cpp Harvest.cpp PhysicalCommodities.cpp Crypto.cpp -o trading_game

# Run the game in background
./trading_game &
PID=$!

# Check for leaks (replace PID with actual process ID)
leaks $PID

# Or check after program exits
echo "exit" | ./trading_game
# Game should exit cleanly
```

### Method 2: Using Address Sanitizer
```bash
# Compile with AddressSanitizer
clang++ -std=c++17 -g -fsanitize=address -fno-omit-frame-pointer \
  main.cpp Commodity.cpp DigitalCommodities.cpp Game.cpp Gems.cpp \
  Harvest.cpp PhysicalCommodities.cpp Crypto.cpp -o trading_game

# Run the game
./trading_game
# If there are leaks, you'll see detailed reports
```

---

## Overall Assessment

### ✅ What's Good:
1. **Proper cleanup** in `Game::run()` - all allocated memory is freed
2. **Destructor exists** for `Commodity` class to clean up `prices` array
3. **Null checks** before delete operations
4. **Virtual destructors** - Commodity base class has virtual destructor (good for polymorphism)

### ⚠️ What to Improve:
1. Add `Game` class destructor for safety
2. Initialize `commodities` pointer to `nullptr` in constructors
3. Replace recursive menu calls with loops to avoid stack overflow
4. Consider using smart pointers (`std::unique_ptr`) for modern C++:
   ```cpp
   std::vector<std::unique_ptr<Commodity>> commodities;
   // Automatic cleanup, no manual delete needed!
   ```

---

## Conclusion

**Current Status:** ✅ No major memory leaks detected  
**Risk Level:** 🟡 Low to Medium (potential stack overflow from recursion)  
**Recommended Action:** Implement the 3 improvements above for production-ready code

Your memory management is solid, but adding a destructor and fixing recursion would make it more robust!
