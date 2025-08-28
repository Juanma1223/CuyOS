docker run -d \
    --name ubuntu-gui \
    -e DISPLAY=$DISPLAY \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    ubuntu:22.04 sleep infinity
