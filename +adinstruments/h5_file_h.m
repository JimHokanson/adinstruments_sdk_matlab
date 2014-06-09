classdef h5_file_h < handle
    %
    %   Class:
    %   adinstruments.h5_file_h
    
    properties
       file_path
       m %Handle to the file.
    end
    
    methods
        function obj = h5_file_h(file_path)
           %
           %    obj = adinstruments.h5_file_h(file_path)
           %
           %    See Also:
           %    adinstruments.readFile
           
           %TODO: Since we are not using this right away, we might
           %want to try and get the file path if it were evaluated 
           %currently (in case it is relative)
           obj.file_path = file_path;
           
        end
        function delete(obj)
           %TODO: Delete 
        end
    end
    
end

