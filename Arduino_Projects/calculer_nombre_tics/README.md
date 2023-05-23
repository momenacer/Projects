# Calcul du nombre de tics d'une roue avec moteur

Ce code Arduino permet de compter le nombre de tics (ou impulsions) générés par une roue équipée d'un moteur. Il utilise une interruption matérielle pour détecter chaque tic et incrémente un compteur en conséquence.

## Matériel requis
- Une carte Arduino compatible (par exemple, Arduino Uno)
- Un moteur pour faire tourner la roue qu'il contient un capteur d'impulsion (encodeur, interrupteur magnétique, etc.) pour détecter les tics de la roue
- Connexions appropriées (alimentation, GND, broche de contrôle du moteur, broche de détection des tics, etc.)

## Configuration du code
- Modifiez les constantes `PIN_TIC` et `MOTOR_PIN` pour correspondre aux broches utilisées pour détecter les tics de la roue et contrôler le moteur, respectivement.
- Ajustez les autres paramètres selon vos besoins, tels que la résolution de l'encodeur ou la vitesse du moteur.

## Utilisation du code
1. Téléversez le code sur votre carte Arduino.
2. Assurez-vous que le moteur et le capteur d'impulsion sont correctement connectés.
3. Alimentez votre circuit.
4. Lorsque le moteur tourne, le nombre de tics de la roue sera affiché sur le moniteur série.

![image](https://2.bp.blogspot.com/-j-d-0Q_y6jA/TZEIYhKMUMI/AAAAAAAABm8/LiOUe0BkLb8/s1600/fig10.jpg)
