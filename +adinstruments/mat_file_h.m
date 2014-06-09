classdef mat_file_h < handle
    %
    %   Class:
    %   adinstruments.mat_file_h
    
    properties
       m %Handle to the file.
    end
    
    methods
        function obj = mat_file_h(file_path,varargin)
           %
           %    obj = adinstruments.mat_file_h(file_path,varargin)
           %
           %    Optional Inputs:
           %    ----------------
           %    load_all : logical (default false)
           %        If true the entire file is loaded into memory at once, 
           %        otherwise the 'matfile' commend and the subsequent
           %        'matlab.io.MatFile' class are used. Loading everything
           %        might makes things slightly faster but it also might be
           %        a lot slower if only analyzing a portion of the file.
           %        It might also cause an "out of memory" error.
           %
           %    See Also:
           %    adinstruments.readFile
           
           %TODO: Link this to input options in read file
           
           in.load_all = false;
           in = sl.in.processVarargin(in,varargin);
           if in.load_all
              obj.m = load(file_path); 
           else
              obj.m = matfile(file_path,'Writable',false);
           end
        end
        function delete(obj)
           %TODO: Delete 
        end
    end
    
end

