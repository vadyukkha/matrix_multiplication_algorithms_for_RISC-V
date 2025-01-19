# Используем официальный образ Ubuntu в качестве базового
FROM ubuntu:22.04

# Устанавливаем зависимости и необходимые инструменты
RUN apt-get update && apt-get upgrade && apt-get install -y \
    libglib2.0-0 libglib2.0-dev \
    build-essential \
    cmake \
    python3.11 \
    python3.11-venv \
    python3.11-dev \
    bash \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Указываем рабочую директорию
WORKDIR /riscv64_project

# Копируем ваш проект в контейнер
COPY . /riscv64_project

# Команда по умолчанию при запуске контейнера
CMD ["bash", "-c", "source /riscv64_project/sc-dt/env.sh && bash"]
