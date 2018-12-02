# Estimation du Mouvement
# Note : codes are commented in french in this section , i'll provide english comments later
Le travail séminal de Horn et Schunck est la première méthode variationnelle pour
l'estimation du flux optique. Il a introduit un nouveau cadre où le flux optique est calculé
comme la solution d'un problème de minimisation. De l'hypothèse que les intensités des
pixels ne changent pas au fil du temps, l'équation de contrainte de flux optique est dérivée.
Cette équation relie le flux optique aux dérivées de l'image. Il y a une infinité de champs
de vecteurs qui satisfont la contrainte de flux optique, donc le problème était mal posé.
Pour surmonter ce problème, Horn et Schunck ont introduit une condition de régularité
supplémentaire qui restreint les solutions possibles. Leur méthode minimise à la fois la
contrainte de flux optique et l'amplitude des variations du champ d'écoulement, produisant
des champs de vecteurs lisses.
Une des limites de cette méthode est que, typiquement, elle ne peut qu'estimer les
petits mouvements. En présence de grands déplacements, cette méthode échoue lorsque le
gradient de l'image n'est pas assez lisse. Dans ce projet, nous décrivons : 
une implémentation de la méthode de : Horn et Schunck et introduisons également une stratégie multi-résolution pour faire face à des déplacements plus importants. Pour cette stratégie multi-échelle, nous créons une structure pyramidale d'images sous-échantillonnées.

# Example d'application :
Inputs : Image 1 & Image 2 ( un mouvement elementaire ) 
# Image 1
![alt text](https://github.com/AissamDjahnine/Mouvement_estimation/blob/master/image1.bmp)
# Image 2
![alt text](https://github.com/AissamDjahnine/Mouvement_estimation/blob/master/image2.bmp)
# Resultats ( via matlab ) : 
![alt text](https://github.com/AissamDjahnine/Mouvement_estimation/blob/master/u_v.bmp)




