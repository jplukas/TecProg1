O programa deve ser capaz de receber a especificação de jogos como entrada e produzir/rodar esse jogo. As informações que devem conter na especificação são: especificações de elementos, lugares, objetos, etc...; A CONCLUIR

Sobre a função pegar:
Essa função deve retirar um elemento x da lista Conteudo de outro elemento A e colocá-lo na lista Conteudo do elemento Aventureiro. Sendo assim, devemos considerar o seguinte: segundo a especificação dada no enunciado sobre os verbos/acoes, cada um deve ser implementado como uma função de duas variáveis, para poderem atuar como verbos intransitivos, transitivos e bitransitivos. Porém, para este caso, há 3 entidade envolvidas: O elemento que será retirado, o lugar de onde ele será retirado e o aventureiro. Sendo assim, há de se pensar em como implementar essa função. Uma opção possível é fazer com que o Elemento Aventureiro seja uma variável única e global, que será referenciada na função, mas não será passada como argumento para ela.

Outra solução possível seria utilizar funções variádicas, que tem um número variável de argumentos, como a printf, por exemplo. Porém, essa ideia vai contra a especificação dos verbos/ações descrita em [aventura.pdf](aventura.pdf).

