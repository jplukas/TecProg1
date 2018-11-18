O programa deve ser capaz de receber a especificação de jogos como entrada e produzir/rodar esse jogo. As informações que devem conter na especificação são: especificações de elementos, lugares, objetos, etc...; A CONCLUIR

Sobre a função pegar:
Essa função deve retirar um elemento x da lista Conteudo de outro elemento A e colocá-lo na lista Conteudo do elemento Aventureiro. Sendo assim, devemos considerar o seguinte: segundo a especificação dada no enunciado sobre os verbos/acoes, cada um deve ser implementado como uma função de duas variáveis, para poderem atuar como verbos intransitivos, transitivos e bitransitivos. Porém, para este caso, há 3 entidade envolvidas: O elemento que será retirado, o lugar de onde ele será retirado e o aventureiro. Sendo assim, há de se pensar em como implementar essa função. Uma opção possível é fazer com que o Elemento Aventureiro seja uma variável única e global, que será referenciada na função, mas não será passada como argumento para ela.

Outra solução possível seria utilizar funções variádicas, que tem um número variável de argumentos, como a printf, por exemplo. Porém, essa ideia vai contra a especificação dos verbos/ações descrita em [aventura.pdf](aventura.pdf). Além disso, aparentemente escrever funções variádicas e genéricas é algo a se evitar, pois pode causar um problema chamado comportamento indefinido/imprevisível ([Undefined behaviour](https://en.wikipedia.org/wiki/Undefined_behavior)).

Assim, a solução que vamos adotar será a de se usar uma variável global para o aventureiro. Porém, isso levanta outra questão: onde irá ficar essa variável? Como faremos para acessá-la?
Se a instância do jogo for simplesmente um programa, podemos colocar essa variável dentro desse programa. Porém, temos que acessar essa variável de dentro de código que não vai estar, *a priori*, junto com o programa principal, a saber, temos que acessá-la de dentro de elemento.h.
Uma ideia interessante é colocar essa variável no próprio elemento.h, assim eliminamos esse problema, e não o teremos também, quando formos acessar essa variável de dentro do código do programa principal, pois teremos que importar elemento.h dele, ou seja, a variável Aventureiro, de tipo Elemento será uma "variável de classe" de elemento.h (ou de outra biblioteca, se assim for decidido).

Criar novos tipos de elemento: NPC e INIMIGO. Um NPC (non-playable character) será uma personagem do jogo com quem o aventureiro poderá interagir (como um homem velho em uma caverna...), mas não poderá ser controlado. Um INIMIGO é, por definição, um inimigo. Pode ser usado para que haja uma luta, em um determinado ponto da história. 

O "atributo" descrição longa de um elemento que seja um LUGAR será usado para fazer uma apresentação do lugar em que o aventureiro se encontra, por exemplo: "Você se vê em um lugar cheio de computadores, e vários estudantes estão usando esses computadores.
Você está sentado em uma mesa com um computador também, mas não está usando-o. Ao seu lado você vê uma pessoa aparentemente dormindo debruçada em uma das mesas. Há duas saídas de lados opostos da sala."

