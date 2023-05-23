# Affichage de la valeur de sortie analogique d'Arduino sur un oscilloscope

Ce code permet d'afficher la valeur de sortie analogique d'Arduino sur un oscilloscope. La valeur analogique est convertie en signal de tension qui peut être visualisé sur l'oscilloscope.

## Matériel requis

- Une carte Arduino
- Un câble de connexion entre l'Arduino et l'oscilloscope

## Fonctionnement

Le programme effectue les étapes suivantes :

1. Connecte une broche de sortie analogique de l'Arduino (par exemple, A0) à l'entrée de l'oscilloscope à l'aide d'un câble de connexion.
2. Démarre une boucle infinie.
3. Lit la valeur de sortie analogique de l'Arduino à l'aide de la fonction `analogRead()`.
4. Convertit la valeur lue en signal de tension en utilisant la formule appropriée, en fonction de la résolution de l'Arduino (10 bits pour la plupart des modèles).
   - Par exemple, si l'Arduino a une résolution de 10 bits et une tension de référence de 5V, la formule est : `voltage = (valeur_lue * 5.0) / 1023.0`.
5. Envoie le signal de tension à l'entrée de l'oscilloscope.
6. Répète les étapes 3 à 5 en boucle pour mettre à jour en temps réel la valeur affichée sur l'oscilloscope.

## Configuration et utilisation

1. Connecte une broche de sortie analogique de l'Arduino à l'entrée de l'oscilloscope à l'aide d'un câble de connexion.
2. Télécharge le programme sur l'Arduino.
3. Alimente l'Arduino.
4. Configure l'oscilloscope pour afficher le signal reçu de l'Arduino.
5. Observe l'affichage de la valeur de sortie analogique d'Arduino en temps réel sur l'oscilloscope.

## Remarques

- Assure-toi de configurer correctement l'oscilloscope pour afficher le signal analogique reçu de l'Arduino.
- Selon les spécifications de ton Arduino, ajuste la formule de conversion de la valeur lue en signal de tension en conséquence.
- Expérimente avec différentes valeurs d'entrée analogique sur l'Arduino pour observer les variations sur l'oscilloscope.

Profite de l'affichage de la valeur de sortie analogique d'Arduino sur l'oscilloscope !



![image](https://davidtribal.com/blog/wp-content/uploads/2013/11/discretisation.jpg)
