# Clignotement et fondu d'une LED

Ce code consiste à réaliser un programme qui fait clignoter une LED en utilisant la technique du fading (variation progressive de l'intensité lumineuse). La LED s'allume progressivement jusqu'à atteindre sa pleine luminosité, puis s'éteint progressivement avant de recommencer le cycle de clignotement.

## Matériel requis

- Une LED
- Une résistance appropriée pour la LED
- Une carte Arduino

## Fonctionnement

Le programme utilise une technique appelée modulation de largeur d'impulsion (PWM) pour simuler le fading de la LED. La PWM permet de contrôler l'intensité lumineuse en ajustant la durée de l'état allumé et de l'état éteint de la LED sur de courtes périodes.

Le programme effectue les étapes suivantes :

1. Initialise les broches du microcontrôleur pour contrôler la LED.
2. Démarre une boucle infinie.
3. Incrémente progressivement la valeur de la PWM de 0 à sa valeur maximale, ce qui fait augmenter progressivement l'intensité lumineuse de la LED.
4. Une fois la valeur maximale atteinte, décrémente progressivement la valeur de la PWM de sa valeur maximale à 0, ce qui fait diminuer progressivement l'intensité lumineuse de la LED.
5. Répète les étapes 3 et 4 en boucle pour obtenir un effet de clignotement avec fading.

## Configuration et utilisation

1. Assurez-vous que la LED est correctement connectée à la broche PWM du microcontrôleur et qu'une résistance appropriée est utilisée pour limiter le courant.
2. Téléchargez le programme sur le microcontrôleur.
3. Alimentez le microcontrôleur.
4. La LED commencera à clignoter avec un effet de fading automatiquement.

## Remarques

- Vous pouvez ajuster la vitesse du fading en modifiant les délais entre les incréments et les décréments de la valeur de la PWM.
- Assurez-vous de respecter les spécifications de votre microcontrôleur en termes de tension, de courant et de broches utilisées pour contrôler la LED.

N'hésitez pas à personnaliser ce code en ajoutant des fonctionnalités supplémentaires, telles que la variation de la couleur de la LED ou la synchronisation avec d'autres périphériques. Amusez-vous bien !








![image](https://github.com/L3-Option-TSI-2023/Mohamed-MENACER/assets/127967325/21ef5935-3238-43b2-a3e5-8b5506063ed3)
