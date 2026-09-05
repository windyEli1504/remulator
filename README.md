# remulator

A work-in-progress **RV32I emulator** written in C, built for educational and testing purposes.

The project aims to provide a simple, understandable virtual machine environment for experimenting with the RISC-V architecture, memory systems, virtual hardware, and low-level debugging, capable of running bare metal RV32I firmware.

> **Status:** Work in progress — currently focused on the core emulation infrastructure.

---

### Planned features

Once completed, `remulator` is intended to provide:

1. **RV32I ISA emulation**
   - Full implementation of the RV32I base instruction set
   - ILP32 ABI support

2. **System memory**
   - 4 GB address space (due to 32-bit ISA)
   - 3 GB of address space available as system memory (allocated on demand)
   - The remaining 1 GB strictly reserved for hardware communication through **MMIO (Memory-Mapped I/O)**

3. **Virtual hardware**
   - SDL-based virtual display
   - Virtualized disk backed by a file
   - UART serial console
   - Additional devices may be added as the project evolves

4. **Debugger interface**
   - Debugger interface inspired by GDB
   - Register inspection
   - Memory inspection
   - Support for debugging the emulated machine

The planned hardware device list is subject to change as development progresses.

---

## Current Focus

Development is in very early stages and is currently centered around the core components required to build the emulator:

- RV32I instruction-set implementation
- CPU state and instruction execution
- Memory subsystem
- Address bus
- MMIO infrastructure
- Debugger interface
- Register and memory inspection

Higher-level virtual hardware such as the display, disk, and UART will be implemented after the core emulation infrastructure is sufficiently stable.

---

## Project Structure

```text
remulator/
├── CMakeLists.txt
├── include/
│   └── remulator/
│       └── ...
├── src/
│   ├── main.c
│   └── ...
├── build/                  # Generated build files
├── compile_commands.json   # Generated as a symlink for clangd LSP
├── .gitignore
└── README.md

---

## Technology

`remulator` is written in C and uses a lightweight native development toolchain.

- **Language:** C23
- **Compiler:** Clang / GCC
- **Build system:** CMake
- **Build backend:** Ninja
- **Language server:** Clangd is recommended due to native support of compile_commands.json but any LSP is fine
- **Debugger:** GDB-compatible tooling where applicable
- **Graphics:** SDL3 (planned)

The project is developed primarily on Linux and specifically targeting Linux.