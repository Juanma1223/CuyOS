# Project Directory Structure

## `/kernel` Folder
The `/kernel` folder contains all the code related to the OS kernel functionality, including:

- **Architecture-Dependent Code:** 
  - Located in `/kernel/arch`, this section holds platform-specific code, such as for the x86 architecture.

## `/libc` Folder
The `/libc` folder includes the C standard library implementation necessary for the cross-compiler to work properly. This folder contains:

- **Standard Libraries:**
  - Libraries required to use C as the programming language.

# Get Started with CuyOS

## Compiling the OS

To compile CuyOS, follow these steps:

1. **Download Dependencies:**
   - Refer to the [OSDev - Building GCC](https://wiki.osdev.org/Building_GCC) guide for a list of required dependencies.

2. **Clone GCC and Binutils Source Code:**
   - Clone the source code for GCC and Binutils to set up a cross-compiling environment:
     ```bash
     git clone git://sourceware.org/git/binutils-gdb.git
     ```
     ```bash
     git clone git://gcc.gnu.org/git/gcc.git
     ```

3. **Set Compilation Environment Variables:**
   - Configure the environment to compile cross-compiling tools into `~/opt/cross/`:
     ```bash
     export PREFIX="$HOME/opt/cross"
     export TARGET=i686-elf
     export PATH="$PREFIX/bin:$PATH"
     ```

4. **Compile Binutils:**
   - Build Binutils for the target system:
     ```bash 
     mkdir build-binutils
     cd build-binutils
     ../binutils-x.y.z/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
     make
     make install
     ```

5. **Compile GCC:**
   - Build GCC for the target system:
     ```bash
     cd $HOME/src
     
     # Ensure $TARGET-as is in the PATH
     which -- $TARGET-as || echo $TARGET-as is not in the PATH
     
     mkdir build-gcc
     cd build-gcc
     ../gcc-x.y.z/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
     make all-gcc
     make all-target-libgcc
     make install-gcc
     make install-target-libgcc
     ```

6. **Modify `default-host.sh`:**
   - Update this script with the directory of your cross-compiled tools.

7. **Run CuyOS on a Virtual Machine:**
   - Install QEMU and then execute `qemu.sh` to create a virtual machine with CuyOS running on it.
