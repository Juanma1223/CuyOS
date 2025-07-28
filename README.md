# CuyOS

CuyOS is a free and open source educational operating system, written in C and assembly, designed to teach and demonstrate low-level OS concepts. It is built using the **Clang** toolchain and targets the x86 (i386) architecture. The project is modular, with a clear separation between kernel, architecture-specific code, and a minimal C standard library.

---

## Table of Contents

- [Folder Structure](#folder-structure)
- [How CuyOS Works](#how-cuyos-works)
- [Getting Started](#getting-started)
- [Development Notes](#development-notes)
- [References](#references)
- [License](#license)
- [Contact](#contact)

---

## Folder Structure

```
CuyOS/
├── src/
│   └── kernel/
│       ├── arch/
│       │   └── i386/
│       │       ├── boot/
│       │       │   └── boot.s
│       │       ├── pic/
│       │       │   └── pic.c
│       │       ├── ...
│       ├── core/
│       │   ├── main.c
│       │   ├── memory.c
│       │   └── ...
│       ├── include/
│       │   ├── kernel.h
│       │   └── ...
│       └── ...
├── libc/
│   ├── src/
│   │   ├── string.c
│   │   ├── stdio.c
│   │   └── ...
│   ├── include/
│   │   ├── string.h
│   │   ├── stdio.h
│   │   └── ...
│   └── Makefile
├── qemu.sh
├── Makefile
├── README.md
└── readme.new.md
```

### Folder Details

- **`src/kernel/`**  
  Main kernel source code.
  - `arch/i386/`: Architecture-specific code for x86 (interrupts, PIC, boot, etc).
  - `core/`: Core kernel logic (main entry, memory management, etc).
  - `include/`: Kernel headers.

- **`libc/`**  
  Minimal C standard library implementation for kernel use.
  - `src/`: Source files for libc functions.
  - `include/`: Headers for libc.

- **`qemu.sh`**  
  Script to launch the built kernel in QEMU.

- **`Makefile`**  
  Top-level build file. Delegates to subproject Makefiles.

---

## How CuyOS Works

### Boot Process

1. **Bootloader**  
   The bootloader (GRUB or a minimal multiboot header) loads the kernel into memory and jumps to the entry point defined in assembly (`boot.s`).

2. **Stack Setup**  
   The assembly code sets up a stack for the kernel, as required by the x86 ABI.

3. **Kernel Entry**  
   Control is transferred to the C kernel entry point (e.g., `kernel_main` in `main.c`).

4. **Initialization**  
   The kernel initializes hardware (e.g., PIC in `pic.c`), sets up memory, and prepares basic services.

5. **C Standard Library**  
   The kernel uses a minimal libc for basic C functionality (e.g., `memcpy`, `printf`).

6. **Execution**  
   The kernel runs its main loop or demo code (e.g., prints "Hello, kernel World!" to the terminal).

---

## Getting Started

### Prerequisites

- Linux system (Debian/Ubuntu recommended)
- Clang, LLD, LLDB, and 32-bit libraries
- QEMU

Install dependencies:

```bash
sudo apt update
sudo apt install clang lld lldb gcc-multilib qemu-system-i386 mtools xorriso make git
```

### Clone the Repository

```bash
git clone https://github.com/Juanma1223/CuyOS.git
cd CuyOS
```

### Build the OS

```bash
make
```

### Run in QEMU

```bash
./qemu.sh
```
---

## Development Notes

- **Clang Toolchain:**  
  All code is compiled using Clang with 32-bit support. Makefiles handle assembling, compiling, and linking.

- **Adding Kernel Features:**  
  Place new architecture-independent code in `src/kernel/core/` and headers in `src/kernel/include/`.  
  For architecture-specific code, use `src/kernel/arch/i386/`.

- **Extending libc:**  
  Add new C standard library functions in `libc/src/` and declare them in `libc/include/`.

---

## References

- [OSDev Wiki](https://wiki.osdev.org/)
- [Clang Documentation](https://clang.llvm.org/docs/)
- [QEMU Documentation](https://wiki.qemu.org/Main_Page)
- [Bare Bones Example README](bare_bones_example/README.md)

---

## License

CuyOS is licensed under the GNU General Public License v3.0 or later. See [bare_bones_example/LICENSE](bare_bones_example/LICENSE) for details.

---

## Contact

For questions or contributions, open an issue or pull request on [GitHub](https://github.com/Juanma1223/CuyOS).

---