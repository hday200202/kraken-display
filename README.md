# Kraken Display SFML

A custom Linux daemon that renders CPU temperature and other information onto an NZXT Kraken display using SFML. Designed for headless execution with systemd and virtual OpenGL (via Xvfb), this project offers dynamic rendering, color gradients, and plans for full customization through a future GUI.

---

## Features

- ✅ Renders current CPU temperature to the Kraken screen
- ✅ Uses SFML for high-quality text and graphics
- ✅ Gradient bar visualizes temperature range (orange → red)
- ✅ Runs as a systemd service with clean signal handling
- ✅ `xvfb-run` integration for headless environments
- ✅ Easy deployment script for updating the binary

---

## Requirements

- [SFML 3.0](https://www.sfml-dev.org/download.php)
- `liquidctl` (for communicating with Kraken devices)
- `xorg-server-xvfb` (for virtual OpenGL rendering under systemd)
- C++20 compiler

---

## Development Setup

```bash
sudo pacman -S sfml liquidctl xorg-server-xvfb