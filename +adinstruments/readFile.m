function file_obj = readFile(file_path)
%
%
%   file_obj = adinstruments.readFile(file_path)

   file_obj = adinstruments.sdk.openFile(file_path);
end