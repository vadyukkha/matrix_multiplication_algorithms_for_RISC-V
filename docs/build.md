# Build system

## How to build

1. Создайте папку `build` из корня проекта и перейдите в нее:

    ``` bash
    mkdir build
    cd build
    ```

2. Используйте cmake для настройки компиляторов:

    + Пропишите для `х86`:

        ``` bash
        cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchain-x86.cmake ..
        ```

    + Пропишите для `RISC-V`:

        ``` bash
        cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchain-riscv.cmake ..
        ```

3. Чтобы собрать проект пропишите:

    ``` bash
    cmake --build .
    ```

4. Теперь в папке `tests` будет лежать два файла, `api_tests` и `kernel_tests`. В одном собраны все тесты для API, а в другом все тесты для функций перемножения матриц. Про тесты читайте *[тут](tests.md)*
