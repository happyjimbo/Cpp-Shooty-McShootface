# Shooty McShootface

A vertical shooter built in C++20, using [SFML](https://www.sfml-dev.org) along with the STL, Boost PFR, and rapidcsv for efficient data management and performance.

![plot](./public/shooty.gif)

---

## Key Features

### Memory and Performance
- **Memory Management**: A balance of smart and raw pointers is used.
    - **Smart Pointers**: Used in non-critical areas like `Game` and `StateHandler` for clarity.
    - **Raw Pointers**: Leveraged in performance-sensitive parts like the object pool, following RAII principles for manual memory control.
- **Template-Based Object Pool**: Efficiently manages game objects, enhancing performance.

### Data Management
- **Serialization & Deserialization**:
    - **Rapidcsv Integration**: Simplifies configuration with structured CSV support, enabling both loading and saving of game settings.
    - **Boost::pfr**: Custom layer built on top of rapidcsv to enable struct serialization with templates, removing the need for hardcoded struct/CSV fields.

### Game Architecture
- **Entity Management**:
    - **ECS-Inspired Architecture**: Systems inspired by ECS principles for modular entity handling.
- **State Management**:
    - **StateHandler**: Manages `World` instance lifecycle, ensuring efficient memory usage.
- **Encapsulation (PImpl Idiom)**: Applied in `StateHandler` and `World` for encapsulation, omitted in core game systems to maximize performance.

### Initializers and Entity Spawning
- **Entity Initializers**: Custom initializers streamline entity setup and spawning, maintaining modularity.

### Visuals and Animation
- **Fragment Shaders**:
    - Flash shader for the player aircraft on hit.
    - Cloud distortion shader for dynamic visuals.
- **Visual Effects**:
    - **Parallax Scrolling**: Adds depth to the ground and cloud layers.
- **Sprite Animation**: Frame-based animations using sprite sheets for smooth visuals.

### Settings
- **ImGui Debug Menu**: Provides an interactive menu for adjusting game settings during runtime, with changes saved back to the CSV file.

---

## C++ Version Compatibility

The game targets C++20 but can be adjusted for older C++ standards:

- **C++14 functionality**:
  - Substitute `std::make_unique` with `new`.
  - Adjust or remove `constexpr` from functions.
  -
- **C++20 functionality**:
  - `std::invocable`: Used in `ProjectileCollisionSystem` to enable template implementation within the `.cpp` file. To downgrade, move implementations to a header or `.inl` file.
  - `std::erase_if`: Utilized in `SoundEffects` for simplified vector management.
  - `boost::pfr::for_each_field` Used in `CvsSerializer.inl` for a reflection based lookup of the struct fields. Remove this and replace with a hardcoded implementation.
