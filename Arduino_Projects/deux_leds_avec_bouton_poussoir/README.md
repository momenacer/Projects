# Commutation entre deux LEDs à l'aide d'un bouton poussoir

Ce code consiste à réaliser un programme qui permet de commuter l'allumage de deux LEDs à l'aide d'un bouton poussoir. Chaque fois que le bouton poussoir est enfoncé, l'état des LEDs est inversé, c'est-à-dire que si une LED est allumée, elle s'éteint, et si une LED est éteinte, elle s'allume.

## Matériel requis

- Deux LEDs
- Deux résistances appropriées pour les LEDs
- Un bouton poussoir
- Un microcontrôleur compatible avec la programmation des LEDs et la lecture de l'état du bouton poussoir (par exemple, Arduino)

## Fonctionnement

Le programme effectue les étapes suivantes :

1. Initialise les broches du microcontrôleur pour contrôler les LEDs et lire l'état du bouton poussoir.
2. Démarre une boucle infinie.
3. Lit l'état du bouton poussoir pour déterminer si celui-ci est enfoncé.
4. Si le bouton poussoir est enfoncé, inverse l'état des LEDs. Si une LED est allumée, elle s'éteint, et si une LED est éteinte, elle s'allume.
5. Répète les étapes 3 et 4 en boucle pour permettre la commutation continue entre les deux LEDs à chaque pression du bouton poussoir.

## Configuration et utilisation

1. Assurez-vous que les LEDs sont correctement connectées aux broches du microcontrôleur et que les résistances appropriées sont utilisées pour limiter le courant.
2. Connectez le bouton poussoir à une broche d'entrée du microcontrôleur.
3. Téléchargez le programme sur le microcontrôleur.
4. Alimentez le microcontrôleur.
5. Appuyez sur le bouton poussoir pour commuter l'allumage des LEDs.

## Remarques

- Vous pouvez personnaliser ce projet en utilisant des LEDs de différentes couleurs ou en ajoutant des fonctionnalités supplémentaires, telles que l'utilisation de temporisations pour éviter les rebonds du bouton poussoir.
- Assurez-vous de respecter les spécifications de votre microcontrôleur en termes de tension, de courant et de broches utilisées pour contrôler les LEDs et lire l'état du bouton poussoir.

N'hésitez pas à expérimenter et à ajouter votre touche personnelle à ce projet. Amusez-vous bien !



![image](https://i.ytimg.com/vi/nWwtNNZKxeI/maxresdefault.jpg)
