========
Overview
========

This code base exposes the C SDK by `ADInstruments  <https://www.adinstruments.com/>`_
to Matlab.

General parts include:

- sdk class/package (see adi.sdk) - this is the Matlab code that directly interfaces with the mex code
- sdk_mex (see +adi/private directory) - this is the actual mex code which calls the ADInstruments dll

==========
Motivation
==========

LabChart provides functionality for exporting data to a '.mat' file, although I have yet to get it to work. I also would prefer not to have files that are simply copies of the original data but in a different format. This code allows reading data directly from LabChart data files.

==============
Current Status
==============

I've fully implemented the reading portion. I've started the writing portion but I haven't finished it yet. The code is not yet stable; I'm still refactoring and cleaning it up.

=================================
Requirments, Installation & Usage
=================================

The SDK requires Windows. A 64 bit dll was released (9/1/2014). Please notify me of any bugs found in the 64 bit version.

To install the package needs to be on the Matlab path. I also currently have several references to my `"Matlab Standard Library" <https://github.com/JimHokanson/matlab_standard_library>`_. I'm working on removing trivial dependencies in this library although some of the fancier functionality will probably continue to rely on that repository.

.. code-block:: matlab

   f = adi.readFile()
   f = adi.convert()

