classdef (Hidden) test_SDK
    %
    %   Class:
    %   adi.test_SDK
    %
    %   Run as:
    %   adi.test_SDK.run_tests
    
    properties
    end
    
    methods (Static)
        function run_tests()
            
           %This code might move or the function might be renamed ...
           temp_file_path = [tempname() '.adicht'];
           
           file_writer = adi.createFile(temp_file_path);
           
           %TODO: I think I need to delete the temp file from the disk
        end
    end
    
end

