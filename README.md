# Response-monitor

Implementação de um programa de monitoramento para HTTP(http method), DNS(dns lookup), PING(icmp echo)

## Etapas de desenvolvimento
1. Pesquisa dos conceitos
2. Consulta a documentação do curl por causa da sua capacidade de fazer requisições HTTP e consulta DNS
3. Estruturação baseado em OOP devido ao encapsulamento e ao polimorfismo que vai nos permitir simplificar o frontend e facilitar a extensibilidade
4. Implementação das flags

## Bibliotecas usadas
 - libcurl
 - pthread
 - libc
 - c-ares
Para mais detalhes consultar o header monitor

## Compilação
```
make
```

## Uso
```
./monitoring <flag> <arg quando permitido>
```
|flag| Descrição |
|----|-----------|
| --config-file | Usa o arquivo de configuração fornecido. Aceita argumento |
| --analyze-time | Calcula a media, mediana e os outliers de acordo com o protocolo (Não faz distinção de host) |
| --simplify | Conta quant requisições foram feitas agrupando por protocolo |
| --help | Mostra uma mensagem de ajuda |
