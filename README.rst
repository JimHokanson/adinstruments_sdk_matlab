========
Overview
========

This code base exposes the C SDK by `ADInstruments  <https://www.adinstruments.com/>`_
to Matlab.

General parts include:

- sdk class/package (see adinstruments.sdk) - this is the Matlab code that directly interfaces with the mex code
- sdk_mex (see adinstruments.sdk_mex) - this is the actual mex code which calls the ADInstruments dll

==========
Motivation
==========

LabChart provides functionality for exporting data to a '.mat' file, although I have yet to get it to work. I also would prefer not to have files that are simply copies of the original data but in a different format. This code allows reading data directly from LabChart data files.

==============
Current Status
==============

Although the SDK supports reading and writing, I have currently only exposed, and only plan on exposing, the reading portion.

The methods are nearly all exposed, but I am still working on the interface for calling these methods.

=====
Usage
=====

Currently the SDK requires 32 bit Matlab (sorry :/)

.. code-block:: matlab

   f = adinstruments.readFile(file_path)

