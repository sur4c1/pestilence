# Pestilence

Educationnal project about the creatition of a self-duplicating obfuscated malware over ELF.

## Subject requierements

- Doesn't execute when a specific process (`test`) is running.
- Doesn't execute when watched by a debugger
- Infection routine must be ofuscated

## Roadmap

- [ ] Check for a `test` process on the machine
- [ ] Check for a debugger overhead
- [ ] Find the place to inject malecious code inside the binary
- [ ] Inject the code and modify the binary
