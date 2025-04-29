import argparse
import os
import subprocess
import time

import matplotlib.pyplot as plt
from dotenv import load_dotenv

load_dotenv()

parser = argparse.ArgumentParser(description="Benchmarking runner")

parser.add_argument('step', type=int, default=16, help="The step of iteration")
parser.add_argument('finish', type=int, default=512, help="The last number of size of matrix")

parser.add_argument('--arch', choices=['x86', 'riscv64'], default='riscv64', help="Architecture to perform (default: riscv64)")
parser.add_argument('--verbose', action='store_true', help="Enable verbose mode")
parser.add_argument('--m', choices = ['sec', 'cycles'], default='cycles', help="Enable new unit of measurement(default: cycles)")

args = parser.parse_args()

rootfs = os.getenv("ROOTFS")

executables = {
    "naive": "benchmarking/benchmark_naive",
    "transpose": "benchmarking/benchmark_transpose",
    "block_transpose": "benchmarking/benchmark_block_transpose",
    "vectorization": "benchmarking/benchmark_vectorization",
    "asm": "benchmarking/benchmark_asm",
    "vectorize_x86": "benchmarking/benchmark_vectorize_x86",
}

all_outputs = [
    "benchmarking_outputs/matmul_naive.txt",
    "benchmarking_outputs/matmul_transpose.txt",
    "benchmarking_outputs/matmul_block_transpose.txt",
    "benchmarking_outputs/matmul_vectorization.txt",
    "benchmarking_outputs/matmul_asm.txt",
    "benchmarking_outputs/matmul_vectorize_x86.txt",
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
        return None

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
        try:
            os.remove(file_path)
        except OSError:
            print(f"Ошибка удаления файла {file_path}")
        return results


def save_results_from_benchmarking():
    step = args.step
    finish = args.finish

    time_start = time.time()
    for algo, path in executables.items():
        print(f"[TEST] >> Тестируем {algo}... << [TEST]")
        if args.arch == 'x86':
            if args.m == 'sec':
                subprocess.run([path, str(step), str(finish), str(args.m)], cwd="../build", check=True)
            else:
               subprocess.run([path, str(step), str(finish)], cwd="../build", check=True) 
        elif args.arch == 'riscv64':
            if args.m == 'sec':
                subprocess.run(["qemu-riscv64", "-L", rootfs, path, str(step), str(finish), str(args.m)], cwd="../build", check=True)
            else:
                subprocess.run(["qemu-riscv64", "-L", rootfs, path, str(step), str(finish)], cwd="../build", check=True)

    print(f"Benchmarking took {time.time() - time_start:.2f} seconds")


def generate_graph():
    plt.figure(figsize=(10, 6))

    for algo, output_file in zip(executables.keys(), all_outputs):
        results = parse_output(output_file)
        if results is not None:
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
