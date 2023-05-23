# Affichage d'une phrase dans le Serial de l'IDE Arduino

Ce code permet d'afficher une phrase spécifique dans le moniteur série de l'IDE Arduino. La phrase sera transmise depuis l'Arduino et affichée sur le moniteur série de l'ordinateur.

## Matériel requis

- Une carte Arduino
- Un câble USB pour connecter l'Arduino à l'ordinateur

## Fonctionnement

Le programme effectue les étapes suivantes :

1. Connecte l'Arduino à l'ordinateur à l'aide du câble USB.
2. Démarre l'IDE Arduino sur l'ordinateur.
3. Ouvre le moniteur série dans l'IDE Arduino.
4. Configure la vitesse de communication (baud rate) du moniteur série pour correspondre à celle définie dans le programme Arduino.
5. Télécharge le programme sur l'Arduino.
6. L'Arduino envoie la phrase spécifiée dans le programme vers le moniteur série.
7. La phrase s'affiche dans le moniteur série de l'IDE Arduino.

## Configuration et utilisation

1. Connecte l'Arduino à l'ordinateur à l'aide du câble USB.
2. Ouvre l'IDE Arduino sur l'ordinateur.
3. Sélectionne le port série correspondant à l'Arduino dans l'IDE Arduino.
4. Configure la vitesse de communication (baud rate) du moniteur série pour correspondre à celle définie dans le programme Arduino.
5. Télécharge le programme sur l'Arduino.
6. Ouvre le moniteur série dans l'IDE Arduino.
7. Observe l'affichage de la phrase spécifiée dans le programme sur le moniteur série de l'IDE Arduino.

## Remarques

- Assure-toi d'avoir correctement configuré le port série et la vitesse de communication (baud rate) pour établir une connexion entre l'Arduino et l'ordinateur.
- Tu peux personnaliser la phrase à afficher en modifiant le programme Arduino.
- Utilise la fonction `Serial.print()` ou `Serial.println()` dans le programme Arduino pour envoyer des données au moniteur série.

Amuse-toi bien en affichant des phrases dans le moniteur série de l'IDE Arduino !


![image](https://i.ytimg.com/vi/LubYc87S9tQ/maxresdefault.jpg)
