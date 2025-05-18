*Build image*
``` bash
docker build -t riscv64_project_image .  
```

*Build and run container*
``` bash
docker run --name riscv64_project_container -it riscv64_project_image
```

*Sysroot*
``` bash
echo 'ROOTFS="../sc-dt/riscv-gcc/sysroot/"' >> .env
```

*Update file*
``` bash
docker cp src/matmul_vectorization.c riscv64_project_container:/riscv64_project/src/matmul_vectorization.c
```

*Start existing container*
``` bash
docker start -ai riscv64_project_container
```

*Update file in running container*
``` bash
docker cp /path/to/changed/file riscv64_project_container:/riscv64_project/path/to/file
```
