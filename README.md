# 🎟️ Sistema de Bilheteria de Cinema

Projeto acadêmico desenvolvido para a disciplina de **Estrutura de Dados** no curso de Engenharia de Software.  
O sistema simula a bilheteria de um cinema, com funcionalidades como reserva de assentos, emissão de bilhetes e geração de relatórios.

---

## 🧠 Integrantes da Equipe

- Luis Felipe Trega
- Natanael Neves
- Raphael Luiz
- Thiago Vieira
- Wagner Serpa

---

## ⚙️ Funcionalidades

- 📌 Reserva de assentos em matriz (sala de cinema)
- 🎫 Emissão de bilhetes
- 🔍 Busca binária por bilhete
- 📋 Relatórios ordenados por tipo de ingresso e número
- 💾 Manipulação de TADs e estruturas de dados
- 🧪 Menu interativo para testes
- Menu de Acesso Gerencial
- Melhoria na Interface do Usuário (UI)
- Persistência de Dados em Arquivo
---

## 🚧 Implementações Pendentes

Aqui estão algumas das funcionalidades e melhorias que ainda precisam ser implementadas no sistema:


1. **Relatório de Pagamento**  
   Criar um sistema que calcule o pagamento dos ingressos, Combos? Talvez!

2. **Easter-eggs**  
   Coloca o peixe por favorzinho.

---


## 🖥️ Como executar

1. Clone o repositório:

   ```bash
   git clone https://github.com/NatanaelN/Trabalho_bilheteria.git


2. Acesse a pasta:

   ```bash
   cd SistemaBilheteria
   ```

3. Compile com `gcc` (ou use o CLion se preferir):

   ```bash
   gcc -o bilheteria main.c *.c
   ```

4. Execute o programa:

   ```bash
   ./bilheteria
   ```

---

## 📁 Estrutura do Projeto

```
Projeto/
├── main.c
├── data/
├── CMakeLists.txt
├── src/
│   ├── controller/
│      ├── reserva.c
│      ├── storage.c
│   ├── model/
│      ├── bilhete.c
│      ├── bilheteria.c
│   ├── view/
│      ├── menu.c
│      ├── menu_gerencial.c
│      ├── menu_principal.c
│      ├── visual.c
├── include/
│   ├── controller/
│      ├── reserva.h
│      ├── storage.h
│   ├── model/
│      ├── bilhete.h
│      ├── bilheteria.h
│      ├── struct.h
│   ├── view/
│      ├── menu.h
│      ├── menu_gerencial.h
│      ├── menu_principal.h
│      ├── visual.h
├── common.h
└── README.md
```

---

## 🧙‍♂️ Observações

- Este projeto é puramente acadêmico.
- Não usar em produção a menos que queira causar um colapso no multiverso cinematográfico.

---

## 📜 Licença

Projeto com fins educacionais. Sinta-se livre para estudar, modificar e contribuir.
