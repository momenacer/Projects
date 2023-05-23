# Calculateur de vitesse de roue Arduino

Ce code Arduino est conçu pour calculer la vitesse d'une roue. Il utilise un microcontrôleur Arduino.

## Matériel requis
- Arduino (par exemple, Arduino Uno)
- Capteur de vitesse (dans le moteur)
- Roue à mesurer

## Montage du circuit
1. Connectez le fil de signal du capteur de vitesse ( de moteur) à une broche numérique de l'Arduino (par exemple, broche 2).
2. Connectez le fil de puissance du capteur de vitesse  ( de moteur) à la broche 5V de l'Arduino.
3. Connectez le fil de mise à la terre du capteur de vitesse à la broche GND de l'Arduino.

## Téléchargement du code
1. Clonez ou téléchargez le code source à partir du référentiel GitHub.
2. Ouvrez le fichier `calcul_vitesse_roue.ino` dans l'IDE Arduino.

## Configuration
1. Définissez la broche de signal du capteur de vitesse en utilisant la constante `VITESSE_PIN`. Par exemple : `const int VITESSE_PIN = 2;`.

## Calibration
Pour obtenir des résultats précis, vous devrez peut-être calibrer le code en fonction de votre configuration spécifique. Voici les étapes recommandées :
1. Mesurez la circonférence de votre roue en centimètres (par exemple, 5 cm).
2. Modifiez la valeur de la constante `CIRCONFERENCE_ROUE` dans le code pour correspondre à votre mesure : `const float CIRCONFERENCE_ROUE = 5.0;`.
3. Téléversez le code sur votre Arduino.

## Utilisation
1. Une fois le code téléversé avec succès sur l'Arduino, ouvrez le moniteur série dans l'IDE Arduino.
2. Mettez la roue en mouvement.
3. Le moniteur série affichera la vitesse de la roue en kilomètres par heure (cm/s).



![image](https://passionelectronique.fr/wp-content/uploads/test-moteur-jaune-L298N-12V-arduino-uno.jpg)
