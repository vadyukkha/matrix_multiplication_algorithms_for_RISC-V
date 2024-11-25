# Tests system

*Перед началом проверьте произвели ли вы билд проекта. Чтобы сделать билд читайте [тут](build.md)*

Тесты написаны с использованием библиотеки `gtest`, таким образом файлы `api_tests` и `kernel_tests` имеют все флаги gtest.

## How to run

1. Перейдите в папку `build`:

    ``` bash
    cd build
    ```

2. Запустите файлы и, если необходимо, укажите флаги:

    + RISC-V
        ``` bash
        qemu-riscv64 -L /path/to/sysroot/ tests/api_tests
        qemu-riscv64 -L /path/to/sysroot/ tests/kernel_tests
        ```
    
    + x86:
        ``` bash
        ./tests/api_tests
        ./tests/kernel_tests
        ```