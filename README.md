# mempeek

mempeek is a lightweight Python library for Windows that allows you to inspect, scan, and manipulate the memory of running processes.

## installation

To install mempeek, simply use `pip`:

```
$ pip install mempeek
```

## Quick start

```
import mempeek

# Attach to a process
process = mempeek.attach(pid=1234)

# Read memory
bytes_data = proc.read(address=0x7FFDF000, size=64)

# Write memory
proc.write(address=0x7FFDF000, data=b'\x90\x90\x90')

# List memory regions
memory_regions = proc.find_memory_regions()
```

## Motivation

Manipulating memory in external processes is essential for reverse engineering, debugging, and dynamic analysis. While tools like Cheat Engine offer a GUI for this purpose, there is a lack of Pythonic, scriptable alternatives that are both powerful and easy to use.

mempeek bridges this gap by providing a modern, pip-installable Python library (backed by C++ and Windows API) that allows you to attach to a process by PID and read, search, or modify its memory — all from Python scripts. It’s ideal for automation, memory hacking, trainers, or integrating with larger tooling workflows.
