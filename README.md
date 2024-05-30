# air-watcher

## AirWatcher - Application de surveillance de la qualité de l'air.

Ce projet a été réalisé par [Nadine Saadala](https://github.com/nadine-saadalla), [Noam Catherine](https://github.com/Mushahime), [Polo Diemunsch](https://github.com/polo-diemunsch) et [Rafael Sagués](https://github.com/sagueso) dans le cadre du cours "Software Engineering & UML" du Département Informatique de l'INSA Lyon.

### Scénario

AirWatcher est une application développée pour une agence gouvernementale chargée de surveiller la qualité de l'air sur un vaste territoire. L'application permet d'analyser les données générées par des capteurs répartis sur le territoire afin de détecter les capteurs défectueux et d'agréger les informations pour produire des statistiques sur la qualité de l'air. De plus, AirWatcher permet de comparer les capteurs entre eux pour identifier les zones présentant des similitudes en termes de qualité de l'air.

### Compilation

La compilation du projet se fait à l'aide de la commande `make` et il suffira de lancer l'executable obtenu pour tester l'application (`./bin/air-watcher`).

N.B : Utilisez `make unit-tests` pour compiler les tests unitaires.

### Utilisation

L'application AirWatcher est basée sur une interface console. Les différentes fonctionnalités sont accessibles via cette interface.

Voici les principales fonctionnalités de l'application :

- Analyse des données des capteurs pour détecter les capteurs défectueux.

- Agrégation des données pour produire des statistiques sur la qualité de l'air.

- Comparaison des capteurs pour identifier les zones avec des similitudes en termes de qualité de l'air.

- Calcul d'une mesure de qualité de l'air à une position géographique précise.

- Analyse des données fournies par les capteurs des particuliers pour déterminer leur fiabilité.
