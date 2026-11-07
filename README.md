# SMART VEST — Intelligent Wearable System for Football Players

**ESPRIT — École Supérieure Privée d'Ingénierie et de Technologies**

**Étudiant :** Firas Khlifi  
**Enseignant :** M. Anis Kammoun  
**Matière :** Communication sans fil et 5G  
**Année universitaire :** 2026–2027

---

## 1. Présentation du projet

SMART VEST est un projet de gilet intelligent destiné à la surveillance de paramètres physiologiques et à la détection d'anomalies chez les joueurs de football.

Le projet comprend une simulation IoT fonctionnelle sous Wokwi et une proposition d'architecture avancée intégrant des capteurs textiles et des techniques de traitement intelligent.

## 2. Objectifs

- Simuler la surveillance de la fréquence cardiaque et de la température ambiante.
- Détecter les dépassements de seuils.
- Déclencher des alertes locales par LED et buzzer.
- Transmettre les mesures via Wi-Fi et MQTT.
- Concevoir une architecture de gilet intelligent intégrant ECG textile, respiration, IMU et TinyML.
- Étudier l'autonomie énergétique, la communication radio et l'intégration textile.

## 3. Architecture fonctionnelle

```text
Capteurs simulés
DHT22 + Potentiomètre
         |
         v
       ESP32
         |
    Traitement
         |
    +----+----+
    |         |
    v         v
LED/Buzzer  Wi-Fi/MQTT
              |
              v
        Broker HiveMQ
              |
              v
       Client Web MQTT
```

**Architecture avancée proposée :**

Électrodes ECG textiles + capteur respiratoire + IMU → acquisition analogique et numérique → filtrage adaptatif → analyse Edge AI / TinyML → ESP32 → alertes et communication IoT.

## 4. Matériel simulé

| Composant | Fonction |
|---|---|
| ESP32 | Microcontrôleur principal |
| DHT22 | Température ambiante simulée |
| Potentiomètre | Simulation de la fréquence cardiaque |
| LED verte | État normal |
| LED rouge | État d'alerte |
| Buzzer | Signal sonore |

## 5. Logiciels et technologies

- Wokwi
- Arduino / ESP32
- C++
- Wi-Fi
- MQTT
- HiveMQ Public Broker
- GitHub

## 6. Fonctionnement

Le système lit périodiquement les données des capteurs simulés.

Une alerte est déclenchée lorsque :

- BPM simulé supérieur à 140.
- Température ambiante inférieure à 10 °C ou supérieure à 35 °C.

En cas d'alerte, la LED rouge s'allume et le buzzer émet un signal. En fonctionnement normal, la LED verte est allumée.

Les données sont publiées sur le broker MQTT public `broker.hivemq.com`, port `1883`, sur le topic :

`demo/smartvest/engineering2026/telemetry`

## 7. Résultats expérimentaux

**Scénario d'alerte :**

- BPM simulé : 180
- Température ambiante : 62,2 °C
- Alerte : `true`
- Réception MQTT : validée sur HiveMQ

**Scénario normal :**

- BPM simulé : 115
- Température ambiante : 24,8 °C
- Alerte : `false`
- LED verte : allumée
- Publication MQTT : validée dans Wokwi

## 8. Innovation proposée : filtrage adaptatif et TinyML

L'innovation étudiée concerne l'amélioration de la fiabilité des mesures physiologiques pendant l'activité sportive.

Le système cible prévoit un filtrage adaptatif des signaux ECG à l'aide des informations de mouvement fournies par une IMU, puis une analyse locale par un modèle TinyML.

Cette architecture reste une proposition de conception et n'est pas implémentée dans la simulation Wokwi actuelle.

## 9. Limites

Le potentiomètre ne mesure pas une fréquence cardiaque réelle. Le DHT22 fournit une température ambiante simulée et non une mesure de température corporelle.

Les électrodes textiles, l'IMU, l'antenne textile et TinyML relèvent de l'étude d'ingénierie.

Le projet n'est pas un dispositif médical certifié.

## 10. Organisation du dépôt

```text
smart-vest-wearable-technology/
├── README.md
├── sketch.ino
├── diagram.json
├── libraries.txt
└── captures/
    ├── Annexe_A02_Compilation_Publication_MQTT.png
    ├── Annexe_A04_Reception_MQTT_SmartVest.png
    └── Annexe_A05_Etat_Normal_SmartVest.png
```

## 11. Exécution

1. Ouvrir le projet dans Wokwi.
2. Charger `sketch.ino`, `diagram.json` et `libraries.txt`.
3. Démarrer la simulation.
4. Observer les données dans le Serial Monitor.
5. Se connecter au broker HiveMQ avec un client MQTT compatible.
6. S'abonner au topic indiqué.
7. Modifier le potentiomètre et la température DHT22 pour tester les alertes.

---

**Projet académique — ESPRIT — 2026–2027**
