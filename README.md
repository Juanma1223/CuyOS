# CuyOS
A FOSS operating system for educational purposes

## References

https://wiki.osdev.org/Bare_Bones

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

4) Compile gcc for target system
```bash
cd $HOME/src
 
# The $PREFIX/bin dir _must_ be in the PATH. We did that above.
which -- $TARGET-as || echo $TARGET-as is not in the PATH
 
mkdir build-gcc
cd build-gcc
../gcc-x.y.z/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc
```

5) Use custom compiled tools with the following command (using environment variables previously set)

```bash
export PATH="$HOME/opt/cross/bin:$PATH"
$TARGET-gcc --version
```

You can also set the environment variable permanently editing ~/.bashrc or ~/.zshrc adding 
```bash
export PATH="$HOME/opt/cross/bin:$PATH"
```
at the end of the file