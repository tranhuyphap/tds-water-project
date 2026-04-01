# TDS Water Quality Monitor

A low-cost, in-situ water quality sensor built with Arduino Nano 
that measures Total Dissolved Solids (TDS) and temperature simultaneously.

Built as a school science research project (NCKH) to investigate 
real water quality in Ho Chi Minh City households — specifically 
whether home RO filters are actually working as expected.

![TDS Monitor Device] images/Finished Product.png

---

## Why This Matters

Vietnam's QCVN 01-1:2024/BYT standard sets the safe drinking water 
limit at 1000 ppm TDS. Many households in Ho Chi Minh City rely on 
RO (Reverse Osmosis) filters, assuming they significantly reduce 
dissolved solids. However, RO filter cartridges degrade over time 
and lose effectiveness — often without any visible sign.

This device gives any household a real-time, low-cost way to verify 
whether their filter is actually working, using a $12 hardware setup.

---

## What It Does

- Measures TDS (ppm) and water temperature (°C) simultaneously
- Averages 10 analog readings per cycle to reduce sensor noise
- Applies ISO 7888 temperature compensation to normalize all 
  readings to 25°C for accurate cross-sample comparison
- Compares results against Vietnam QCVN 01-1:2024/BYT drinking 
  water standard in real time
- Displays all results on OLED screen, updated every second
- Reports one of four status conditions:
  - ✅ DAT QCVN — TDS and temperature both within standard
  - ⚠️ VUOT QCVN: TDS CAO — TDS exceeds 1000 ppm limit
  - ⚠️ NUOC NONG (TDS OK) — Water too warm, TDS acceptable
  - ❌ VUOT QCVN: TDS+NHIET — Both parameters out of range

---

## Hardware Components

| Component | Purpose | Approx. Cost |
|-----------|---------|--------------|
| Arduino Nano (CH340) | Microcontroller | ~80,000 VND |
| TDS Meter Module V1.0 | Measures dissolved solids | ~60,000 VND |
| DS18B20 waterproof sensor | Measures water temperature | ~35,000 VND |
| SSD1306 0.96" OLED display | Shows real-time readings | ~40,000 VND |
| Jumper wires + breadboard | Connections | ~30,000 VND |
| **Total** | | **~290,000 VND (~$12 USD)** |

---

## Key Findings

We tested 5 water sources across Ho Chi Minh City in March 2026. 
Full results: [results.md](results.md)

The most significant finding: our home RO filter measured **105 ppm** — 
nearly identical to the unfiltered tap water at **103 ppm**. This suggests 
the filter cartridge had degraded and was no longer removing dissolved 
solids effectively, despite appearing physically normal.

Temperature compensation proved critical: the saltwater sample 
read **1081 ppm** raw, but corrected to **983 ppm** after ISO 7888 
compensation at 25°C — a difference of 98 ppm that would affect 
any cross-sample comparison done without compensation.

---

## How to Replicate

1. Wire components according to pin definitions in `tds_monitor.ino`:
   - DS18B20 data pin → Arduino D4
   - TDS module signal pin → Arduino A1
   - OLED SDA → A4, SCL → A5
2. Install required libraries via Arduino IDE Library Manager:
   `Adafruit_SSD1306`, `Adafruit_GFX`, `DallasTemperature`, `OneWire`
3. Upload `tds_monitor.ino` to Arduino Nano
4. Open Serial Monitor at 9600 baud to see readings alongside OLED

---

## What I Learned

Building this device taught me that engineering is as much about 
measurement accuracy as it is about hardware assembly. The temperature 
compensation step (ISO 7888) was the hardest part to get right — 
without it, every reading at a different temperature is essentially 
incomparable. I also learned that real-world sensor data is noisy, 
which is why averaging 10 readings per cycle matters more than it 
might seem in theory.

The finding about the RO filter was unexpected and genuinely useful — 
it changed a real decision in our household.

---

## Built By

Tran Huy Phap & Nguyen Vo Anh Minh  
Grade 11 · THPT Nguyen Thuong Hien · Ho Chi Minh City, Vietnam  
March 2026
