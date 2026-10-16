# SignalShark — My Build Journey

SignalShark is my ongoing project for exploring wireless signals and tracking aircraft and satellites. I’m building it step by step while learning C++, Python, electronics, and working with APIs.

This README documents how I started, what works today, and what I want to build next.

## How it started

I started with an ESP32-S3 and two nRF24L01+ PA/LNA modules. My first idea was to build an ADS-B aircraft tracker.

While researching the hardware, I learned that the nRF24L01 operates on 2.4 GHz and cannot receive the 1090 MHz ADS-B signals used by aircraft in Europe. I changed my approach: use the ESP32 for local wireless measurements and retrieve aircraft positions from the internet on my laptop.

## Getting the ESP32 working

I set up Arduino IDE and uploaded a small program that printed a message every two seconds. Getting serial output working took some troubleshooting: the board has two USB connections, and the USB CDC setting needs to match the connection being used.

Once my message appeared in the Serial Monitor, I had a working starting point.

### My ESP32-S3 board

![ESP32-S3 development board, front and back](images/esp32.jpg)

### Learning the pins

I started learning how to read GPIO labels and distinguish data pins from power connections.

![ESP32-S3 pin diagram reference](images/pinchema.png)

This image is a reference, not a completed wiring plan for the project.

## Learning the programming basics

Before building the scanner, I practised printing text, creating a counter, comparing values with `if` and `else`, and repeating actions with loops. Later, I learned to create functions and return values.

I wanted to understand each change rather than just copy a complete program.

## Building the Wi-Fi scanner

I used the ESP32’s built-in Wi-Fi to scan nearby networks. At first, I displayed only the number of networks found. I gradually added:

- Network names and Wi-Fi channels.
- Signal strength in dBm.
- Strong, moderate, and weak signal labels.
- Numbered results and scan duration.

I learned that −40 dBm is stronger than −80 dBm, and that a channel identifies where a network operates in the frequency band. I moved the signal rating into its own function to make the scanning code easier to read.

## Adding a serial menu

Instead of scanning continuously, I added commands through the Serial Monitor:

| Command | Action |
| --- | --- |
| `w` or `W` | Start a Wi-Fi scan |
| `m` or `M` | Display the menu |
| `h` or `H` | Display help |

I added a message for unknown commands and learned to ignore the line-ending characters sent when pressing Enter. A formatting problem also taught me why `print()` keeps output on the same line while `println()` starts a new one.

The scanner is currently controlled from my laptop over USB.

## Planning the radio hardware

I explored adding an nRF24L01 module to monitor activity in the 2.4 GHz band. This part is not connected yet: I still need to confirm the unlabelled module’s pinout and arrange a suitable 3.3 V supply before wiring it.

I also looked into jumper wires, female headers, and a prototyping board. The planned activity monitor will detect activity above a threshold; it will not identify devices or provide calibrated signal-strength measurements.

## Starting the aircraft tracker

While the radio hardware was on hold, I started a separate Python program on my laptop. I created a virtual environment and began with a simple terminal message.

Next, I used `urllib.request` to request internet data and `json` to read the responses. I added an IP-location lookup, followed by a request to ADSB.lol for aircraft around a chosen location.

### Learning about IP location

The location service reported Haarlemmermeer while I was in Amsterdam. That showed me that IP location is only an estimate.

For now, the search uses an approximate, manually configured point near Slotermeer with a radius of 25 nautical miles. Automatic location selection with a manual correction option is still planned.

## Displaying aircraft

The first successful request returned a count of nearby aircraft. I added a loop to display each callsign. When only one callsign appeared, I learned that Python indentation determines whether a statement runs inside or outside a loop.

After fixing that, I added aircraft type codes, aligned the columns, and created an ASCII aircraft banner for the terminal.

### Current terminal output

![SignalShark aircraft tracker running in the terminal](images/process.png)

This screenshot shows one snapshot of the returned data. Counts and available information change between requests. Some returned records may represent ground vehicles rather than airborne aircraft; filtering those records is a future improvement.

## Where I am now

I have two working parts:

- **ESP32 Wi-Fi scanner:** displays nearby 2.4 GHz networks, channels, signal strengths, and signal ratings through a USB serial menu.
- **Python aircraft viewer:** fetches records around a configured location and displays their count, callsigns, and aircraft type codes when available.

These programs still run separately. The aircraft viewer uses internet data; it does not receive aircraft transmissions through the ESP32 or nRF24.

Departure and destination information, satellite tracking, and a combined graphical interface are not implemented yet.

## What I want to build next

- Show aircraft altitude, speed, and distance.
- Look up departure and destination airports where free data permits.
- Improve error handling for failed internet requests.
- Add ISS and satellite information.
- Confirm the nRF24 wiring and build the radio activity monitor.
- Bring the features together in a laptop interface.
- Explore an optional touchscreen after the main features work.

## Data sources

- [ADSB.lol](https://www.adsb.lol/docs/open-data/api/) — aircraft data, published under ODbL 1.0.
- [IPWhois](https://ipwhois.io/documentation) — approximate IP-based location.

**Status: actively learning and building.**
