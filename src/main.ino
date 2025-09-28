#include <WiFi.h>
#include <SD.h>
#include <SPI.h>
#include <ESPAsyncWebServer.h>
#include <Update.h>

const char* ssid = "WiFi_name ";
const char* password = "password";

#define SD_CS 5  // Chip select pin for SD card module

AsyncWebServer server(80);

// Handle 404 errors
void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "404 Not Found");
}

// Determine correct content type
String getContentType(String filename) {
  if (filename.endsWith(".html")) return "text/html";
  if (filename.endsWith(".css")) return "text/css";
  if (filename.endsWith(".js")) return "application/javascript";
  if (filename.endsWith(".jpg") || filename.endsWith(".jpeg")) return "image/jpeg";
  if (filename.endsWith(".png")) return "image/png";
  if (filename.endsWith(".gif")) return "image/gif";
  if (filename.endsWith(".mp3")) return "audio/mpeg";
  return "text/plain";
}

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");
  Serial.println("IP Address: " + WiFi.localIP().toString());

  // Mount SD card
  if (!SD.begin(SD_CS)) {
    Serial.println("SD Card mount failed!");
    return;
  }

  // Ensure /music directory exists
  if (!SD.exists("/music")) {
    SD.mkdir("/music");
  }

  // Serve index.html at root
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SD, "/index.html", "text/html");
  });

  // List MP3 files in /music directory
  server.on("/list-mp3s", HTTP_GET, [](AsyncWebServerRequest *request){
    File dir = SD.open("/music");
    String json = "[";
    while (true) {
      File entry = dir.openNextFile();
      if (!entry) break;
      if (!entry.isDirectory() && String(entry.name()).endsWith(".mp3")) {
        json += "\"" + String(entry.name()) + "\",";
      }
      entry.close();
    }
    if (json.endsWith(",")) json.remove(json.length() - 1);
    json += "]";
    request->send(200, "application/json", json);
  });

  // File upload to /music folder
  server.on("/upload", HTTP_POST, [](AsyncWebServerRequest *request) {
    request->send(200);
  },[](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final) {
    static File uploadFile;

    if (index == 0) {
      String path = "/music/" + filename;
      uploadFile = SD.open(path, FILE_WRITE);
    }

    if (uploadFile) uploadFile.write(data, len);

    if (final && uploadFile) {
      uploadFile.close();
    }
  });

  // Serve static files from SD card
  server.serveStatic("/", SD, "/").setDefaultFile("index.html");

  // CORS headers (optional)
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");

  // 404 fallback
  server.onNotFound(notFound);

  // Start web server
  server.begin();
}

void loop() {
  // Nothing needed in loop
}
