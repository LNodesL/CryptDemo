# CryptDemo

A simple codebase to showcase a very primitive example of loading an exe & pushing to a tmp file and suspended process.

## Setup Example
Compile Hello World program:
```
gcc helloworld.cpp -static -o helloworld
```

Compile LoadAndRun.c:
```
gcc LoadAndRun.c -static -o LoadAndRun
```

Test program:
```
./LoadAndRun.exe
```


## Dev Notes
- My goal is not to give you a working builder & full crypter experience
- My goal is to help beginners get started by seeing how an exe is converted to binary & pushed to a process
- A lot more work was required to go from this type of prototype to a fully working build + crypter setup on my first project
- Using this codebase you can expect to hit between 5-15/71 on a scanner like Virus Total
- You can consider using function pointers, skCrypter or similar, and other tools to further advance your programs
- Memory allocation or encryption should be the next thing you research after you understand process management from this demo
- You may also want to look into how to generate a header file (see my git or HF thread) to include bin data
- You can also look into how resource objects can be injected into a pre-compiled PE


