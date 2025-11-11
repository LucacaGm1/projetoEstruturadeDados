cmake_minimum_required(VERSION 4.0)
project(projeto)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(.vscode)
include_directories(orientações)

add_executable(projeto
        .vscode/tasks.json
        orientações/carrinhos_clientes_v2.txt
        orientações/estoques_v2.txt
        orientações/filiais_v2.txt
        orientações/produtos_v2.txt
        orientações/Projeto_Final_ED1.pdf
        .gitignore
        carrinhos_clientes_v2.txt
        estoques_v2.txt
        filiais_v2.txt
        main.c
        main.exe
        main.ilk
        main.o
        main.obj
        main.pdb
        produtos_v2.txt
        README.md
        vc140.pdb)
