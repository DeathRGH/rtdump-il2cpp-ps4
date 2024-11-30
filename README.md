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

# Adding Unsupported Versions
If the provided signatures do not work for the game you are working on, follow the steps below to add your game:

Search for the string `il2cpp_init` in ida. It should have exactly one xref.<br>
Follow the xref to the function that uses the string and generate a sig for it.<br>
Example:
`55 48 89 E5 53 48 83 EC ?? ?? ?? ?? ?? ?? ?? ?? BF 30 00 00 00`

## Updating Variables
```cpp
int index_offset;
```
This is the offset between two strings being read in the function.<br>
In this example `0x1FA9F0 - 0x1FA9A8 = 0x48`.<br>
![image](https://github.com/user-attachments/assets/d8bc0b3d-c042-491d-ab21-0456d1d76e7a)

<br>

---

<br>

```cpp
int string_end_offset;
```
This is the offset from the function start to the end of the first instruction reading a string.<br>
You can simply take the address of the instruction after the one reading the string and subtract the function start address.<br>
In this example `0x1FA9AF - 0x1FA980 = 0x2F`.<br>
![image](https://github.com/user-attachments/assets/006dbe88-e908-4648-9937-60031f497124)

<br>

---

<br>

```cpp
int string_function_offset;
```
This is the offset between the instruction after reading the string and the corrosponding function being read as a pointer.<br>
In this example `0x807A3B9A - 0x807A3B78 = 0x22`.<br>
![image](https://github.com/user-attachments/assets/171235e2-be2e-4034-a2e4-cb5f38d27fd0)<br>
If there is no instruction in between, specify 0.<br>
Example:<br>
![image](https://github.com/user-attachments/assets/cba05fc7-5af9-4ab6-8a94-df01dc3fba27)

<br>

---

<br>

```cpp
int string_alloc_size_offset;
```
This is the offset between the instruction after reading a string and the next allocator size instruction.<br>
In this example `0x1FA9DF 0x1FA9AF = 0x30`.<br>
![image](https://github.com/user-attachments/assets/cb874d8e-6b45-4407-9b8b-c8b56b4c2168)


<br>

---

<br>

```cpp
int allocation_size = 0x30;
```
This seems to be a constant for any game I have looked at so far and should not need to be updated.
