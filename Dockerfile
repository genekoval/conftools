FROM git.aurora.aur/aurora/cpp

RUN pacman --noconfirm -Syu \
 && pacman --noconfirm -S yaml-cpp

RUN --mount=type=bind,target=. \
    cmake --workflow --preset=docker
