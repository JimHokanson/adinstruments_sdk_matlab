function convertToMat(file_path)
%
%   adinstruments.convertToMat(*file_path)
%

if nargin == 0
   [file_name,file_root] = uigetfile({'*.adicht'},'Pick a file to convert'); 

    if isnumeric(file_name)
        return
    end
    file_path = fullfile(file_root,file_name);
end

file_obj = adinstruments.readFile(file_path);
file_obj.exportToMatFile();

end