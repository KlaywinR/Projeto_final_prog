# 🚀 Floyd-Warshall em C — Projeto de Portfólio

Implementação do **algoritmo de Floyd-Warshall** em **linguagem C**, com foco em **organização de código**, **modularização**, **boas práticas de engenharia de software** e **estrutura profissional de projeto**.

O sistema calcula os **menores caminhos entre todos os pares de cidades** em um grafo ponderado, simulando um cenário real de rotas e distâncias.

---

## 🧠 Sobre o Projeto

Este projeto foi desenvolvido com o objetivo de demonstrar:

- Domínio da linguagem **C**
- Aplicação de **algoritmos clássicos de grafos**
- **Separação de responsabilidades** em módulos
- Organização de projetos em **múltiplas pastas**
- Uso de **Makefile** e compilação multiplataforma
- Escrita de código legível, reutilizável e escalável

Ideal para fins acadêmicos e como **projeto de portfólio**.

---

## ✨ Funcionalidades

- Cadastro manual de cidades e distâncias
- Importação de dados via arquivo (`dados.txt`)
- Execução do algoritmo de Floyd-Warshall
- Cálculo do menor caminho entre quaisquer cidades
- Exibição da matriz de:
  - Distâncias mínimas
  - Predecessores
- Reconstrução do caminho percorrido
- Exportação dos resultados (`resultados.txt`)
- Interface via menu no terminal

---

## 🗂️ Arquitetura do Projeto

floyd-warshall/
│
├── src/
│ ├── main.c
│ │
│ ├── algorithm/
│ │ ├── floyd_warshall.c
│ │ └── floyd_warshall.h
│ │
│ ├── data/
│ │ ├── data_io.c
│ │ └── data_io.h
│ │
│ ├── menu/
│ │ ├── menu.c
│ │ └── menu.h
│ │
│ └── io/
│ ├── print.c
│ └── print.h
│
├── include/
│ └── globals.h
│
├── Makefile
└── README.md

---

## 🛠️ Tecnologias Utilizadas

- **C (ANSI C / C99)**
- **GCC**
- **Makefile**
- **MSYS2 / MinGW (Windows)**
- **Terminal / CLI**

---

## ⚙️ Como Executar

### 🔹 Compilação manual (Windows)

```powershell
gcc src\main.c src\menu\menu.c src\data\data_io.c src\algorithm\floyd_warshall.c src\io\print.c -Iinclude -o floyd.exe

