function file_obj = readFile(file_path,varargin)
%x Opens up a LabChart file and extracts meta data.
%
%   file_obj = adinstruments.readFile(file_path)
%
%   This function reads some preliminary data from the specified LabChart
%   or simple data file and exposes access to further commands for reading
%   data.
%
%   This is THE gateway function for working with these files.

in.remove_empty_channels = true;
in = sl.in.processVarargin(in,varargin);


   file_h   = adinstruments.sdk.openFile(file_path);
   
   file_obj = adinstruments.file(file_path,file_h,in);
end