toolchain_file="toolchain.cmake"

function build {
    rm -rf build;
    mkdir build;
    cmake -S . -B build\
    -DCMAKE_TOOLCHAIN_FILE=$toolchain_file\
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON;
}

function compile {
    cd build;
    make -j$(nproc);
    cd ..;
}

function flash {
    openocd -f interface/stlink.cfg \
            -f target/stm32g4x.cfg  \
            -c "program build/blinky.bin 0x08000000 reset exit";
}

function clean {
    rm -rf build;
}