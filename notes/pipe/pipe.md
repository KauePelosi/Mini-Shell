# Pipe

## O que é:
Dentro de um shell a pipe é uma estrutura que conecta a saída de um comando a entrada de outro.

### Exemplo:

```
ls -l | grep ".cpp"
```

O comando "ls -l" lista os arquivos de determinado diretório com mais detalhes, a partir disso a pipe redireciona essa saída de dados como entrada para o comando "grep .cpp" que faz com que sejam listados apenas os arquivos com a extensão .cpp daquele diretório.

## Objetivo e utilidade:
O pipe nasce de alguns conceitos do Unix que dizem:
```
"Faça uma coisa e a faça bem".
```

Dessa forma o real poder e utilidade do pipe é a praticidade que ele te da ao permitir que comandos pequenos se conectem entre si de forma extremamente rápida e organizada.

## Como funciona:
A pipe estabelece uma comunicação direta com o kernel, criando um túnel de comunicação onde a saída de programa X (stdout) se transfora na entrada do programa Y (stdin). O mais interessante é que a comunicação entre os comandos utilizando a pipe como ponte acontece em tempo real, ou seja, enquanto comando X está gerando sua saída, comando Y já está consumindo a mesma.

### Na memória
O que ocorre ainda mais internamente é a criação de vários processos ao mesmo tempo, com o uso do comando fork() que pede ao kernel linux que crie um processo novo inicialmente igual ao processo que chamou o fork().

Tomando como exemplo novamente o comando:

```
ls -l | grep ".cpp"
```

Na execução desse comando pelo shell, acontece o seguinte:

* O shell detecta se na entrada do usuário existe alguma pipe (|).

* A partir da identificação da pipe, o shell cria um fd (filedescriptor), que é um identificador em forma de inteiro que tem o objetivo de informar ao kernel o que está acontecendo com os arquivos (o kernel linux trata tudo como arquivos), através do comando "int fd[[2]]" onde fd[[0]] representa a leitura (consumo dos dados - stdin) e fd[[1]] representa a escrita (envio dos dados - stdout)

* O shell pede ao sistema operacional que crie dois processos novos com o fork(), um para cada comando;

* O shell então utiliza o comando dup2 para redirecionar a saída do comando ls -l para a pipe que a direciona como entrada para o comando grep ".cpp".

Exemplo visual
```
ls -l stdout -> fd[1] pipe fd[0] -> stdin grep
```

## Conclusão
A pipe é um mecanismo essencial de comunicação entre processos porque facilita demais a vida.
Futuramente pretendo adicionar mais documentações, principalmente de teor técnico do meu aprendizado, aprofundando o funcionamento conforme evoluo a adição da pipe no meu shell.
