# Get Started with CuyOS

## Compiling the OS

1. Download all dependencies listed on [OSDev - Building GCC](https://wiki.osdev.org/Building_GCC).

2. Clone GCC and Binutils source code to build a cross-compiling environment:
    ```bash
    git clone git://sourceware.org/git/binutils-gdb.git
    ```
    ```bash
    git clone git://gcc.gnu.org/git/gcc.git
    ```

3. Set compilation environment variables. This will compile all cross-compiling tools into `~/opt/cross/`:
    ```bash
    export PREFIX="$HOME/opt/cross"
    export TARGET=i686-elf
    export PATH="$PREFIX/bin:$PATH"
    ```

4. Compile Binutils for the target system:
    ```bash 
    mkdir build-binutils
    cd build-binutils
    ../binutils-x.y.z/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
    make
    make install
    ```

5. Compile GCC for the target system:
    ```bash
    cd $HOME/src
    
    # The $PREFIX/bin directory _must_ be in the PATH. We did that above.
    which -- $TARGET-as || echo $TARGET-as is not in the PATH
    
    mkdir build-gcc
    cd build-gcc
    ../gcc-x.y.z/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
    make all-gcc
    make all-target-libgcc
    make install-gcc
    make install-target-libgcc
    ```

6. Modify `default-host.sh` and write the directory of your cross-compiled tools.

7. Execute `qemu.sh` (install QEMU first) to create a virtual machine with CuyOS running on it. :)