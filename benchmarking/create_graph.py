import os
import subprocess
import time

import matplotlib.pyplot as plt

executables = {
    "naive": "benchmarking/benchmark_naive",
    "transpose": "benchmarking/benchmark_transpose",
}

all_outputs = [
    "benchmarking_outputs/matmul_naive.txt",
    "benchmarking_outputs/matmul_transpose.txt",
]


def compile_code():
    print("[COMPILATION] >> Компиляция исходных файлов...")
    try:
        subprocess.run(["cmake", "--build", "."], cwd="../build", check=True)
        print("[COMPILATION] >> Компиляция завершена успешно.")
    except subprocess.CalledProcessError as e:
        print(f"Ошибка при компиляции: {e}")
        exit(1)
    except FileNotFoundError as e:
        print(f"Ошибка: {e}. Проверьте путь до build!")
        exit(1)


def parse_output(file_path):
    if not os.path.exists(file_path):
        print(f"Файл {file_path} не найден!")
        exit(1)

    results = {}
    with open(file_path, "r") as file:
        for line in file:
            try:
                matrix_size, circles = line.split(":")
                matrix_size = int(matrix_size.strip())
                circles = float(circles.strip())
                results[matrix_size] = circles
            except ValueError:
                print(f"Ошибка парсинга строки: {line.strip()}")
                continue
        return results


def save_results_from_benchmarking():
    step = 16
    finish = 515

    time_start = time.time()
    for algo, path in executables.items():
        print(f"[TEST] >> Тестируем {algo}... << [TEST]")
        subprocess.run([path, str(step), str(finish)], cwd="../build", check=True)
        # subprocess.run(["qemu-riscv64", path, str(step), str(finish)], cwd="../build", check=True)

    print(f"Benchmarking took {time.time() - time_start:.2f} seconds")


def generate_graph():
    plt.figure(figsize=(10, 6))

    for algo, output_file in zip(executables.keys(), all_outputs):
        results = parse_output(output_file)
        matrix_sizes = sorted(results.keys())
        times = [results[size] for size in matrix_sizes]
        plt.plot(matrix_sizes, times, label=algo, marker="o")

    plt.xlabel("Matrix size (N x N)")
    plt.ylabel("Сycles of work")
    plt.title("Matrix multiplication performance")
    plt.legend()
    plt.grid(True)
    plt.savefig("benchmarking_outputs/performance.png")
    print("График сохранён в performance.png")


if "__main__" == __name__:
    if not os.path.exists("benchmarking_outputs"):
        os.mkdir("benchmarking_outputs")
        
    compile_code()

    save_results_from_benchmarking()

    generate_graph()
