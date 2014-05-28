function file_obj = readFile(file_path,varargin)
%x Opens up a LabChart file and extracts meta data.
%
%   file_obj = adinstruments.readFile(file_path)
%
%   This function reads some preliminary data from the specified LabChart
%   or simple data file and exposes access to further commands for reading
%   data.
%
%   Outputs:
%   --------
%   file_obj : adinstruments.file
%
%   This is THE gateway function for working with these files.
%
%   See Also:
%   adinstruments.file


in = adinstruments.file_read_options;
in = sl.in.processVarargin(in,varargin);

[~,~,file_extension] = fileparts(file_path);

if strcmp(file_extension,'.mat')
    sdk = adinstruments.mat_file_sdk;
else
    sdk = adinstruments.sdk;
end

file_h = sdk.openFile(file_path);

file_obj = adinstruments.file(file_path,file_h,sdk,in);
end