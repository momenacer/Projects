# Code Arduino avec Affichage LCD

Ce dépôt GitHub contient un code pour Arduino pour afficher du texte sur un écran LCD. Ce guide vous aidera à comprendre le projet et à le mettre en œuvre.

## Matériel requis
- Arduino Uno (ou tout autre modèle compatible)
- Écran LCD 16x2
- Potentiomètre 
- Câbles de connexion

## Branchement
- Connectez le GND de l'Arduino à la broche GND de l'écran LCD.
- Connectez le +5V de l'Arduino à la broche VCC de l'écran LCD.
- Connectez le pin 2 de l'Arduino à la broche RS de l'écran LCD.
- Connectez le pin 3 de l'Arduino à la broche E de l'écran LCD.
- Connectez les pins 4, 5, 6, 7 de l'Arduino à D4, D5, D6, D7 de l'écran LCD respectivement.
- Connectez le pin 11 de l'Arduino à la broche A de l'écran LCD.
- Connectez le pin central du potentiomètre à la broche V0 de l'écran LCD.
- Connectez les extrémités du potentiomètre respectivement à la broche GND et à la broche +5V de l'écran LCD.

## Bibliothèque requise
- LiquidCrystal : Vous pouvez l'installer via le gestionnaire de bibliothèques Arduino.

## Code
Le fichier `LCD.ino` contient le code source pour afficher du texte sur l'écran LCD. Assurez-vous d'ouvrir ce fichier dans l'IDE Arduino et de téléverser le code sur votre carte Arduino.

## Utilisation
Après avoir téléversé le code sur votre Arduino, l'écran LCD affichera le texte défini dans le code. Vous pouvez modifier le texte en modifiant la ligne appropriée dans la fonction `setup()` du code.

## Contributions
Les contributions à ce projet sont les bienvenues. Si vous trouvez des problèmes ou si vous avez des suggestions d'amélioration, n'hésitez pas à ouvrir une demande d'extraction (pull request) ou à signaler un problème (issue) dans le dépôt GitHub.
  
    
![image](https://i.ytimg.com/vi/pmg9dOT1aAM/maxresdefault.jpg)
