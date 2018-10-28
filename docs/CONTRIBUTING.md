# Como contribuir para o projeto

Aqui estão algumas diretivas que iremos adotar na hora de fazer contribuições para o projeto. Siga essas diretivas na hora de fazer decisões de desenvolvimento, abrir uma ***issue*** ou fazer um ***pull request***.

Primeiramente, você deve estar familiarizado com o **GitHub *workflow***. Caso contrário, leia a [documentação do **GitHub**](https://guides.github.com/). Nela se encontra tudo o que você precisa saber sobre como usar corretamente o fluxo de trabalho do **Git**.


## Estilo e documentação
Todo o código do projeto deve conter uma boa documentação, tanto interna quanto externa. Procure fazer isso escrevendo código limpo, intuitivo e elegante, comentando seu código sempre que julgar necessário e escrevendo *commit messages* e *commit descriptions* claras e concisas. Sobre os comentários, pense que seu código deve ser legível e intuitivo o bastante para que seja necessário escrever o mínimo de comentários possível, **mas não deixe de escrevê-los**.
Como este é um projeto em grupo, e o desenvolvimento é colaborativo, tenha em mente que outras pessoas lerão seu código várias vezes durante o curso do projeto. Sendo assim é necessário haver uma coerência de estilo na hora de escrever seu código. Procure seguir as convenções adotadas pelo grupo e discutir novas, sempre que quiser.
Além disso, sinta-se à vontade para propor mudanças e adicionar novas páginas à documentação do projeto.


## Decisões de desenvolvimento
**TODAS** as decisões que forem tomadas durante o desenvolvimento do projeto (como: estruturas de dados usadas, relações entre essas estruturas, algoritmos usados, interfaces) devem ser justificadas. Procure sempre utilizar estruturas que garantam melhor eficiência de tempo de processamento e memória utilizada, de acordo com seus fins. (Exemplo: se a operação que mais for realizada em uma determinada estrutura seja a busca, seria melhor optar por um vetor, ou árvore binária, do que uma lista ligada).
Deixe explícito o porquê de tal estrutura ser usada em detrimento de outra, citando a complexidade das operações (busca, inserção, remoção, etc...).


## Colaborações
**NUNCA** faça alterações diretamente no ramo *master*. Você deve sempre abrir um novo *branch* para escrever seu código, e então, quando estiver pronto, faça uma *pull request*. Todas as *pull requests* devem ser discutidas e avaliadas por **todos** os integrantes do grupo antes de serem adicionadas ao ramo *master*.
**SEMPRE** adicione unidades de teste para seu código para que os outros integrantes possam testá-lo, e teste-o você mesmo, a fim de evitar trabalho desnecessário.
Tente participar de todas as discussões envolvendo o projeto.
Leia, inspecione e teste o código de todos os integrantes.
