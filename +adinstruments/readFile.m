function file_obj = readFile(file_path)
%
%
%   file_obj = adinstruments.readFile(file_path)
%
%   This function reads some preliminary data from the specified LabChart
%   or simple data file and exposes access to further commands for reading
%   data.
%
%   This is THE gateway function for working with these files.

   file_h   = adinstruments.sdk.openFile(file_path);
   
   file_obj = adinstruments.file(file_path,file_h);
end