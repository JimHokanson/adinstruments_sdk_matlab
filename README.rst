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

====================
Installation & Usage
====================

Labchart needs to be installed on the computer. The SDK may need to be installed. More info will be coming on this soon as I start installing on other people's computers. Alternatively I may at some point choose to upload the required dll.

Currently the SDK requires 32 bit Matlab (sorry :/) I have asked ADInstruments about providing 64 bit support although they did not seemed thrilled with this idea. Requests on their `forum <http://forum.adinstruments.com/>`_ might make this more likely.

.. code-block:: matlab

   f = adinstruments.readFile(file_path)

