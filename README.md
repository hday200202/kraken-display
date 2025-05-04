# Kraken Display

A Linux tool that renders real-time system information (like CPU temperature) to the screen of an 2023 NZXT Kraken cooler using SFML. Built for use in headless environments and designed to run as a background service, this project provides a customizable and visually rich alternative to Windows-only software.

---

## Features

- Displays CPU temperature with smooth text and graphical indicators
- Animated gradient bar that visually represents system heat
- Intended to run as a systemd service or lightweight background app

---

## Requirements

- [SFML 3.0](https://www.sfml-dev.org/download.php)
- `liquidctl` (for Kraken LCD communication)

---

## Building

Clone the repo and build the binary:

```bash
git clone https://github.com/hday200202/kraken-display.git
cd kraken-display-sfml
make
