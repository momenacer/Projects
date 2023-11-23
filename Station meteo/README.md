# LVGL ported to the STM32F769 Discovery
<img src="https://i.ytimg.com/vi/ZUJxbCbBod0/maxresdefault.jpg">

# Projet de Station Météorologique - Projet de Master en Systèmes Embarqués

## Introduction

Le projet de la Station Météorologique vise à relever le défi important du changement climatique en utilisant un système embarqué. L'impact de l'activité humaine sur le réchauffement climatique est désormais indéniable, et la nécessité de surveiller et de comprendre les modèles météorologiques n'a jamais été aussi cruciale. Ce projet, inspiré du "Weather Shield" de Sparkfun, utilise la carte STM32F746G Discovery pour créer une station météo complète capable de mesurer divers paramètres météorologiques.

## Objectifs du Projet

L'objectif principal de ce projet est de concevoir et de mettre en œuvre une station météorologique en utilisant une carte STM32F746G Discovery. La station devrait être capable de mesurer les paramètres suivants :

- Humidité
- Température
- Pression atmosphérique
- Direction et vitesse du vent
- Précipitations quotidiennes (pluviométrie)

Les données collectées seront affichées et stockées directement sur la station en utilisant l'écran LCD intégré et le lecteur de carte SD. De plus, les données peuvent être transmises sans fil à un appareil distant tel qu'un smartphone ou un Raspberry Pi.

## Composants Matériels

Le matériel se présente sous la forme d'un bouclier Arduino qui se connecte au connecteur d'extension STM32. Les capteurs choisis comprennent :

### 1. Température, Humidité et Pression Atmosphérique

Le bouclier ST X-NUCLEO-IKS01A3 avec les capteurs HTS221 et LPS22HH est utilisé. Consultez la documentation technique du bouclier pour les caractéristiques et les méthodes de récupération des données.

### 2. Capteurs de Vitesse et Direction du Vent

En utilisant les "Weather Meters" de Sparkfun, des informations détaillées sur ces capteurs sont disponibles dans la documentation Sparkfun et la documentation Fine Offset fournie. Expliquez les principes de fonctionnement, y compris les principes physiques utilisés pour convertir la vitesse et la direction du vent en un format numérique utilisable par le STM32.

### 3. Capteur de Pluie

Le capteur de pluie utilise le principe du "tipping bucket". Recherchez et expliquez ce principe, y compris la manière dont le STM32 récupère les informations de précipitations. Assurez une connexion appropriée via une résistance de tirage (pull-up) à 3,3V pour que les capteurs de vent et de pluie soient fonctionnels.

## Affichage des Données et Interaction

Le projet utilise l'écran LCD de 480x272 pixels de la carte Discovery pour l'affichage des données. L'interaction avec la station comprend des LED RVB pour l'indication de l'état et deux boutons-poussoirs pour l'entrée utilisateur.

## Solution de Communication Radio

Explorez des solutions de communication à faible consommation compatibles avec le STM32 pour la transmission sans fil des données.

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
- Clone the project: `git clone https://github.com/lvgl/lv_port_stm32f769_disco.git --recurse-submodules`
- Import into STM32CubeIDE
