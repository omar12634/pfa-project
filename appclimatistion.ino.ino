#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

// **Définition des broches et type de capteur**
#define DHTPIN 18      // Broche où est connecté le capteur DHT22
#define DHTTYPE DHT22 // Type de capteur DHT (DHT11 ou DHT22)

// **Initialisation du capteur**
DHT dht(DHTPIN, DHTTYPE);

// **Informations WiFi**
const char* ssid = "Fibre";         // Remplacez par votre WiFi
const char* password = "Achrafomar"; // Remplacez par votre mot de passe

// **API de ThingSpeak**
String thingSpeakAPI = "https://api.thingspeak.com/update";
String apiKey = "FCIZ8SOT51INN97C"; // Remplacez par votre clé API

void setup() {
    Serial.begin(115200);
    dht.begin(); // Démarrage du capteur DHT

    // **Connexion au WiFi**
    WiFi.begin(ssid, password);
    Serial.print("Connexion au WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println(" Connecté!");
}

void loop() {
    // Vérifier la connexion WiFi
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;

        // **Lecture des valeurs du capteur**
        float temperature = dht.readTemperature(); // Lire la température en °C
        float humidite = dht.readHumidity();       // Lire l'humidité en %

        // Vérifier si les lectures sont valides
        if (!isnan(temperature) && !isnan(humidite)) {
            Serial.print("🌡️ Température : "); Serial.print(temperature); Serial.print(" °C  |  ");
            Serial.print("💧 Humidité : "); Serial.print(humidite); Serial.println(" %");

            // **Construction de l'URL pour envoyer les données**
            String url = thingSpeakAPI + "?api_key=" + apiKey + "&field1=" + String(temperature) + "&field2=" + String(humidite);

            // **Envoi des données**
            http.begin(url);
            int httpCode = http.GET();  // Exécuter la requête HTTP GET
            
            if (httpCode > 0) {
                Serial.println("✅ Données envoyées avec succès !");
            } else {
                Serial.println("❌ Erreur d'envoi !");
            }
            
            http.end(); // Fermer la connexion HTTP
        } else {
            Serial.println("❌ Erreur de lecture du capteur !");
        }
    } else {
        Serial.println("❌ WiFi non connecté !");
    }

    delay(15000); // Envoyer toutes les 15 secondes
}
