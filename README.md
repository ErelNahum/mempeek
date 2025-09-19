# mempeek

![mempeek_banner](/static/cover.png)

⚡ *Lightweight Python library for inspecting, scanning, and manipulating memory of running Windows processes.*

[![Python](https://img.shields.io/badge/python-3.9%2B-blue?logo=python&logoColor=white)](https://www.python.org/)
[![Platform](https://img.shields.io/badge/platform-windows-blue?logo=windows)](https://www.microsoft.com/windows)

[//]: # ([![License]&#40;https://img.shields.io/badge/license-MIT-green?style=flat-square&#41;]&#40;LICENSE&#41;)

[//]: # ([![PyPI]&#40;https://img.shields.io/pypi/v/mempeek?color=brightgreen&logo=pypi&#41;]&#40;https://pypi.org/project/mempeek/&#41;)


## 📦 installation

To install mempeek, simply use `pip`:

```bash
$ pip install mempeek
```

## 🚀 Quick start

```python
import mempeek

# Attach to a process
process = mempeek.attach(pid=1234)

# Read memory
bytes_data = proc.read(address=0x7FFDF000, size=64)

# Write memory
proc.write(address=0x7FFDF000, data=b'\x90\x90\x90')

# List memory regions
memory_regions = proc.find_memory_regions()

# Find all occurencess of a byte pattern
addresses = proc.search_bytes(pattern=b'MZ')
```

## 🎯 Motivation

Manipulating memory in external processes is essential for reverse engineering, debugging, and dynamic analysis. While tools like Cheat Engine offer a GUI for this purpose, there is a lack of Pythonic, scriptable alternatives that are both powerful and easy to use.

mempeek bridges this gap by providing a modern, pip-installable Python library (backed by C++ and Windows API) that allows you to attach to a process by PID and read, search, or modify its memory — all from Python scripts. It’s ideal for automation, memory hacking, trainers, or integrating with larger tooling workflows.
