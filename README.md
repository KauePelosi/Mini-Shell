🐚 MiniShell
Um interpretador de comandos simples desenvolvido em C++ para fins de aprendizado de Sistemas Operacionais e gerenciamento de memória. Este projeto simula o comportamento básico de um Shell (como Bash ou Zsh), permitindo a execução de comandos internos e externos.

🚀 Funcionalidades Atuais
Tokenização Eficiente: Processamento de entrada do usuário usando std::move para evitar cópias desnecessárias.

Comandos Internos (Built-ins): Sistema de despacho via std::unordered_map para execução rápida (ex: cd).

Comandos Externos: Execução de binários do sistema via fork() e execvp().

Modularidade: Estrutura de código dividida entre tokenize, dispatcher, e lógica de execução.

🛠️ Tecnologias e Conceitos Aplicados
C++17/20: Uso de std::string_view para otimização de chaves de busca.

RAII & Smart Memory: Uso de referências e movimentação de objetos (std::move) para performance.

POSIX API: Manipulação de processos (pid_t, waitpid) e sistema de arquivos (chdir, getcwd).

📋 Próximos Passos (Backlog)
[ ] Aprimorar Tokenize: Adicionar suporte para aspas (ex: cd "Pasta com Espaço").

[ ] Segurança de Memória: Substituir const_cast por cópias seguras no tratamento de argumentos para o execvp.

[ ] Expansão de Comandos: Implementar exit, pwd e help.

[ ] Gerenciamento de Sinais: Tratar Ctrl+C (SIGINT) para não encerrar o Shell acidentalmente.

[ ] Otimização de Container: Implementar reserve() no vetor de tokens para evitar realocações custosas.

🏗️ Como Compilar e Rodar
Bash
# Compile o projeto
g++ -Iinclude src/*.cpp -o minishell

# Execute
./minishell
