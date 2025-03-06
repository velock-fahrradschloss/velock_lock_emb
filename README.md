# Velock Lock Code

This repository contains the firmware that is used to power the Velock-Lock-System. Be aware that this is a POC-Project. This system will fire a break signal forever if the lock is damaged in any kind of way.

This project an Arduino UNO Microcontroller and is therefore programmed with the compatible arduino framework. Also this project uses two libraries (RCSwitch & LowPower), which can be installed via the "Arduino-IDE". This system uses a sleep functionality so the microcontroller will work more battery efficient.

## How does it work?

The system contains a piezzo-buzzer, a 433MHz transmitter and a wire, which is located at the lock-chain itself. If the chain is cut or damaged, the wire will also be damaged and therefore won't send a HIGH state on a INPUT Pin. In that case the lock is considered broken and the 433MHz transmitter will send a BREAK-Signal to the GPS-LoRaWAN-System hidden in the backlight (see repo: velock_backlight_emb).

## Configuration Options

#define LOCKPIN 3 -> Pin for the lock-wire
#define ALARM 8 -> Pin for the piezzo-buzzer
#define TRANSMITTER 10 -> Pin for the 433MHz transmitter
#define BREAK_TOLERANCE_MILLIS 2000 -> Thershhold for the Break-Signal (LOCKPIN more than 2 seconds LOW = Break-Signal)