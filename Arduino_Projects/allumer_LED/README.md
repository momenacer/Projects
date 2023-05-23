# Contrôle de LED avec Arduino

Ce dépôt contient un code Arduino simple permettant de contrôler une LED.

## Matériel requis
- Carte Arduino
- LED
- Résistance (adaptée à la LED)
- Fils de connexion

## Schéma de câblage
Connectez la LED à la carte Arduino de la manière suivante :
- Reliez la patte la plus longue de la LED (anode) à une broche de sortie numérique de la carte Arduino (par exemple, la broche 13).
- Connectez la patte la plus courte de la LED (cathode) à une résistance appropriée (généralement 220 ohms).
- Reliez l'autre extrémité de la résistance à la masse (GND) de la carte Arduino.

Assurez-vous que la LED est correctement câblée avant de téléverser le code.

## Téléversement du code
1. Installez l'IDE Arduino si ce n'est pas déjà fait.
2. Clonez ou téléchargez ce dépôt.
3. Ouvrez le fichier `led_control.ino` dans l'IDE Arduino.
4. Sélectionnez le type de carte Arduino correct dans le menu "Outils".
5. Sélectionnez le port série approprié dans le menu "Outils".
6. Cliquez sur le bouton "Téléverser" pour envoyer le code vers la carte Arduino.

## Utilisation
Après avoir téléversé le code sur la carte Arduino, la LED s'allumera et s'éteindra toutes les secondes. Vous pouvez ajuster le délai d'allumage/extinction de la LED en modifiant la variable `delayTime` dans le code.

## Contributions
Les contributions sont les bienvenues ! Si vous souhaitez améliorer ce code, n'hésitez pas à ouvrir une demande de fusion (pull request).





![image](https://tesseract-it.com/assets/img/blog/arduino-plan-1.png)
