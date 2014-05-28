classdef mat_file_h < handle
    %
    %   Class:
    %   adinstruments.mat_file_h
    
    properties
       m
    end
    
    methods
        function obj = mat_file_h(file_path,varargin)
            
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

