function file_obj = readFile(file_path)
%
%
%   file_obj = adinstruments.readFile(file_path)

   file_h   = adinstruments.sdk.openFile(file_path);
   
   file_obj = adinstruments.file(file_path,file_h);
end