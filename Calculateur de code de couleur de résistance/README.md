# Projet Odometry Suiveur de ligne 

L'objectif du projet était la réalisation d'une application qui convertisse les anneaux de couleur des
résistances en sa valeur numérique et inversement.  

Ça commencée d'après un plaint d'une plateforme de commerce de composants électroniques qu'elle
a un mal à l'aise avec les clients qui n'arrivent pas bien à faire comprendre exactement le type de résistance
qu'ils veulent. LabVIEW, le logiciel utilisé qui nous a permet de construire cette application en utilisant des
Cases structures des Events et les Séquentielles pour bien écrire notre programme.

## Configuration matérielle
📝

Notre projet se constitue de deux sous VIs qui seront exploité au sein d'un VI principal qui permettra
de sélectionner l'opération de conversion voulue après que l'opérateur se soit identifié. Avec la possibilité
de faire plusieurs conversions de suite.  
  
On a utilisé comme des fonctions particulières :  
  
- Le modulo dans notre sous VI qui nous permet de citer une couleur pour chaque numéro.
- Un différent appel des sous VI d’après le VI principal, on a utilisé directement Path pour
appeler un sous VI.
- Pour mieux comprendre notre programme et pour qu’il soit plus structuré on a utilisé des
LAYOUTs qui nous facilite d’aller d’une page à une autre.
- Un stop der programme plus un message display lors 3 fausse essayes d’identification.
## Configuration logicielle

📝
Un VI principal qui nécessite une identification pour accéder à une page qui nous donne le choix entre deux
opérations, soit une conversion Valeur à une couleur soit une Valeur à une Couleur. Avec chaqu’un des
opérations est programmées dans un Sous VI. Donc on a fini par avoir deux Sous VI et un VI principal 
    
1/ Le choix de conversion Valeur à une couleur (SV1), permet à l’opérateur de :
- Tapez une Valeur décimale.
- Sélectionner un Multiplicateur.
- Sélectionner une Tolérance.
- Sélectionner un Coefficient thermique.
Après la saisie et la sélection des valeurs un bouton nommé « Color code » apparaitre qui exécute la
conversion et affiche le code couleur correspondant.   

2/ Le choix de conversion Couleur à une Valeur (SV2), permet à l’opérateur de :
- Saisir séquentiellement la couleur de 6 anneaux.
Après le choix de la 6
ème couleur de la résistance un bouton nommé « Résistance value » apparaitre qui
exécute la conversion et affiche la valeur de la résistance sous la forme :
‘’ ( Rnominale ± tolérance )multiple Ω /Coeff. Temp ‘’   

3/ Quelques Propriétés qu’on a développées :
- Après 3 essayes d’identification si le nom ou prénom ou le mot de passe sont incorrecte le
programme s’arrêtera tout seul.
- Si l’identification était correcte une LED nommé ‘’ Login & Password ‘’ s’allumera en verte.
- Si l’identification était correcte un affichage apparaitre de forme ‘’ Bienvenue !
@nom_de_l_opérateur ‘’.
- Un bouton qui permet à l’opérateur de faire plusieurs conversions.
- Un bouton qui permet de « Déconnecter »
- Un bouton qui permet de stopper le programme en retournant à la première page.  

## Compilation et téléversement
📝

Sélectionnez le type de carte Arduino et le port série appropriés dans l'IDE Arduino. Compilez le code et vérifiez s'il y a des erreurs. Si la compilation est réussie, téléversez le code sur la carte Arduino.

## Utilisation
📝

Assurez-vous que le robot est correctement assemblé et que les moteurs sont alimentés. Placez le robot sur une surface plane, allumez-le et observez son comportement. Si le robot dévie lorsqu'il est censé se déplacer en ligne droite, ajustez les valeurs de vitesse dans le code pour obtenir un déplacement plus précis.

## Avertissement

🤝  

Prenez les précautions nécessaires lors de l'assemblage et de l'utilisation du robot. Éteignez toujours le robot avant de modifier ou de travailler sur les connexions électriques pour éviter les risques de courts-circuits ou de chocs électriques. Soyez conscient de votre environnement et des personnes autour lorsque le robot est en mouvement.


🤝  



https://github.com/momenacer/MENACER_Mohamed/assets/127967325/02931a98-f556-4b52-9c17-0b3a6b6db077




![image](https://logovtor.com/wp-content/uploads/2020/11/arduino-open-source-community-logo-vector.png)

<p><img align="center" src="https://github-readme-streak-stats.herokuapp.com/?user=momenacer&" alt="momenacer" /></p>
