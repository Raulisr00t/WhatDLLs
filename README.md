# WhatDLLs

WhatDLLs is a simple command-line tool designed to enumerate the loaded DLLs for a specific process on a Windows system. It allows you to list all modules (DLLs) loaded by a running process by providing its name.

## Features
1.Enumerates loaded DLLs for a given process ID (PID).
2.Uses the CreateToolhelp32Snapshot API to get module information.
3.Displays the address and name of each loaded module.
    
## Usage
```powershell
whatdlls.exe <process_name>
```

### Example

```powershell
To list the modules for firefox.exe:

whatdlls.exe firefox.exe
```

### Output

```powershell
The program will display the following information for each module (DLL) loaded by the target process:

    Address: The memory address where the module is loaded.
    Name: The name of the loaded module (DLL).

Example output:

Enumerating modules for PID: 1234
Address: 0x7ffd0000 Name: kernel32.dll
Address: 0x7ffa0000 Name: user32.dll
```

### Building the Project
```powershell
Clone the repository or download the source files.
Open the solution in Visual Studio (or any compatible C++ IDE).
Build the project by selecting Build > Build Solution.
```

### License

This project is licensed under the MIT License - see the LICENSE.md file for details.
