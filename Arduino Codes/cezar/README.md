# Cryptage et décryptage César

Ce code consiste en la réalisation d'un système de cryptage et de décryptage à l'aide d'un poussoir et de trois LEDs (verte, jaune et rouge), en s'inspirant du code de César utilisé à l'époque romaine pour transmettre des informations secrètes.

## Fonctionnement

Le système comporte trois états, qui sont cycliquement activés à chaque pression sur le bouton :

### État 1 - LED Jaune allumée
Dans cet état, seule la LED Jaune est allumée. La phrase entrée dans le terminal est simplement recopiée à l'identique dans le terminal. Cela signifie que le texte est affiché en clair, sans subir de cryptage.

### État 2 - LED Rouge allumée
Dans cet état, seule la LED Rouge est allumée. La phrase entrée dans le terminal est recopiée dans le terminal, mais cette fois-ci sous forme cryptée selon la méthode du code de César. Chaque lettre du message est décalée d'un certain nombre fixe de positions dans l'alphabet. Lorsqu'on atteint la fin de l'alphabet, le décalage continue avec les lettres du début.

### État 3 - LED Verte allumée
Dans cet état, seule la LED Verte est allumée. La phrase cryptée entrée dans le terminal est recopiée dans le terminal sous forme décryptée. Le processus inverse du cryptage est effectué : chaque lettre du message est décalée en sens inverse du décalage précédemment appliqué, permettant ainsi de retrouver le message original.

## Utilisation

1. Assurez-vous que le matériel nécessaire (bouton, LEDs) est correctement connecté à votre système.
2. Compilez et exécutez le programme sur votre terminal.
3. Appuyez sur le bouton pour changer d'état à chaque pression :
   - État 1 : LED Jaune allumée - affichage du texte en clair.
   - État 2 : LED Rouge allumée - affichage du texte crypté.
   - État 3 : LED Verte allumée - affichage du texte décrypté.
4. Répétez l'étape précédente pour alterner entre les différents états et observer les résultats.

## Remarques

- Assurez-vous d'avoir correctement configuré et initialisé votre environnement pour pouvoir utiliser les bibliothèques nécessaires et interagir avec le matériel.
- La méthode de cryptage utilisée ici est simple et basée sur le code de César. Dans des cas réels, il est recommandé d'utiliser des algorithmes de cryptage plus robustes et sécurisés pour protéger les informations sensibles.

N'hésitez pas à apporter des modifications ou à ajouter des fonctionnalités à ce projet en fonction de vos besoins spécifiques. Amusez-vous bien !





![image](https://www.robot-maker.com/ouvrages/wp-content/uploads/2016/10/feusigna_bb.png)
