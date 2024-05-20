# CuyOS
A FOSS operating system for educational purposes

## If you want to setup a development environment using linux, follow this steps

1) Clone GCC and Binutils source code to build a cross compiling environment
```bash
 git clone git://sourceware.org/git/binutils-gdb.git
 ```
 ```bash
 git clone git://gcc.gnu.org/git/gcc.git
 ```

 2) Set compilation environment variables, this will compile all cross compiling tools into ~/opt/cross/
 ```bash
export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"
```

3) Compile binutils for target system
```bash 
mkdir build-binutils
cd build-binutils
../binutils-x.y.z/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make
make install
```