# STATION METEO project with STM32F746G-Discovery
![station-meteo-digital-multicolore-connectee-par-wifi](https://github.com/momenacer/MENACER_Mohamed/assets/127967325/9099632c-9a7c-4cc5-807f-f9c86994c8de)


# Projet de Station Météorologique - Notre projet de Master 1 en Systèmes Embarqués

## Introduction

Ce projet de la Station Météorologique vise à relever le défi important du changement climatique en utilisant un système embarqué. L'impact de l'activité humaine sur le réchauffement climatique est désormais indéniable, et la nécessité de surveiller et de comprendre les modèles météorologiques n'a jamais été aussi cruciale. Ce projet, inspiré du "Weather Shield" de Sparkfun, utilise la carte STM32F746G Discovery pour créer une station météo complète capable de mesurer divers paramètres météorologiques.

## Objectifs de ce Projet

L'objectif principal de ce projet est de concevoir et de mettre en œuvre une station météorologique en utilisant une carte STM32F746G Discovery. Notre station est capable de mesurer les paramètres suivants :

- Humidité
- Température
- Pression atmosphérique
- Direction et vitesse du vent
- Précipitations quotidiennes (pluviométrie)

Les données collectées seront affichées et stockées directement sur la station en utilisant l'écran LCD intégré et le lecteur de carte SD.

## Composants Matériels

Le matériel se présente sous la forme d'un bouclier STM32 qui se connecte au connecteur d'extension STM32. Les capteurs choisis comprennent :

### 1. Température, Humidité et Pression Atmosphérique

Le bouclier ST X-NUCLEO-IKS01A3 avec les capteurs HTS221 et LPS22HH est utilisé. Consultez la documentation technique du bouclier pour les caractéristiques et les méthodes de récupération des données.

### 2. Capteurs de Vitesse et Direction du Vent

En utilisant les "Weather Meters" de Sparkfun, des informations détaillées sur ces capteurs sont disponibles dans la documentation Sparkfun et la documentation Fine Offset fournie. 

### 3. Capteur de Pluie

Le capteur de pluie utilise le principe du "tipping bucket", plus une connexion appropriée via une résistance de tirage (pull-up) à 3,3V pour que les capteurs de vent et de pluie soient fonctionnels.

## Affichage des Données et Interaction

Le projet utilise l'écran LCD de 480x272 pixels de la carte Discovery pour l'affichage des données. L'interaction avec la station comprend des LED RVB pour l'indication de l'état et deux boutons-poussoirs pour l'entrée utilisateur.

## Implémentation Logicielle

Le logiciel STM32 devrait inclure :

- Acquisition des données à partir des capteurs
- Affichage des données sur l'interface graphique
- Stockage des données sur une carte SD en utilisant le middleware FatFS

Des fonctionnalités facultatives pour des points bonus incluent :

- Intégration d'un framework graphique (TouchGFX, StemWin, LVGL, etc.)
- Transmission sans fil des données
- Utilisation des mécanismes de gestion de l'énergie du STM32 pour une consommation minimale

Suggestions :

- Optimisez la fréquence d'affichage des données
- Déclenchez les mesures de vent et de pluie uniquement lorsque cela est pertinent
- Envisagez d'afficher les tendances et les graphiques des données en utilisant les boutons-poussoirs disponibles

## Conclusion

Ce README fournit un aperçu du projet de la Station Météorologique, décrivant ses objectifs, ses composants matériels et son implémentation logicielle. Pour des informations détaillées, veuillez consulter la documentation du projet et le code source.


## Get started
- Clone the project: `https://github.com/momenacer/MENACER_Mohamed/tree/b455dd7db336c4e8d53eeb02eee131fec6853be1/Station%20meteo/stationMeteo_prjt`
- Import into STM32CubeIDE
