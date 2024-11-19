import os
import subprocess

import matplotlib.pyplot as plt

executables = {
    "naive": "../build/benchmarking/benchmark",
}


def compile_code():
    print("[COMPILATION] >> Компиляция исходных файлов...")
    try:
        subprocess.run(["cmake", ".."], cwd="../build", check=True)
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


if "__main__" == __name__:
    all_outputs = [
        "matmul_naive.txt",
    ]

    compile_code()
    step = 16
    finish = 512

    for algo, path in executables.items():
        print(f"[TEST] >> Тестируем {algo}... << [TEST]")
        subprocess.run([path, str(step), str(finish)], check=True)

    plt.figure(figsize=(10, 6))

    for algo, output_file in zip(executables.keys(), all_outputs):
        results = parse_output(output_file)
        matrix_sizes = sorted(results.keys())
        times = [results[size] for size in matrix_sizes]
        plt.plot(matrix_sizes, times, label=algo, marker="o")

    plt.xlabel("Matrix size (N x N)")
    plt.ylabel("Circles of work")
    plt.title("Matrix multiplication performance")
    plt.legend()
    plt.grid(True)
    plt.savefig("performance.png")
    print("График сохранён в performance.png")
