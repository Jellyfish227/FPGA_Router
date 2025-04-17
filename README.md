# FPGA Router Project

This project is a associated project for the course CENG4120 - VLSI CAD @ CUHK CSE. 

## License

This project is licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License (CC BY-NC-ND 4.0). This means:

- ✅ You may share this work with proper attribution
- ❌ You may not use this work for commercial purposes
- ❌ You may not distribute modified versions of this work
- ❌ You may not incorporate this work into projects with incompatible licenses

For more details, see the [LICENSE](LICENSE) file or visit [creativecommons.org/licenses/by-nc-nd/4.0/](https://creativecommons.org/licenses/by-nc-nd/4.0/).

## Project Specification

link to the project specification: [Project Specification](https://docs.google.com/document/d/1j5CG7rs7Lly9z2geyGshsqmxCjwI-02XgDg34WKzxnc/edit?tab=t.0#heading=h.w9vrcq760723)

## Project Deadlines 

- [x] Team Formation : 2025-04-01
- [x] Project Proposal Presentation : 2025-04-09
- [ ] Alpha Submission : 2025-04-25
- [ ] Final Submission : 2025-05-03
- [ ] Presentation & Result release : 2025-05-06

## Project Setup

```bash
chmod +x setup.sh
./setup.sh
```

## Requirements

- CMake 3.10+
- C++17 Compiler
- Boost Library
- OpenMP

### Download Boost Library

# macOS (using Homebrew)
```bash
brew install boost
```

# Linux (Ubuntu/Debian)
```bash
sudo apt-get install libboost-all-dev
```

# Linux (Fedora/RHEL)
```bash
sudo dnf install boost-devel
```

### OpenMP
# macOS (using Homebrew)
```bash
brew install libomp 
```

# Linux (Ubuntu/Debian)
```bash
sudo apt-get install libomp-dev
```

# Linux (Fedora/RHEL)
```bash
sudo dnf install libomp-devel

```

## CMake Configuration

Add to your CMakeLists.txt:

```cmake
# Find required packages
find_package(Boost REQUIRED COMPONENTS iostreams)
find_package(OpenMP REQUIRED)

# Add include directories
include_directories(${Boost_INCLUDE_DIRS})

# Add compiler flags for OpenMP
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")

# Link libraries
target_link_libraries(YourTarget PRIVATE 
    ${Boost_LIBRARIES}
    OpenMP::OpenMP_CXX
)
```
