Unity
=====

Simple Unit Testing for C (setjmp/longjmp less version for Microchip's XC8 / PIC16)

This project is forked from original ThrowTheSwitch's project.
The aim here is to develop an Unity version that does not use setjmp/longjmp calls.
This is suitable (and a must too) for compilers that do not support setjmp/longjmp.

XC8 compier does not support them for PIC12/PIC16 microcontrollers.

Changed files:
* unity.c
* unity.h
* unity_internals.h

Some test are performed with modules, that were TDD'ed by setjmp/longjmp UNITY and their behavior
is the same now. I hope I did not introduced errors. Please test this and report any bugs you found.
