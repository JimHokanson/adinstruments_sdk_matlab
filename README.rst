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

I've fully implemented the reading portion. I've started the writing portion but I haven't finished it yet. The code is not yet stable; I'm still refactoring and cleaning it up.

=================================
Requirments, Installation & Usage
=================================

Currently the SDK requires 32 bit Matlab (sorry :/). I think ADInstruments may soon be releasing a 64 bit dll. Given the usage of a dll this code only works in Windows.

To install the package needs to be on the Matlab path. I also currently have several references to my `"Matlab Standard Library" <https://github.com/JimHokanson/matlab_standard_library>`_. I'm working on removing trivial dependencies in this library although some of the fancier functionality will probably continue to rely on that repo.

.. code-block:: matlab

   f = adinstruments.readFile(file_path)

