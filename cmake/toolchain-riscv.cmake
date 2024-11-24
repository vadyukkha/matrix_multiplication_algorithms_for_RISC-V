set(CMAKE_SYSTEM_NAME Linux) 
set(CMAKE_SYSTEM_PROCESSOR riscv64)

# set(CMAKE_C_COMPILER riscv64-unknown-linux-gnu-gcc)
# set(CMAKE_CXX_COMPILER riscv64-unknown-linux-gnu-g++)
# set(CMAKE_LINKER riscv64-unknown-linux-gnu-ld)  # Указываем линкер

# set(CMAKE_C_COMPILER riscv64-unknown-elf-gcc)
# set(CMAKE_CXX_COMPILER riscv64-unknown-elf-g++)
# set(CMAKE_LINKER riscv64-unknown-elf-ld)

set(CMAKE_C_COMPILER riscv64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER riscv64-linux-gnu-g++)
set(CMAKE_LINKER riscv64-linux-gnu-ld)  # Указываем линкер

set(CMAKE_FIND_ROOT_PATH /opt/riscv64-gnu-toolchain-glibc-bin/sysroot)

set(CMAKE_CXX_EXTENSIONS ON)
# add_compile_definitions(GTEST_HAS_FILE_SYSTEM=0 GTEST_HAS_STRDUP=0 GTEST_HAS_PTHREAD=0 GTEST_HAS_POSIX_RE=0 GTEST_HAS_CLONE=0 GTEST_HAS_EXCEPTIONS=0 GTEST_HAS_TR1_TUPLE=0 GTEST_HAS_STREAM_REDIRECTION=0 GTEST_HAS_RTTI=0)
