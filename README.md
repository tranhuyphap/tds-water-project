# TDS Water Quality Monitor

An in-situ TDS (Total Dissolved Solids) and temperature sensor
built with Arduino Nano for testing household water quality.

## What it does
- Measures TDS (ppm) and temperature (°C) simultaneously
- Applies ISO 7888 temperature compensation
- Compares results against Vietnam QCVN 01-1:2024/BYT standard
- Displays results on OLED screen in real-time

## Hardware
- Arduino Nano (CH340)
- TDS Meter Module V1.0
- DS18B20 waterproof temperature sensor
- SSD1306 0.96" OLED display
- Total cost: ~290,000 VND (~$12 USD)

## Results
Tested 5 water sources in Ho Chi Minh City.
Found home RO filter TDS (105 ppm) nearly equal to tap water (103 ppm),
indicating filter effectiveness had degraded.

## Built by
Tran Huy Phap & Nguyen Vo Anh Minh — Grade 11, THPT Nguyen Thuong Hien
