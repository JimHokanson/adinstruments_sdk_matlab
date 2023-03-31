classdef file_read_options < handle
    %
    %   Class:
    %   adi.file_read_options
    %
    %   Contains reading options. Currently this is for all file formats.
    
    properties %All file formats:
       %adi.file
       
       %If true, channels without data for all records are removed.
       remove_empty_channels = true; 
       
       %    This should be a cell array of channels which you wish to not
       %    include when reading the file.
       channels_remove = {} %TODO: On setting ensure it is a cell array

       % This should be pairs of <old_names>,<new_names>
       channel_name_mapping = {};
       
       %conversion_max_
    end
    
    properties %Mat file format only
       load_all_mat_on_start = true; %Not yet linked to the method
       %See: adi.mat_file_h
    end
    
    methods
    end
    
end

