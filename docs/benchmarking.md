# Benchamrking system

*Перед началом проверьте произвели ли вы билд проекта. Чтобы сделать билд читайте [тут](build.md)*

## How to run

1. Перейдите в папку `benchmarking`:

    ``` bash
    cd benchmarking
    ```

2. Создайте виртуальное окружение для питона и запустите его:

    ``` bash
    python3 -m venv .venv
    source .venv/bin/activate
    ```

3. Установите необходимые зависимости:

    ``` bash
    pip install -r requirements.txt
    ```

4. Если у вас архитектура RISC-V, то создайте файл `.env` и пропишите в нем путь до вашего `sysroot`:

    ``` bash
    touch .env 
    echo 'ROOTFS="/path/to/sysroot/"' >> .env
    ```

5. Запустите скрипт для создания бенчмарков:

    ``` bash
    python3 create_graph.py 15 200
    ```

Файл имеет обязательные аргументы `step` и `finish`, устанавливающие соответственно шаг размера матрицы, с которым хотите итерироваться, и размер матрицы, который будет последним для бенчмаркинга. Также файла поддерживает флаги `--arch`, `--verbose`. Чтобы узнать подробнее про флаги файла, при запуске файла укажите флаг `--help`.
Бенчмаркинг проводится на квадратных матрицах.


## Приложение
Вы можете использовать отдельный запуск бенчмарка для определенной функции. Для этого соберите проект из папки `build` и запустите файл из этой же директории. Файлы также принимают два обязательных параметра `step` и `finish`. Например:

+ RISC-V:

    ``` bash
    qemu-riscv64 -L /path/to/sysroot/ benchmarking/benchmark_naive 10 120
    ```

+ x86:

    ``` bash
    ./benchmarking/benchmark_naive 10 120
    ```