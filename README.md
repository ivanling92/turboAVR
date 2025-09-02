# turboAVR

A lightweight utility designed to streamline AVR microcontroller programming for students and developers. TurboAVR simplifies the compilation and programming process for Il Matto boards from the University of Southampton, making it easier to get your code running on AVR hardware quickly.

## Overview

TurboAVR automates the typical AVR development workflow:
1. **Compilation**: Compiles your C code using avr-gcc with optimized settings
2. **Linking**: Creates an ELF executable for the ATmega644P microcontroller
3. **Hex Generation**: Converts the ELF to Intel HEX format
4. **Programming**: Uploads the firmware to your Il Matto board via USB ASP programmer

## Hardware Support

- **Primary Target**: Il Matto board (ATmega644P @ 12MHz)
- **Programmer**: USB ASP compatible
- **More Information**: [Il Matto Board Details](https://www.ecs.soton.ac.uk/outreach/kits/micro-arcana-series)

## Installation

### Windows Users

1. **Download**: Get the latest turboAVR.exe from the releases
2. **Setup Path**: Run `Installer.bat` to add turboAVR to your system PATH
3. **Dependencies**: Ensure AVR toolchain is installed (avr-gcc, avrdude)

### Mac Users

1. **Install AVR Tools**: 
   ```bash
   brew install avrdude
   ```

2. **Fix Driver Issues** (if needed):
   ```bash
   brew install cmake pkg-config hidapi libftdi libusb libusb-compat libelf libserialport
   ```

3. **Compile from Source**: Use the provided makeavr.bat as reference for compilation flags

## Usage

### Basic Usage
```bash
turboAVR yourcode.c
```

### Multiple Files
```bash
turboAVR main.c utils.c
```

### Prerequisites
- Ensure your Il Matto board is connected via USB
- Put the board in programming mode before running turboAVR
- Place turboAVR.exe in your project directory or ensure it's in your PATH

### Workflow
1. Write your C code for the ATmega644P
2. Connect your Il Matto board and set it to programming mode
3. Run `turboAVR yourcode.c`
4. Follow the on-screen prompts
5. Your code will be compiled and uploaded automatically

## Technical Details

- **Target MCU**: ATmega644P
- **Clock Frequency**: 12MHz
- **Compiler**: avr-gcc with -Os optimization
- **Output Format**: Intel HEX
- **Programmer Protocol**: USB ASP

## Limitations

- Currently supports single-file and simple multi-file projects
- External libraries are not supported
- Windows-focused (Mac support is experimental)
- Requires manual programming mode activation

## Troubleshooting

### Common Issues

1. **"That's not how this works, you dumbass!"**
   - You forgot to specify a source file
   - Usage: `turboAVR yourfile.c`

2. **Programming Fails**
   - Ensure board is in programming mode
   - Check USB connection
   - Verify driver installation for USB ASP programmer

3. **Compilation Errors**
   - Check your C syntax
   - Ensure code is compatible with AVR-GCC
   - Review compiler output for specific errors

4. **avrdude not found**
   - Install AVR toolchain
   - Ensure avrdude is in your system PATH

### Log Files
TurboAVR generates a LOG.txt file containing programming details. Check this file if programming fails.

## File Structure

```
project/
├── turboAVR.exe      # Main executable
├── yourcode.c        # Your source files
├── prog.elf          # Generated ELF file
├── prog.hex          # Generated HEX file
└── LOG.txt           # Programming log
```

## Building from Source

To compile turboAVR yourself:

```bash
gcc -o turboAVR turboAVR.c
```

Or use the provided `makeavr.bat` script as a reference.

## Contributing

This utility is designed for educational use with Il Matto boards. Contributions to improve compatibility, add features, or fix bugs are welcome.

## Version History

- **V3.5**: Current version with improved error messages and logging
- **V2.3**: Enhanced compilation workflow
- **V1.2**: Initial programmer implementation

## Support

For questions about the Il Matto board or turboAVR usage, refer to the University of Southampton's documentation or check the generated LOG.txt file for programming details.
