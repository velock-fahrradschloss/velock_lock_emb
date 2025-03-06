# Velock Lock Code  

This repository contains the firmware used to power the Velock Lock System. Please note that this is a **proof-of-concept (POC) project**. If the lock is damaged in any way, the system will continuously send a break signal.  

### Technical Overview  
This project is based on an **Arduino UNO microcontroller** and is programmed using the compatible Arduino framework. Additionally, it utilizes two libraries: **RCSwitch** and **LowPower**, both of which can be installed via the Arduino IDE.  

To improve battery efficiency, the system includes a **sleep functionality**, reducing power consumption when not in use.  

## How Does It Work?  

The system consists of:  
- A **piezo buzzer**  
- A **433MHz transmitter**  
- A **wire integrated into the lock chain**  

If the chain is cut or damaged, the wire will also break, preventing it from sending a **HIGH signal** to the input pin. In this case, the system detects the lock as broken and the **433MHz transmitter** sends a **BREAK signal** to the GPS-LoRaWAN system hidden in the backlight (see repository: `velock_backlight_emb`).  

## Configuration Options  

```cpp
#define LOCKPIN 3  // Pin for the lock wire  
#define ALARM 8  // Pin for the piezo buzzer  
#define TRANSMITTER 10  // Pin for the 433MHz transmitter  
#define BREAK_TOLERANCE_MILLIS 2000  // Threshold for the break signal (LOCKPIN LOW for more than 2 seconds = break signal)  
