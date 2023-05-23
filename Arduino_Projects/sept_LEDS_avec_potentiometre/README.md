# Contrôle de sept LED avec un potentiomètre sur Arduino

Ce code consiste à utiliser un potentiomètre pour contrôler l'allumage de sept LED individuelles sur Arduino. Chaque LED peut être activée ou désactivée en fonction de la position du potentiomètre.

## Matériel requis

- Une carte Arduino
- Un potentiomètre
- Sept LED
- Sept résistances appropriées pour les LED
- Des fils de connexion

## Fonctionnement

Le programme effectue les étapes suivantes :

1. Connecte le potentiomètre à une broche analogique de l'Arduino.
2. Configure les sept broches de sortie pour contrôler les LED.
3. Connecte chaque LED à une broche de sortie et ajoute une résistance appropriée en série pour limiter le courant.
4. Démarre une boucle infinie.
5. Lit la valeur du potentiomètre à l'aide de la fonction `analogRead()`.
6. Convertit la valeur lue en une valeur comprise entre 0 et 1023 (pour une résolution de 10 bits).
7. Divise la valeur lue en plage égale pour contrôler l'allumage des sept LED.
8. Utilise la fonction `digitalWrite()` pour activer ou désactiver chaque LED en fonction de la plage de valeurs définie.
9. Répète les étapes 5 à 8 en boucle pour mettre à jour en temps réel l'allumage des LED en fonction de la position du potentiomètre.

## Configuration et utilisation

1. Connecte le potentiomètre à une broche analogique de l'Arduino.
2. Connecte chaque LED à une broche de sortie de l'Arduino, en ajoutant une résistance appropriée en série pour chaque LED.
3. Télécharge le programme sur l'Arduino.
4. Alimente l'Arduino.
5. Fais tourner le potentiomètre pour contrôler l'allumage des sept LED en fonction de sa position.

## Remarques

- Assure-toi de respecter les spécifications des LED et des résistances utilisées pour éviter de les endommager.
- Tu peux personnaliser ce projet en ajoutant des fonctionnalités supplémentaires, comme l'ajout d'un écran LCD pour afficher l'état des LED ou l'utilisation de boucles de couleurs pour les LED.
- N'oublie pas de faire attention aux polarités lors du câblage des LED et des résistances.

Amuse-toi bien en contrôlant les sept LED avec le potentiomètre sur Arduino !







![image](https://arduino.developpez.com/tutoriels/arduino-a-l-ecole/images/image-114.png)
