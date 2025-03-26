# rtdump-il2cpp-ps4

A runtime il2cpp dumper for Unity games running on the PlayStation4!<br>
Working on any il2cpp version, also the games that give you errors with the classic dumpers.

Ported from: [Zygisk-Il2CppDumper](https://github.com/Perfare/Zygisk-Il2CppDumper)

# Why?
The compiled intermediate language instructions have a bunch of metadata that is required for the games to function.<br>
This data can be dumped and used to generate the equivalent of having debug symbols for the game.<br>
I plan on expanding this project in the future so you can generate the scripts for ida and ghidra on the console itself.

# Requirements
- [make_fself_rust](https://github.com/TheRouletteBoi/make_fself_rust)
- Official PlayStation4 SDK
- Visual Studio 2019 or newer

# Setup
Add an environment variable pointing to a folder containing the built [make_fself_rust](https://github.com/TheRouletteBoi/make_fself_rust) and name it `PS4_DEP`.
### Example Folder Structure
```bash
G:
└── PS4
    └── dep
        └─── self
            └── make_fself.exe
```
# Building
Build the solution with visual studio.<br>
I left a post build event for automatic file transfers via FTP. Simply change the PC name or remove the checks if you want to use it for yourself.

# Usage
Once you have the prx built and fake signed to a sprx, you can use any sprx loader to inject into a Unity game.
The current status is printed to klog and a dump file will be generated in `/data/il2cpp`.
