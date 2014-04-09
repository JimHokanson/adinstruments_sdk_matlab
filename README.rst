========
Overview
========

This code base exposes the C SDK by `ADInstruments  <https://www.adinstruments.com/>`_
to Matlab.

General parts include:

- sdk class/package (see adinstruments.sdk) - this is the Matlab code that directly interfaces with the mex code
- sdk_mex (see adinstruments.sdk_mex) - this 

==============
Current Status
==============

Although the SDK supports reading and writing, I have currently only exposed, and only plan on exposing, the reading portion.

I am currently finishing exposure of the read methods.

=====
Usage
=====

Currently the SDK requires 32 bit Matlab (sorry :/)

.. code-block:: matlab

   adfile = adinstruments.sdk.openFile(file_path);

