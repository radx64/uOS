# µOS
micro Operating System for x86 architecture

Build status: 
[![Build Status](https://travis-ci.org/radx64/uOS.svg?branch=master)](https://travis-ci.org/radx64/uOS)

### Functionalities
- Bootable
- Knows how to handle Frame Buffer with scrolling it up.
- Text cursor support
- Serial communication support

![Imgur](http://i.imgur.com/TyE9ebt.png)

### Steps
* [x] Bootable via GRUB
* [x] Framebuffer support in VGA text mode
* [x] Support text cursor movement
* [x] Support serial output via serial port (for further debugging purposes)
* [x] Implement some basics of standard library
* [ ] Interrupts [ongoing]
* [ ] Keyboard support [ongoing]
* [ ] File system
* [ ] User mode 
* [ ] Virtual memory
* [ ] Paging
* [ ] System calls
* [ ] Multitasking

### References:
- A. Tanenbaum, 2007. Modern operating systems, 3rd edition. Prentice Hall, Inc.
- D. M. Ritchie B. W. Kernighan, 1988. The c programming language, second edition. Prentice Hall,Inc.,
- E.Helin, A.Renberg. [The little book about OS development](https://littleosbook.github.io/)
- Intel, [Intel 64 and iA-32 architectures software developer’s manual vol. 3A](http://www.intel.com/content/ www/us/en/architecture-and-technology/64-ia-32-architectures-software-developer-vol-3a-part-1-manual.html)
- NASM [tutorial](http://cs.lmu.edu/~ray/notes/nasmtutorial) 
- R. Hyde. The art of Assembly Language [Chapter 22 The PC Serial Ports](http://flint.cs.yale.edu/cs422/doc/art-of-asm/pdf/CH22.PDF)
- Series of lectures from Princeton Univeristy Computer Science Department [link here](https://www.cs.princeton.edu/courses/archive/fall15/cos318)
- JamesM's kernel development tutorials [link here](http://www.jamesmolloy.co.uk/tutorial_html/1.-Environment%20setup.html)
