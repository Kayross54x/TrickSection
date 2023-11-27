# TrickSection
Terceiro trabalho prático da matéria de algoritmos 1 onde uso conceitos de programação dinâmica e algoritmos gulosos juntamente com o problema da mochila. CC - UFMG

Descrição do problema:
Além do reino da Baicônia, existe outra sociedade fundada e mantida pelos preceitos fundamentais do Deboísmo: a comuna da Radlândia. Ao contrário de nossas amigas capivaras, a população da Radlândia não é a maior fã de ficar de boa na lagoa; ela prefere encontrar a paz universal para mandar bem no skate e falar sobre as manobras mais radicais que podem ser executadas nas infinitas pistas que existem na comuna.

Diná é uma nova moradora da Radlândia, que uma vez foi visitar sua amiga Mica e nunca mais quis ir embora. Ela agora está mergulhada no Deboísmo radlândico, absorvendo toda a cultura de sua nova casa. Como Diná não nasceu nem cresceu cercada de pistas que desafiam as leis da física, ela ainda não tem certeza de qual a sequência de manobras mais radical possível de se atravessar a pista do bairro.

Mas como é medida a radicalidade de uma travessia? Obviamente, a Radlândia tem seu próprio sistema de pontuação, que funciona da seguinte forma:

Uma pista tem N seções onde sequências de manobras podem ser realizadas (uma sequência pode ser vazia), com cada seção tendo um fator de bonificação ci e um tempo de travessia ℓi.

Existem apenas K manobras permitidas na comuna, com cada uma tendo uma duração tj e uma pontuação base pj. Cuidado: a pontuação base pode ser negativa!

Uma manobra pode ser realizada no máximo uma vez em cada seção da pista (não é da hora fazer spam), e nenhuma manobra pode ser feita parcialmente: ela deve começar e terminar dentro de uma seção.

Caso uma manobra seja feita em duas seções seguidas, sua pontuação é reduzida para ⌊pj/2⌋; por exemplo, se pj = 5, a nova pontuação é 2. Uma manobra feita na seção i mas não feita na seção i + 1 tem sua pontuação integral na seção i + 2.

A pontuação final de uma sequência de manobras ⟨m1, . . . , mr⟩ na seção com fator de bonificação ci é dada pelo somatório das pontuações de cada uma das r manobras vezes ci. Ou seja, se realizamos manobras com pontuações ⟨1, ⌊7/2⌋ , 2, 5⟩ em ci = 10, então temos uma sequência de manobras com valor total (1 + 3 + 2 + 5) · 10 · 4 = 440.

Ajude Diná a descobrir qual a travessia mais radical que ela pode fazer e impressionar Mica!

Formato da Entrada:
Cada caso de teste é composto por várias linhas. A primeira linha contém dois inteiros, N e K, que representam, respectivamente, o número de seções de manobra da pista e o número de manobras catalogadas na Radlândia; é garantido que 1 ≤ N ≤ 100 e 1 ≤ K ≤ 10. Cada uma das N linhas seguintes descreve uma seção da pista. A i-ésima dessas linhas contém dois inteiros: ci, que representa o fator de bonificação da seção (1 ≤ ci ≤ 100) e ℓi, que representa o tempo de travessia da seção (1 ≤ ℓi ≤ 10^6). Em seguida, temos K linhas, cada uma descrevendo uma manobra. A j-ésima dessas linhas contém dois inteiros: a pontuação base pj (-10^6 ≤ pj ≤ 10^6) da manobra e o tempo tj necessário para executar a manobra (1 ≤ tj ≤ 10^6); assuma que as manobras são numeradas de 1 a K na ordem que são dadas na entrada. Assuma que Diná é brilhante na mecânica do skate e consegue emendar uma manobra em outra sem nenhum problema. A entrada deve ser lida da entrada padrão.

Formato da Saída:
A saída contém múltiplas linhas. Na primeira linha deve ser impresso um único inteiro T, que representa a pontuação total máxima que Diná pode alcançar. Em seguida, seguem N linhas, cada uma com vários inteiros. A i-ésima dessas linhas representa a i-ésima seção de manobras. O primeiro inteiro ni nessa linha representa o número de manobras que devem ser feitas na seção; em seguida, devem ser impressos ni números, cada um representando uma manobra feita na i-ésima seção. A saída deve ser escrita na saída padrão.
