
# Contrôle de sept LEDs avec fading contrôlé par un potentiomètre sur Arduino

Ce code permet de contrôler l'allumage de sept LEDs individuelles en utilisant une technique de fading (variation d'intensité lumineuse). Chaque LED peut être ajustée en intensité à l'aide d'un potentiomètre.

## Matériel requis

- Une carte Arduino
- Un potentiomètre
- Sept LEDs
- Sept résistances appropriées pour les LEDs
- Des fils de connexion

## Fonctionnement

Le programme effectue les étapes suivantes :

1. Connecte le potentiomètre à une broche analogique de l'Arduino.
2. Connecte chaque LED à une broche de sortie de l'Arduino, en ajoutant une résistance appropriée en série pour chaque LED.
3. Démarre une boucle infinie.
4. Lit la valeur du potentiomètre à l'aide de la fonction `analogRead()`.
5. Convertit la valeur lue en une valeur comprise entre 0 et 255 (pour une résolution de 8 bits).
6. Utilise la fonction `analogWrite()` pour ajuster le rapport cyclique de chaque LED en fonction de la valeur lue.
   - Plus la valeur est élevée, plus l'intensité lumineuse de la LED sera élevée.
   - Plus la valeur est faible, plus l'intensité lumineuse de la LED sera faible.
7. Répète les étapes 4 à 6 en boucle pour mettre à jour en temps réel l'intensité lumineuse des LEDs en fonction de la position du potentiomètre.

## Configuration et utilisation

1. Connecte le potentiomètre à une broche analogique de l'Arduino.
2. Connecte chaque LED à une broche de sortie de l'Arduino, en ajoutant une résistance appropriée en série pour chaque LED.
3. Télécharge le programme sur l'Arduino.
4. Alimente l'Arduino.
5. Fais tourner le potentiomètre pour ajuster l'intensité lumineuse des sept LEDs.

## Remarques

- Assure-toi de respecter les spécifications des LEDs et des résistances utilisées pour éviter de les endommager.
- N'oublie pas de faire attention aux polarités lors du câblage des LEDs et des résistances.

Amuse-toi bien en contrôlant l'intensité lumineuse des sept LEDs avec le potentiomètre sur Arduino !

![image](https://europe1.discourse-cdn.com/arduino/original/4X/6/4/d/64d52555a54b670362392326ca5aa07554b8c226.jpeg)
