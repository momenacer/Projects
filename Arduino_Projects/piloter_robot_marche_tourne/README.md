# Pilotage autonome d'un robot avec Arduino et deux roues

Ce code consiste à réaliser un système qui permet de piloter un robot de manière autonome en utilisant un microcontrôleur Arduino et deux roues motorisées. Le robot sera capable d'avancer, reculer, tourner à gauche et tourner à droite de manière autonome, sans intervention humaine.

## Matériel requis

- Un robot avec deux roues motorisées
- Un microcontrôleur Arduino
- Un module de pilotage des moteurs (par exemple, un pont en H)

## Fonctionnement

Le programme effectue les étapes suivantes :

1. Initialise les broches du microcontrôleur pour contrôler les moteurs et, le cas échéant, les capteurs.
2. Démarre une boucle infinie.
3. Lit les capteurs (si disponibles) pour obtenir des informations sur l'environnement du robot.
4. Utilise les informations des capteurs (le cas échéant) pour prendre des décisions concernant les mouvements du robot.
5. Envoie des signaux de commande aux moteurs pour faire avancer, reculer, tourner à gauche ou tourner à droite le robot en fonction des décisions prises.
6. Répète les étapes 3 à 5 en boucle pour permettre au robot de se déplacer de manière autonome.

## Configuration et utilisation

1. Connectez le module de pilotage des moteurs au microcontrôleur Arduino en utilisant les broches appropriées.
2. Connectez les roues motorisées au module de pilotage des moteurs.
3. Si vous utilisez des capteurs, connectez-les aux broches appropriées du microcontrôleur.
4. Téléchargez le programme sur le microcontrôleur.
5. Alimentez le microcontrôleur et le robot.
6. Le robot sera désormais capable de se déplacer de manière autonome.

## Remarques

- Vous pouvez personnaliser ce projet en ajoutant des fonctionnalités supplémentaires, telles que la détection d'obstacles, le suivi de ligne, la communication sans fil pour contrôler le robot à distance, etc.
- Assurez-vous de respecter les spécifications du microcontrôleur, du module de pilotage des moteurs et des capteurs utilisés.
- Soyez prudent lors de l'exécution du robot pour éviter tout dommage ou blessure potentielle.

N'hésitez pas à expérimenter et à ajouter votre touche personnelle à ce projet. Amusez-vous bien en pilotant votre robot de manière autonome avec Arduino et deux roues !


![image](https://ledisrupteurdimensionnel.com/wp-content/uploads/2022/06/07-colocar-sensor-ultrasonido.jpg)
