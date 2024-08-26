# Parallel Computing Exercises
Exercises proposed in the Parallel Computing discipline at IFMA.

## Run original code
```
cls ; rm .\colonia-original.exe ; cls ; gcc .\colonia-original.c -o .\colonia-original.exe -lm -Wall -Wextra ; .\colonia-original.exe
```

## Run original code with time
```
cls ; rm .\colonia-original.exe ; cls ; gcc .\colonia-nao-paralelizada.c -o .\colonia-nao-paralelizada.exe -fopenmp -lm -Wall -Wextra ; .\colonia-nao-paralelizada.exe
```

```
cls ; rm .\colonia-paralelizada.exe ; gcc .\colonia-paralelizada.c -o .\colonia-paralelizada.exe -fopenmp -lm -Wall -Wextra ; .\colonia-paralelizada.exe
```