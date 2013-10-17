Unity
=====

Simple Unit Testing for C (setjmp/longjmp less version for Microchip's XC8 / PIC16)

This project is forked from original ThrowTheSwitch's project.
The aim here is to develop an Unity version that does not use setjmp/longjmp calls.
This is suitable (and a must too) for compilers that do not support setjmp/longjmp.

XC8 compier does not support them for PIC12/PIC16 microcontrollers.

Changed files:
* src/unity.c
* src/unity.h
* src/unity_internals.h
* auto/generate_test_runner.rb
