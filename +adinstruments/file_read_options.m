classdef file_read_options < handle
    %
    %   Class:
    %   adinstruments.file_read_options
    %
    %   Contains reading options. Currently this is for all file formats.
    
    properties %All file formats:
       %adinstruments.file
       remove_empty_channels = true; %If true, channels without data for 
       %all records are removed.
       conversion_max_
    end
    
    properties %Mat file format only
       load_all_mat_on_start = true; %Not yet linked to the method
       %See: adinstruments.mat_file_h
    end
    
    methods
    end
    
end

