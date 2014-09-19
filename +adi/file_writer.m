classdef file_writer < handle
    %
    %   Class:
    %   adi.file_writer
    
    properties
        file_path
    end
    
    properties (Hidden)
        file_h
        data_writer_h
    end
    
    methods
        function obj = file_writer(file_path,file_h,data_writer_h)
            %
            %   Call adi.createFile() to initialize this object
            %   
            %   obj = adi.file_writer(file_path,file_h)
            %
            %   See Also:
            %   adi.createFile
            
            obj.file_path = file_path;
            obj.file_h = file_h;
            obj.data_writer_h = data_writer_h;
            
        end
        %methods 
        %addRecord
        %addChannel
    end
    
end

