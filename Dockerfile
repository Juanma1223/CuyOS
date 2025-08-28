FROM ubuntu:24.04

RUN apt-get update && apt-get install -y \
    clang \
    lld \
    lldb \
    gcc-multilib \
    qemu-system-i386 \
    grub-pc-bin \
    mtools \
    xorriso \
    make \
    qemu-system-x86 \
    x11-apps \
    && rm -rf /var/lib/apt/lists/*

RUN useradd -ms /bin/bash developer
USER developer
WORKDIR /home/developer

COPY --chown=developer:developer . .

RUN chmod +x /home/developer/qemu.sh

ENTRYPOINT ["./qemu.sh"]
