# Contrôle du rapport cyclique d'une LED avec un potentiomètre sur Arduino

Ce code consiste à utiliser un potentiomètre pour contrôler le rapport cyclique d'un signal PWM (Pulse Width Modulation) généré par Arduino et ainsi ajuster l'intensité lumineuse d'une LED.

## Matériel requis

- Une carte Arduino
- Un potentiomètre
- Une LED
- Une résistance appropriée pour la LED
- Des fils de connexion

## Fonctionnement

Le programme effectue les étapes suivantes :

1. Connecte le potentiomètre à une broche analogique de l'Arduino.
2. Configure une broche de sortie pour générer un signal PWM.
3. Connecte la LED à la broche de sortie PWM et ajoute la résistance en série pour limiter le courant.
4. Démarre une boucle infinie.
5. Lit la valeur du potentiomètre à l'aide de la fonction `analogRead()`.
6. Convertit la valeur lue en une valeur de rapport cyclique comprise entre 0 et 255 (pour une résolution de 8 bits).
7. Utilise la fonction `analogWrite()` pour générer un signal PWM avec le rapport cyclique calculé.
8. Répète les étapes 5 à 7 en boucle pour mettre à jour en temps réel le rapport cyclique et ajuster l'intensité lumineuse de la LED en fonction de la position du potentiomètre.

## Configuration et utilisation

1. Connecte le potentiomètre à une broche analogique de l'Arduino.
2. Connecte la broche de sortie PWM de l'Arduino à la résistance, puis à la LED (l'anode de la LED doit être connectée à la résistance).
3. Connecte la cathode de la LED (le côté opposé à l'anode) à la masse (GND) de l'Arduino.
4. Télécharge le programme sur l'Arduino.
5. Alimente l'Arduino.
6. Fais tourner le potentiomètre pour ajuster l'intensité lumineuse de la LED en contrôlant le rapport cyclique du signal PWM.

## Remarques

- Assure-toi de respecter les spécifications de la LED et de la résistance utilisées pour éviter de les endommager.
- Tu peux personnaliser ce projet en ajoutant d'autres fonctionnalités, telles que l'utilisation d'un écran LCD pour afficher la valeur du rapport cyclique ou l'utilisation d'un potentiomètre plus précis pour obtenir une meilleure résolution.
- N'oublie pas de faire attention aux polarités lors du câblage de la LED et de la résistance.

Amuse-toi bien en contrôlant l'intensité lumineuse de ta LED avec Arduino et le potentiomètre !




![image](https://mataucarre.fr/wp-content/uploads/2019/03/led_potentiometre_arduino-300x235.png)
