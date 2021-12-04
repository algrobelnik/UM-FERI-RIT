nasm -felf64 main.asm && ld main.o -o main.x && ./main.x
nasm -f elf64 main.asm -o main.o && g++ main.o -lc -fPIC -no-pie -o main.x
