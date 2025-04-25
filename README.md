# 🎟️ Sistema de Bilheteria de Cinema

Projeto acadêmico desenvolvido para a disciplina de **Estrutura de Dados** no curso de Engenharia de Software.  
O sistema simula a bilheteria de um cinema, com funcionalidades como reserva de assentos, emissão de bilhetes e geração de relatórios.

---

## 🧠 Integrantes da Equipe

- Luis Felipe Trega
- Natanael Neves
- Thiago Vieira
- Raphael Luis
- Wagner Serpa

---

## ⚙️ Funcionalidades

- 📌 Reserva de assentos em matriz (sala de cinema)
- 🎫 Emissão de bilhetes
- 🔍 Busca binária por bilhete
- 📋 Relatórios ordenados por tipo de ingresso e número
- 💾 Manipulação de TADs e estruturas de dados
- 🧪 Menu interativo para testes

---

## 🚧 Implementações Pendentes

Aqui estão algumas das funcionalidades e melhorias que ainda precisam ser implementadas no sistema:

1. **Menu de Acesso Gerencial**  
   Implementar a funcionalidade para inserção de novos filmes dinamicamente, resetar salas, acesso a relatórios, cancelamento de bilhetes, menu acessível somente com login e senha de funcionário.

2. **Relatório de Pagamento**  
   Criar um sistema que calcule o pagamento dos ingressos, Combos? Talvez!

3. **Melhoria na Interface do Usuário (UI)**  
   A interface de menu interativo precisa de melhorias, como a adição de cores, validações de entrada e navegação mais intuitiva.

4. **Melhoria na Interface do Usuário (UI)**  
   Padronização da interface, seja com cores e tamanho.

5. **Persistência de Dados em Arquivo**  
   Implementar a funcionalidade para salvar os dados de reserva e vendas em um arquivo (TXT, JSON, CSV, etc.), permitindo que as informações sejam mantidas após a execução do programa.

6. **Easter-eggs**  
   Coloca o peixe por favorzinho.

---


## 🖥️ Como executar

1. Clone o repositório:

   ```bash
   git clone https://github.com/NatanaelN/CineRato.git


2. Acesse a pasta:

   ```bash
   cd bilheteria-cinema
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
├── bilhete.c
├── assentos.c
├── utils.c
├── include/
│   ├── bilhete.h
│   ├── assentos.h
│   └── utils.h
└── README.md
```

---

## 🧙‍♂️ Observações

- Este projeto é puramente acadêmico.
- Não usar em produção a menos que queira causar um colapso no multiverso cinematográfico.

---

## 📜 Licença

Projeto com fins educacionais. Sinta-se livre para estudar, modificar e contribuir.