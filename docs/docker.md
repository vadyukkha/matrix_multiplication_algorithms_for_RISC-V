*Сборка image*
``` bash
docker build -t riscv64_project_image .  
```

*Запуск контейнера*
``` bash
docker run --name riscv64_project_container -it riscv64_project_image
```

*sysroot*
``` bash
echo 'ROOTFS="../sc-dt/riscv-gcc/sysroot/"' >> .env
```

*update file*
``` bash
docker cp src/matmul_vectorization.c riscv64_project_container:/riscv64_project/src/matmul_vectorization.c
```