xhost +local:docker
docker build -t cuyos-qemu .
docker run -it --rm \
    -e DISPLAY=$DISPLAY \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    cuyos-qemu
