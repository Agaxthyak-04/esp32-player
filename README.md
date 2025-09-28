# esp32-player

## Project Overview

This project enables three to four users to listen to songs offline simultaneously using an ESP32 microcontroller with an SD card module. By connecting to a local Wi-Fi network created by the ESP32, users can stream audio tracks stored on the SD card to their devices without requiring an internet connection.

## Features

- **Offline Playback:** Songs are stored on an SD card attached to the ESP32.
- **Multi-User Streaming:** Up to 3-4 users can connect and listen to music concurrently.
- **Wi-Fi Access Point:** ESP32 acts as a Wi-Fi hotspot; users connect via Wi-Fi.
- **Web Interface:** Users access a simple web page to browse and play songs.
- **No Internet Required:** Works entirely offline, ideal for local parties or group listening.

## Hardware Requirements

- ESP32 development board
- Micro SD card module (compatible with ESP32)
- Micro SD card (formatted as FAT32, loaded with audio files)
- Power supply for ESP32 (USB or battery)
- (Optional) Audio output hardware (DAC/I2S module, headphones, or speakers if direct playback is needed)

## Software Requirements

- Arduino IDE or PlatformIO
- ESP32 board support installed
- Required Arduino libraries:
  - `WiFi.h`
  - `ESPAsyncWebServer.h`
  - `SD.h`
  - `FS.h`
  - `Audio.h` (or similar for audio streaming)
- (Optional) Python or web browser for client-side playback

## How It Works

1. **Startup:** ESP32 initializes SD card and creates a Wi-Fi hotspot (e.g., `ESP32_Music`).
2. **Connection:** Users connect their devices (phones, laptops) to the ESP32 Wi-Fi network.
3. **Song Selection:** Users access the ESP32's IP address in a browser to view and select songs.
4. **Streaming:** Selected audio files are streamed from the SD card to each connected client.

## Getting Started

### 1. Hardware Setup

- Connect the SD card module to the ESP32 (refer to ESP32 SD pinout).
- Insert a FAT32-formatted micro SD card with `.mp3` or `.wav` files in the root directory.

### 2. Software Setup

- Clone this repository and open the project in your IDE.
- Configure your SD card and Wi-Fi settings in the code.
- Install the required libraries.
- Upload the code to your ESP32.

### 3. Connect and Play

- Power on the ESP32. It will create a Wi-Fi network (default SSID: `ESP32_Music`).
- Connect your device to this network.
- Open a browser and go to `http://192.168.4.1` (default ESP32 AP IP).
- Browse and select songs to play.

## Limitations & Notes

- Maximum concurrent users may be limited by ESP32 RAM, Wi-Fi bandwidth, and audio streaming method.
- For best results, use compressed audio formats (e.g., 128kbps mp3).
- This is a local streaming solution; it does not broadcast audio over FM/BT.
