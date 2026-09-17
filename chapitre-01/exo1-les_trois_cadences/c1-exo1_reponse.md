# calcul de la durée d’une image et soustraction des 8ms que prennent les capteurs 
a) à 72Hz
d=1000/72 =13,9ms
d-8 = 13,889-8=5,9ms
ici le temps restant pour le code est de 5,9ms

b) à 90Hz
d=1000/90 =11,1ms
d-8 = 11,1-8=3,1ms
le temps restant ici pour le code est de 3,1ms

c) à 120Hz
d=1000/120 =8,3ms
d-8= 8,3-8=0,3 ms
le temps restant ici pour le code est de 0,3ms
donc nous avons :
- 5,9ms à 72Hz
- 3,1ms à 90Hz
- 0,3ms à 120Hz

nous constatons que à 120Hz, il ne reste presque plus de temps pour le code.

calculons les proportions du budget à :
- 72Hz :
P=(8/13,9)100=57,6%
- 120Hz:
  P=(8/8,3)100=96,3%

 une cadence plus élevée est un avantage pour l’utilisateur seulement si le temps fixe imposé reste petit par rapport au nouveau budget. quand il arrive à un certain niveau ce temps fixe occupe presque tout l’espace disponible et rendre le programme impossible à exécuter.

 trouvons le niveau pour lequel le budget est saturé à 100%

 d=1000/f. ici, d=8
 8=1000/f
 f=1000/8=125Hz
 donc en conclusion, avec un budget fixe de 8ms par image, la cadence ne doit pas dépasser les 125Hz sinon le programme est impossible à exécuter.


La limite de 125 Hz reste vraie pour un rendu où chaque image est vraiment calculée; les casques à 144 Hz ne dépassent pas cette limite ils la contournent grâce à la reprojection qui est une technique qui déforme une image déjà rendue selon les nouveaux mouvements de tête au lieu de recalculer une image complète. le casque affiche donc plus souvent une information retouchée plutôt que plus souvent une nouvelle information . mais dès que l'utilisateur se déplace, des zones cachées qui étaient cachées derrière les objets deviennent visibles sans qu'aucune image précédente ne contienne cette information — la reprojection doit alors l'inventer, ce qui produit des artefacts visibles aux bords des objets proches et prouve que cette technique ne dispense jamais de dessiner vraiment la scène.
