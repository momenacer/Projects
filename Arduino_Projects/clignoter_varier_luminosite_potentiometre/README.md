# Clignotement de LED avec variation de luminosité à l'aide d'un potentiomètre

Ce code consiste à réaliser un programme qui fait clignoter une LED tout en permettant de contrôler la luminosité de celle-ci à l'aide d'un potentiomètre. La LED s'allume et s'éteint périodiquement, et l'intensité lumineuse varie en fonction de la position du potentiomètre.

## Matériel requis

- Une LED
- Une résistance appropriée pour la LED
- Un potentiomètre
- Un microcontrôleur compatible avec la programmation de la LED et la lecture du potentiomètre (par exemple, Arduino)

## Fonctionnement

Le programme effectue les étapes suivantes :

1. Initialise les broches du microcontrôleur pour contrôler la LED et lire la valeur du potentiomètre.
2. Démarre une boucle infinie.
3. Lit la valeur du potentiomètre pour obtenir la position du curseur.
4. Utilise la valeur du potentiomètre pour ajuster la luminosité de la LED en utilisant la modulation de largeur d'impulsion (PWM). La valeur lue est convertie en une valeur de PWM appropriée pour contrôler l'intensité lumineuse de la LED.
5. Allume et éteint la LED à intervalles réguliers pour créer l'effet de clignotement.
6. Répète les étapes 3 à 5 en boucle pour maintenir le clignotement de la LED en fonction de la position du potentiomètre.

## Configuration et utilisation

1. Assurez-vous que la LED est correctement connectée à la broche PWM du microcontrôleur et qu'une résistance appropriée est utilisée pour limiter le courant.
2. Connectez le potentiomètre à une entrée analogique du microcontrôleur.
3. Téléchargez le programme sur le microcontrôleur.
4. Alimentez le microcontrôleur.
5. La LED clignotera à une luminosité variable en fonction de la position du potentiomètre.

## Remarques

- Vous pouvez ajuster la vitesse de clignotement et la plage de variation de luminosité en modifiant les délais et les valeurs de PWM dans le code.
- Assurez-vous de respecter les spécifications de votre microcontrôleur en termes de tension, de courant et de broches utilisées pour contrôler la LED et lire le potentiomètre.

N'hésitez pas à personnaliser ce projet en ajoutant des fonctionnalités supplémentaires, telles que la mise en œuvre d'un gradateur de lumière ou la synchronisation avec d'autres périphériques. Amusez-vous bien !











![image](https://arduino.developpez.com/tutoriels/arduino-a-l-ecole/images/image-112.png)
