# Laboratoire 01 - IFT630

|         |                  |
| :------ | :--------------- |
| Nom     | Ramasamy         |
| Prénoms | Luc Nathan       |
| CIPs    | raml2101         |

## Exécution du laboratoire

### Sans Docker 
Pour compiler et exécuter le programme sans Docker
```sh
make run
```

### Avec Docker (environnement de correction)
L'environnement de correction utilise `Docker`. Votre soumission sera 
compatible si vous : 
- Conservez les noms de fichiers d'origine
- N'ajoutez pas de bibliothèques externes (qui ne sont pas une 
  bibliothèque standard)

Pour tester votre code dans cet environnement avant la soumission, 
utilisez les commandes du `Makefile`.
```sh
make docker-run
```

## Questions

**Ligne 2** : Expliquez votre stratégie pour déterminer le nombre 
optimal de fils selon les valeurs de n,m,p.

Réponse: Afin de déterminer le nombre optimal de fils avec les valeurs de n, m et p, on regarde la taille de la matrice C résultant du produit de n lignes de A et m colonnes de B. Puisque C est une matrice n*p (dans notre cas 3*3), on peut la découper en n lignes qui correspondront à un fil d'exécution. Le fil regardera la ligne qui lui est attribué ainsi que les colonnes qui joignent la ligne regardée. Cela permettra aux fils de travailler indépendamment sur la matrice, évitant des problèmes de mémoire.

---
**Ligne 23** : Détaillez votre approche pour la création des 
différents fils d'exécution.

Réponse: Pour créer les fils d'exécution, on crée une boucle qui va créer un certain nombre de fils trouvés en ligne 2 (dans notre cas, 3). Le début du fil se trouve en prenant l'indice de la ligne donné au fil (ex. Le fil d'exécution 1 commence à la ligne 0 (un vecteur commence à 0 et pas 1)). La fin du fil est donnée par la valeur minimale entre i * taille_segment et n (le nombre de lignes de A et de C). Par exemple, la fin du thread 1 est au début de la ligne 1, car i * taille_segment est plus petit que n dans le cas où i = 1. Enfin, on crée les threads et on les stocke dans un vecteur.

---
**Ligne 26** : Justifiez votre méthode de synchronisation pour 
l'attente de la fin d'exécution des fils.

Réponse: Pour faire simple, en lançant la méthode join (attente de la fin d'exécution des fils) après la boucle de création des fils d'exécution, cela permet de lancer simultanément les threads crées dans la boucle, assurant un travail parallèle et une synchronisation correcte. Si le join() était dans la boucle, on devrait attendre que chaque thread finit avant de passer au prochain à créer, ce qui nous amène à faire du séquentiel et non du parallèle.
