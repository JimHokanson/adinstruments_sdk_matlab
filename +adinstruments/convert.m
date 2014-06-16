function convert(file_path,varargin)
%
%   c
%
%   This function will save a .adicht file's contents into a .mat file
%
%   Optional Inputs:
%   ----------------
%   file_path : str (default: prompts user)
%       Path to the file. If omitted a prompt will ask the user to select
%       the file to convert.
%   format : {'h5','mat'} (default 'h5')
%       The format to convert the file to.

in.conversion_options = [];
in.format = 'h5'; %or 'mat'
in = sl.in.processVarargin(in,varargin);

if in.format(1) == '.'
    in.format(1) = [];
end
   
if nargin == 0 || isempty(file_path)
   [file_name,file_root] = uigetfile({'*.adicht'},'Pick a file to convert'); 

    if isnumeric(file_name)
        return
    end
    file_path = fullfile(file_root,file_name);
end


file_obj = adinstruments.readFile(file_path);

switch in.format
    case 'h5'
        %adinstruments.file.exportToMatFile
        file_obj.exportToHDF5File()
    case 'mat'
        %adinstruments.file.exportToMatFile
        file_obj.exportToMatFile();
    otherwise
        error('Unrecognized format option: %s',in.format);


end