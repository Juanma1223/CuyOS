# Project Directory Structure

## `/kernel` Folder
The `/kernel` folder contains all the code related to the OS kernel functionality, including:

- **Architecture-Dependent Code:**
  - Located in `/kernel/arch`, this section holds platform-specific code, such as for the x86 architecture.

## `/libc` Folder
The `/libc` folder includes the C standard library implementation necessary for the OS. This folder contains:

- **Standard Libraries:**
  - Libraries required to use C as the programming language.

# Get Started with CuyOS

## Compiling the OS

To compile CuyOS, follow these steps:

1. **Download Dependencies:**
   - Ensure you have Clang installed with 32-bit support.
   - Install Clang and necessary dependencies:
     ```bash
     sudo apt update
     sudo apt install clang lld lldb libc-dev-i386 gcc-multilib
     ```

2. **Clone the Repository:**
   - Clone the source code for CuyOS:
     ```bash
     git clone https://github.com/Juanma1223/CuyOS.git
     cd cuyos
     ```

3. **Build CuyOS:**
   - Use the provided Makefile to compile the OS:
     ```bash
     make
     ```

4. **Run CuyOS on a Virtual Machine:**
   - Install QEMU and then execute `qemu.sh` to create a virtual machine with CuyOS running on it.
     ```bash
     sudo apt install qemu-system-i386  # Debian-based systems
     ./qemu.sh
     ```

