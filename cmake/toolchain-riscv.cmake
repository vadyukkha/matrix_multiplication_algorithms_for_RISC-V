set(CMAKE_SYSTEM_NAME Linux) 
set(CMAKE_SYSTEM_PROCESSOR riscv64)

# Toolchain setting
add_definitions(-DRISCV)
message(STATUS "Compiling for RISC-V")
set(CMAKE_C_COMPILER riscv64-unknown-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER riscv64-unknown-linux-gnu-g++)
set(CMAKE_LINKER riscv64-unknown-linux-gnu-ld)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=rv64gcv -mabi=lp64d -fvect-cost-model=cheap -O2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=rv64gcv -O2")
