TextMining Project
===

# Docker (recommanded way)

Generate executables

```bash
# TODO
```

# Configure

At the root-level:
```bash
$ bash configure

# It should create /out and /bin directories
```

# Launch (production)

Execute the following command:
```bash
$ make
```
> Executables will be found under **bin/release**

# Launch (debug)

From Visual Studio Code, execute the default task to generate the debug configuration.
> Executables will be found under **bin/debug**

# Clean

Execute the following command:
```bash
$ make distclean
```

# Questions

**1. Decrivez les choix de design de votre programme**

Le programme utilise un patricia trie pour stocker le dictionnaire de mot, une distance de Damereau-Levenshtein pour calculer la distance entre 2 mots, et une recherche approximative de mots ressemblant optimisé.

Ce patricia trie est représenté par une classe *Patricia_trie* contenue dans le fichier *patricia_trie.cc*. Cette classe contient un vecteur de pointeur sur noeuds, correspondant à ses fils, qui sont eux mêmes des patricia trie *(std::vector<Patricia_trie\*>)*. La classe contient aussi une string *data_* et un entier de fréquence *freq_*. Chaque noeuds correspond ainsi à une instanciation de la classe.
Un noeud contient la fin d'un mot si sa fréquence est nulle, et si le dernier caratère de sa string *data_* est un *$*.

La fonction de calcule de distance utilises l'algorithme vu en cours, en ayant cours à une matrice (un std::vector<stc::vector<>> sur entiers).

La recherche approximative de patricia trie parcours récursivement l'arbre, et de façon à éviter les parcours inutiles en ignorant certaines branches de l'arbre (en regardant au préalable la taille du prochain mot par exemple).

**2.	Listez l’ensemble des tests effectués sur votre programme (en plus des units tests)**

L'ensemble des testes effectués portent sur :

- la bonne construction du patricia trie (vision avec une fonction de pretty-printer)
- la distance de Damereau-Levenshtein entre 2 mots
- le bon ensemble de mots résultants en comparaison avec la ref
- le bon ordre de trie des résultats (distance, fréquence, mots)

**3.	Avez-vous détecté des cas où la correction par distance ne fonctionnait pas (même avec une distance élevée) ?**

Pas de disfonctionnements détectés lors des testes effectués.

**4.	Quelle est la structure de données que vous avez implémentée dans votre projet, pourquoi ?**

Un trie a initialement été implémentée, car c'est une structure de donnée assez simple à codé et à exploiter, mais il n'était pas suffisamment optimisé pour passer les contraintes de RAM. En effet, il utilise trop de noeuds, soit 1 noeud par charactère. Un patricia trie à donc été implémentée, il "compactes" les noeuds communs entre eux afin de stocker non pas 1 charactère mais une chaîne de charactère par noeud. Les différences de perfomance et de mémoire se sont nettement améliorées.

**5.	Proposez un réglage automatique de la distance pour un programme qui prend juste une chaîne de caractères en entrée, donner le processus d’évaluation ainsi que les résultats**

On pourrait lancer la recherche approximative sur le patricia trie avec une distance temporaire étant égale à la taille du mots, puis réduire cette distance au fur et à mesure que la recherche trouve des mots avec une distance inférieure. Au niveau algorithmique, on pourrait utiliser une variable global *dist_tmp* qui diminuerai à chaque rencontre d'une distance inférieure, et qui pourrai être consulté et utilisé à chaque nouvel appel récursif, en tant que distance maximale autorisée. Enfin, on récupérerai seulement les mots avec la distance minimal retenue.

**6.	Comment comptez vous améliorer les performances de votre programme**

Plusieurs points peuvent être améliorés afin de booster les performances du programme :

- ne pas recalculer à chaque noeud la distance, mais utiliser un accumulateur (le fait d'accepter les transpositions complique les choses)
- réduire la taille des noeuds du patricia trie, par exemple en remplaçant les std::string par des char*
- utiliser d'autre structure que la STL peut offrir, afin de réduire au maximum le nombre de bit de padding
- utiliser une matrice de taille réduite pour la distance de Damereau-Levenshtein, en utilisant seulement 2 vecteurs à chaque fois par exemple
- lors de la recherche dans l'arbre, explorer en parrallèles plusieurs branches simultanément afin d'avoir un gain de temps

**7.	Que manque-t-il à votre correcteur orthographique pour qu’il soit à l’état de l’art ?**

Pour être à l'état de l'art, le correcteur orthographique pourrai prendre en compte :

- les erreurs de frappe liée au clavier, en prenant en compte la distance entre les lettres du clavier
- les erreurs phonétiques voir phonogrammique (ex: pharmacie - pharmatie)
- les erreurs liées à la normalisation (accent, cédille, majuscule, etc.)
- les erreurs liées à la calligraphie, par exemple les lettres qui se ressemble (ex: m/n, i/l, etc.)
- les erreurs liées à la coupure de mots (ex: aujourd'hui)
- les erreurs liées aux abréviations, en utilisant par exemple un dictionnaire d'abréviation connus

# Authors

EPITA School, SCIA Master 1 - Project for Text Mining and Natural Language Course. 

Authors: **BENSABAT David** (bensab_d)